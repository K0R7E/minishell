#include "minishell.h"

void handle_builtin(t_parsing *pars, const char *token, int *i);
void handle_command(t_parsing *pars, const char *token, int *j);
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
	for (int i = 0; pars->cmd_cmd && pars->cmd_cmd[i] != NULL; i++) {
		printf("cmd_cmd:    %s\n", pars->cmd_cmd[i]);
	}
	// Print the args array
	for (int i = 0; pars->args && pars->args[i] != NULL; i++) {
		printf("args: num:   %d %s\n", i, pars->args[i]);
	}
}

void ft_parser(t_lexer *tokens, t_parsing *pars, t_info *info)
{
    int i = 0;
	int j = 0;
	int k = 0;

	pars->yon = 0;
    pars->cmd_cmd = NULL;
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
	pars->pipes_count = 0;
	pars->command_count = 0;

	//pars = (t_parsing *){0};

    while (tokens != NULL)
	{
		if (tokens->type == TokenTypeInputRedirect)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_RDONLY);
			pars->yon = 1;
            printf("redir_in:    %s\n", pars->in_file);
			tokens = tokens->next;
        }
		else if (tokens->type == TokenTypeOutputRedirect)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			pars->yon = 1;
            printf("redir_out:   %s\n", pars->out_file);
			tokens = tokens->next;
        }
		else if (tokens->type == TokenTypeOutputAppend)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->in_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			pars->yon = 1;
            printf("recir_append: %s\n", pars->in_file);
			tokens = tokens->next;
        }
		else if (tokens->type == TokenTypePipe)
		{
			pars->yon = 0;
			pars->pipes_count++;
			printf("pipe: %s\n", tokens->token);
		}
		else if (tokens->type == TokenTypeHeredoc)
		{
			pars->heredoc_delimiter = strdup(tokens->next->token);
			/* pars->fd_in = 0; */
			pars->yon = 1;
            printf("heredoc_delimiter: %s\n", pars->heredoc_delimiter);
        }
		else if (tokens->type == TokenTypeWord)
		{
			if (strcmp(tokens->token, "pwd") == 0 || strcmp(tokens->token, "echo") == 0 || strcmp(tokens->token, "cd") == 0 || strcmp(tokens->token, "env") == 0 || strcmp(tokens->token, "export") == 0 || strcmp(tokens->token, "unset") == 0 || strcmp(tokens->token, "exit") == 0)
			{
				handle_builtin(pars, tokens->token, &i);
				if(tokens->next != NULL)
				{
					if ((strcmp(tokens->next->token, "-n") == 0))
					{
						handle_builtin(pars, tokens->next->token, &i);
						tokens = tokens->next;
					}
				}
				pars->yon = 1;
			}
			else if (pars->yon == 0 || ((tokens->token[0] == '-') && pars->command_count == 1))
			{
				handle_command(pars, tokens->token, &j);
				if (strcmp(tokens->token, "-n") == 0)
					pars->command_count = 0;
			}
			else
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
	pars->command_count = 0;
}

void handle_command(t_parsing *pars, const char *token, int *j)
{
	if (pars->cmd_cmd == NULL) {
		pars->cmd_cmd = malloc(sizeof(char *));
		pars->cmd_cmd[0] = NULL;
	}
	pars->cmd_cmd = realloc(pars->cmd_cmd, (*j + 2) * sizeof(char *));
	pars->cmd_cmd[*j] = strdup(token);
	pars->cmd_cmd[*j + 1] = NULL;
	(*j)++;
	pars->yon = 1;
	pars->command_count = 1;
}

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
	pars->command_count = 0;
}