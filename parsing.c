#include "minishell.h"

void handle_builtin(t_parsing *pars, const char *token, int *i);
void handle_path(t_parsing *pars, const char *token, int *j);
void handle_argument(t_parsing *pars, const char *token, int *k);

/* t_lexer *create_token(int type, const char *token) {
    t_lexer *new_token = malloc(sizeof(t_lexer));
    new_token->type = type;
    new_token->token = strdup(token);
    new_token->next = NULL;
    return new_token;
} */

/* void free_tokens(t_lexer *tokens) {
    while (tokens != NULL) {
        t_lexer *temp = tokens;
        tokens = tokens->next;
        free(temp->token);
        free(temp);
    }
} */

// Function to tokenize input
/* t_lexer *tokenize_input(const char *input) {
    t_lexer *head = NULL;
    t_lexer *current = NULL;

    // Tokenize the input based on spaces
    char *token = strtok(strdup(input), " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            // Output redirect
            current->next = create_token(TokenTypeOutputRedirect, ">");
			current = current->next;
        } else if (strcmp(token, "<") == 0) {
            // Input redirect
            current->next = create_token(TokenTypeInputRedirect, "<");
			current = current->next;
        } else if (strcmp(token, ">>") == 0) {
            // Output append
            current->next = create_token(TokenTypeOutputAppend, ">>");
			current = current->next;
        } else if (strcmp(token, "<<") == 0) {
            // Heredoc
            current->next = create_token(TokenTypeHeredoc, "<<");
			current = current->next;
        } else if (strcmp(token, "|") == 0) {
            // Pipe
            current->next = create_token(TokenTypePipe, "|");
			current = current->next;
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
} */

/* void print_tokens(t_lexer *tokens)
{
    while (tokens != NULL) {
        printf("Type: %d, Token: %s\n", tokens->type, tokens->token);
        tokens = tokens->next;
    }
} */

/* void free_parsing(t_parsing *pars)
{
	if (pars->cmd_path)
		free(pars->cmd_path);
    if (pars->in_file)
		free(pars->in_file);
	if (pars->out_file)
		free(pars->in_file);
    if (pars->out_file)
		free(pars->out_file);
	if (pars->args)
	{
    	for (int i = 0; pars->args && pars->args[i] != NULL; i++) {
    	    free(pars->args[i]);
    	}
    	free(pars->args);
	}
} */

void ft_print(t_parsing *pars)
{
	// Print the cmd_builtins array
	for (int i = 0; pars->cmd_builtin && pars->cmd_builtin[i] != NULL; i++) {
		printf("cmd_builtin: %s\n", pars->cmd_builtin[i]);
	}
	// Print the cmd_path array
	for (int i = 0; pars->cmd_path && pars->cmd_path[i] != NULL; i++) {
		printf("cmd_path:    %s\n", pars->cmd_path[i]);
	}
	// Print the args array
	for (int i = 0; pars->args && pars->args[i] != NULL; i++) {
		printf("args: num:   %d %s\n", i, pars->args[i]);
	}
}

void ft_parser(t_lexer *tokens, t_parsing *pars) {
    int i = 0;
	int j = 0;
	int k = 0;

	pars->yon = 0;
    pars->cmd_path = NULL;
    pars->cmd_builtin = NULL;
    pars->args = NULL;
    pars->in_file = NULL;
    pars->out_file = NULL;
    pars->fd_in = 0;
    pars->fd_out = 0;
    pars->fd_pipe[0] = 0;
    pars->fd_pipe[1] = 0;
	pars->lexer = tokens;

    while (tokens != NULL)
	{
		if (tokens->type == TokenTypeInputRedirect)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_RDONLY);
			handle_argument(pars, tokens->token, &k);
			pars->yon = 1;
            printf("redir_in:    %s\n", pars->in_file);
        }
		else if (tokens->type == TokenTypeOutputRedirect)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			handle_argument(pars, tokens->token, &k);
			pars->yon = 1;
            printf("redir_out:   %s\n", pars->out_file);
        }
		else if (tokens->type == TokenTypeOutputAppend)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			handle_argument(pars, tokens->token, &k);
			pars->yon = 1;
            printf("recir_append: %s\n", pars->in_file);
        }
		else if (tokens->type == TokenTypeHeredoc)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			handle_argument(pars, tokens->token, &k);
			pars->yon = 1;
            printf("heredoc_delimiter: %s\n", pars->out_file);
        }
		else if (tokens->type == TokenTypeWord)
		{
			if (strcmp(tokens->token, "pwd") == 0 || strcmp(tokens->token, "echo") == 0 || strcmp(tokens->token, "cd") == 0 || strcmp(tokens->token, "env") == 0 || strcmp(tokens->token, "export") == 0 || strcmp(tokens->token, "unset") == 0 || strcmp(tokens->token, "exit") == 0)
				handle_builtin(pars, tokens->token, &i);
			else
			 	handle_path(pars, tokens->token, &j);
			handle_argument(pars, tokens->token, &k);
		} 
        tokens = tokens->next;
    }
	ft_print(pars);
}

/* int main()
{
    const char *input = "ls -l > output.txt < input.txt << append.txt | grep pattern";

    t_lexer *tokens = tokenize_input(input);

    printf("Tokens:\n");
    print_tokens(tokens);

    printf("\nParsed:\n");
    t_parsing parsing;
    ft_parser(tokens, &parsing);

    free_tokens(tokens);
    free_parsing(&parsing);

    return 0;
} */

/* int ft_check_prev_token_type(t_lexer *tokens)
{
	if (tokens->type == TokenTypeInputRedirect && tokens->next->type == TokenTypeWord)
		return (1);
	else if (tokens->type == TokenTypeOutputRedirect && tokens->next->type == TokenTypeWord)
		return (1);
	else if (tokens->type == TokenTypeOutputAppend && tokens->next->type == TokenTypeWord)
		return (1);
	else if (tokens->type == TokenTypeHeredoc && tokens->next->type == TokenTypeWord)
		return (1);
	return (0);
} */

void handle_builtin(t_parsing *pars, const char *token, int *i)
{
    if (pars->cmd_builtin == NULL) {
        pars->cmd_builtin = malloc(sizeof(char *));
        pars->cmd_builtin[0] = NULL;
    }
    pars->cmd_builtin = realloc(pars->cmd_builtin, (*i + 2) * sizeof(char *));
    pars->cmd_builtin[*i] = strdup(token);
    pars->cmd_builtin[*i + 1] = NULL;
    (*i)++;
}

void handle_path(t_parsing *pars, const char *token, int *j)
{
	if (pars->yon == 1)
	{
		pars->yon = 0;
		return ;
	}
    if (pars->cmd_path == NULL) {
        pars->cmd_path = malloc(sizeof(char *));
        pars->cmd_path[0] = NULL;
    }
    pars->cmd_path = realloc(pars->cmd_path, (*j + 2) * sizeof(char *));
    pars->cmd_path[*j] = ft_strjoin("/usr/bin/", token);
    pars->cmd_path[*j + 1] = NULL;
    (*j)++;
}

void handle_argument(t_parsing *pars, const char *token, int *k)
{
    if (pars->args == NULL) {
        pars->args = malloc(sizeof(char *));
        pars->args[0] = NULL;
    }
    pars->args = realloc(pars->args, (*k + 2) * sizeof(char *));
    pars->args[*k] = strdup(token);
    pars->args[*k + 1] = NULL;
    (*k)++;
}