#include "minishell.h"

void handle_builtin(t_parsing *pars, const char *token, int *i);
void handle_path(t_parsing *pars, const char *token, int *j);
void handle_argument(t_parsing *pars, const char *token, int *k, t_info *info);

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

void ft_parser(t_lexer *tokens, t_parsing *pars, t_info *info)
{
    int i = 0;
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
	pars->lexer = *tokens;
	pars->heredoc_delimiter = NULL;
	pars->hd_lines = NULL;
	pars->pipes_count = ft_count_pipes(pars);

    while (tokens != NULL)
	{
		if (tokens->type == TokenTypeInputRedirect)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_RDONLY);
			handle_argument(pars, tokens->token, &k, info);
			pars->yon = 1;
            printf("redir_in:    %s\n", pars->in_file);
        }
		else if (tokens->type == TokenTypeOutputRedirect)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			handle_argument(pars, tokens->token, &k, info);
			pars->yon = 1;
            printf("redir_out:   %s\n", pars->out_file);
        }
		else if (tokens->type == TokenTypeOutputAppend)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			handle_argument(pars, tokens->token, &k, info);
			pars->yon = 1;
            printf("recir_append: %s\n", pars->in_file);
        }
		else if (tokens->type == TokenTypePipe)
		{
			handle_argument(pars, tokens->token, &k, info);
			pars->yon = 1;
			printf("pipe: %s\n", tokens->token);
		}
		else if (tokens->type == TokenTypeHeredoc)
		{
			pars->heredoc_delimiter = strdup(tokens->next->token);
			handle_argument(pars, tokens->token, &k, info);
			pars->yon = 1;
            printf("heredoc_delimiter: %s\n", pars->heredoc_delimiter);
        }
		else if (tokens->type == TokenTypeWord)
		{
			if (strcmp(tokens->token, "pwd") == 0 || strcmp(tokens->token, "echo") == 0 || strcmp(tokens->token, "cd") == 0 || strcmp(tokens->token, "env") == 0 || strcmp(tokens->token, "export") == 0 || strcmp(tokens->token, "unset") == 0 || strcmp(tokens->token, "exit") == 0)
				handle_builtin(pars, tokens->token, &i);
			handle_argument(pars, tokens->token, &k, info);
		} 
        tokens = tokens->next;
    }
	ft_print(pars);
	
}

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

/* void handle_path(t_parsing *pars, const char *token, int *j)
{
    int new_size = (*j) + 2;

    char **new_cmd_path = malloc(new_size * sizeof(char *));
    if (!new_cmd_path)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *j; ++i)
    {
        new_cmd_path[i] = pars->cmd_path[i];
    }

    size_t prefix_len = strlen("/usr/bin/");
    size_t token_len = strlen(token);
    char *path_token = malloc(prefix_len + token_len + 1);
    if (!path_token)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    strcpy(path_token, "/usr/bin/");
    strcat(path_token, token);

    new_cmd_path[*j] = path_token;
    new_cmd_path[new_size - 1] = NULL;

    free(pars->cmd_path);

    pars->cmd_path = new_cmd_path;

    (*j)++;
} */

void handle_argument(t_parsing *pars, const char *token, int *k, t_info *info)
{
    if (!pars->heredoc_delimiter)
		token = replace_dollar((char *)token, info);
	//printf("token:%s\n", token); 
	//split up again, if there is a space in the token
	if (pars->args == NULL) {
        pars->args = malloc(sizeof(char *));
        pars->args[0] = NULL;
    }
    pars->args = realloc(pars->args, (*k + 2) * sizeof(char *));
    pars->args[*k] = strdup(token);
    pars->args[*k + 1] = NULL;
    (*k)++;
}