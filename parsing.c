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

void init_fds(t_parsing *pars)
{
	pars->fds.flag = -2;
	pars->fds.fd_in = -2;
	pars->fds.fd_out = -2;
	pars->fds.value = NULL;
}

void create_fds_list(t_parsing *pars, int type, char *token)
{
	t_fds *tmp;

	tmp = malloc(sizeof(t_fds));
	if (type == TokenTypePipe)
		tmp->flag = 1;
	else
		tmp->flag = 0;
	if (type == TokenTypeInputRedirect)
	{
		tmp->fd_in = dup(pars->fd_in);
		tmp->fd_out = -1;
	}
	else
	{
		tmp->fd_out = dup(pars->fd_out);
		tmp->fd_in = -1;
	}
	tmp->value = ft_strdup(token);
	tmp->next = NULL;
	if (pars->fds.flag == -2)
	{
		pars->fds = *tmp;
	}
	else
	{
		t_fds *tmp2;

		tmp2 = &pars->fds;
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}

}

void ft_print_fds(t_fds *fds)
{
	t_fds *tmp;
	
	tmp = fds;
	while (tmp != NULL)
	{
		printf("flag: %d\n", tmp->flag);
		printf("fd_in: %d\n", tmp->fd_in);
		printf("fd_out: %d\n", tmp->fd_out);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}

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

int check_if_after_hd(t_lexer *tokens, t_parsing *pars)
{
	t_lexer *tmp;

	(void)pars;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == TokenTypeHeredoc)
		{
			if (tmp->next->type == TokenTypeWord)
				return (1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (0);
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
	init_fds(pars);

	//pars = (t_parsing *){0};

    while (tokens != NULL)
	{
		if (check_if_after_hd(tokens, pars) != 1)
			tokens->token = change_env_var(tokens->token, info);
		if (tokens->type == TokenTypeInputRedirect)
		{
            pars->in_file = strdup(tokens->next->token);
            pars->fd_in = open(pars->in_file, O_RDONLY);
			pars->yon = 1;
            printf("redir_in:    %s\n", pars->in_file);
			tokens = tokens->next;
			if (tokens->next)
				create_fds_list(pars, tokens->next->type, tokens->token);
			else
			 	create_fds_list(pars, -1, tokens->token);
        }
		else if (tokens->type == TokenTypeOutputRedirect)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			pars->yon = 1;
            printf("redir_out:   %s\n", pars->out_file);
			tokens = tokens->next;
			if (tokens->next)
				create_fds_list(pars, tokens->next->type, tokens->token);
			else
			 	create_fds_list(pars, -1, tokens->token);

        }
		else if (tokens->type == TokenTypeOutputAppend)
		{
            pars->out_file = strdup(tokens->next->token);
            pars->fd_out = open(pars->in_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			pars->yon = 1;
            printf("recir_append: %s\n", pars->in_file);
			tokens = tokens->next;
			if (tokens->next)
				create_fds_list(pars, tokens->next->type, tokens->token);
			else
			 	create_fds_list(pars, -1, tokens->token);
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
			tokens = tokens->next;
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
	ft_print_fds(&pars->fds);
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
	(void)info;
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