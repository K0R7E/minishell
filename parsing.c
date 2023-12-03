#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// Token types
enum {
    TokenTypeWord = 1,
    TokenTypeOutputRedirect = 2,
    TokenTypeInputRedirect = 3,
    TokenTypeOutputAppend = 4,
    TokenTypeHeredoc = 5,
    TokenTypePipe = 6,
    TokenTypeEnd = 7,
};

typedef struct s_lexer
{   
    int             pipes;
    int             type;
    char            *token;
    struct s_lexer  *next;
}   t_lexer;

typedef struct s_parsing
{
    char    *cmd_path;
    int     command; //whatever this means?
    t_lexer *lexer;
    char    **args;
    char    *in_file;
    char    *out_file;
    int     fd_in;
    int     fd_out;
    int     fd_pipe[2];
}   t_parsing;

t_lexer *create_token(int type, const char *token) {
    t_lexer *new_token = malloc(sizeof(t_lexer));
    new_token->type = type;
    new_token->token = strdup(token);
    new_token->next = NULL;
    return new_token;
}

void free_tokens(t_lexer *tokens) {
    while (tokens != NULL) {
        t_lexer *temp = tokens;
        tokens = tokens->next;
        free(temp->token);
        free(temp);
    }
}

// Function to tokenize input
t_lexer *tokenize_input(const char *input) {
    t_lexer *head = NULL;
    t_lexer *current = NULL;

    // Tokenize the input based on spaces
    char *token = strtok(strdup(input), " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            // Output redirect
            current->next = create_token(TokenTypeOutputRedirect, ">");
        } else if (strcmp(token, "<") == 0) {
            // Input redirect
            current->next = create_token(TokenTypeInputRedirect, "<");
        } else if (strcmp(token, ">>") == 0) {
            // Output append
            current->next = create_token(TokenTypeOutputAppend, ">>");
        } else if (strcmp(token, "<<") == 0) {
            // Heredoc
            current->next = create_token(TokenTypeHeredoc, "<<");
        } else if (strcmp(token, "|") == 0) {
            // Pipe
            current->next = create_token(TokenTypePipe, "|");
        } else {
            // Word
            if (head == NULL) {
                head = create_token(TokenTypeWord, token);
                current = head;
            } else {
                current->next = create_token(TokenTypeWord, token);
                current = current->next;
            }
        }

        token = strtok(NULL, " ");
    }

    // Add an end token
    if (current != NULL) {
        current->next = create_token(TokenTypeEnd, "");
    }

    return head;
}

void print_tokens(t_lexer *tokens)
{
    while (tokens != NULL) {
        printf("Type: %d, Token: %s\n", tokens->type, tokens->token);
        tokens = tokens->next;
    }
}

void free_parsing(t_parsing *pars) {
    free(pars->cmd_path);
    free(pars->in_file);
    free(pars->out_file);
    for (int i = 0; pars->args && pars->args[i] != NULL; i++) {
        free(pars->args[i]);
    }
    free(pars->args);
}

void ft_parser(t_lexer *tokens, t_parsing *pars) {
    int j = 0;

    pars->cmd_path = NULL;
    pars->command = 0;
    pars->args = NULL;
    pars->in_file = NULL;
    pars->out_file = NULL;
    pars->fd_in = 0;
    pars->fd_out = 0;
    pars->fd_pipe[0] = 0;
    pars->fd_pipe[1] = 0;
	pars->lexer = tokens;

    while (tokens != NULL) {
        if (tokens->type == TokenTypeWord) {
            // Initialize args to NULL before reallocating memory
            if (pars->args == NULL) {
                pars->args = malloc(sizeof(char *));
                pars->args[0] = NULL;
            }

            pars->args = realloc(pars->args, (j + 2) * sizeof(char *));
            pars->args[j] = strdup(tokens->token);
            pars->args[j + 1] = NULL;
            j++;
        } else if (tokens->type == TokenTypeInputRedirect) {
            pars->in_file = strdup(tokens->token);
            pars->fd_in = open(pars->in_file, O_RDONLY);
            printf("redir_in: %s\n", pars->in_file);
        } else if (tokens->type == TokenTypeOutputRedirect) {
            pars->out_file = strdup(tokens->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            printf("redir_out: %s\n", pars->out_file);
        } else if (tokens->type == TokenTypeOutputAppend) {
            pars->in_file = strdup(tokens->token);
            pars->fd_in = open(pars->in_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            printf("recir_append: %s\n", pars->in_file);
        } else if (tokens->type == TokenTypeHeredoc) {
            pars->out_file = strdup(tokens->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            printf("heredoc_delimiter: %s\n", pars->out_file);
        }
        tokens = tokens->next;
    }
	// Print the args array outside the loop
	for (int i = 0; pars->args && pars->args[i] != NULL; i++) {
		printf("args: %s\n", pars->args[i]);
	}
}

int main()
{
    const char *input = "ls -l > output.txt < input.txt >> append.txt | grep pattern";

    t_lexer *tokens = tokenize_input(input);

    printf("Tokens:\n");
    print_tokens(tokens);

    printf("\nParsed:\n");
    t_parsing parsing;
    ft_parser(tokens, &parsing);

    free_tokens(tokens);
    free_parsing(&parsing);

    return 0;
}

