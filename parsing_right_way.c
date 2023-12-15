#include "minishell.h"
#include <stdio.h>

void free_pars_list(t_pars *head)
{
	t_pars *current;
	t_pars *next;
	int i;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd_path);
		free(current->command);
		if (current->cmd_args != NULL)
		{
			i = 0; // Reset i to 0
			while (current->cmd_args[i])
			{
				free(current->cmd_args[i]);
				i++;
			}
		}
		free(current->cmd_args);
		if (current->args != NULL)
		{
			i = 0; // Reset i to 0
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		free(current->in_file);
		free(current->out_file);
		free(current);
		current = next;
	}
}

int ft_check_word_type(t_pars *pars, t_lexer *tokens, t_info *info)
{
	(void)info;
	(void)pars;
	if (strcmp(tokens->token, "pwd") == 0 || strcmp(tokens->token, "echo") == 0
		|| strcmp(tokens->token, "cd") == 0 || strcmp(tokens->token, "env") == 0
		|| strcmp(tokens->token, "export") == 0 || strcmp(tokens->token, "unset") == 0
		|| strcmp(tokens->token, "exit") == 0)
		return (1);
	return (0);
}

char *get_path_new(t_pars *pars, t_lexer *tokens, char *token, t_info *info)
{
    int i;
    char *exec;
    char **allpath;
    char *path_part;
    char **s_cmd;

	(void)tokens;
	(void)pars;
    i = -1;
/* 	if (ft_check_word_type(pars, tokens, info) == 1)
		return (NULL); */
    allpath = ft_split(info->path, ':');
    s_cmd = ft_split(token, ' ');
    while (allpath[++i])
    {
        path_part = ft_strjoin(allpath[i], "/");
        exec = ft_strjoin(path_part, s_cmd[0]);
        free(path_part);
        if (access(exec, F_OK | X_OK) == 0)
        {
            return (exec);
        }
        free(exec);
    }
    return (token);
}

int is_next_args(t_lexer *tokens)
{

	if (tokens->next != NULL && tokens->next->type != TokenTypePipe) 
		return (1);
	return (0);
}

void ft_print_pars(t_pars *pars)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (pars != NULL)
	{
		printf("Node: %d\n", i);
		printf("----------------------\n");
		printf("Fd_in: %d\n", pars->fd_in);
		printf("Fd_out: %d\n", pars->fd_out);
		printf("In_file: %s\n", pars->in_file);
		printf("Out_file: %s\n", pars->out_file);
		printf("Cmd_path: %s\n", pars->cmd_path);
		printf("Command: %s\n", pars->command);
		printf("cmd_args: ");
		if (pars->cmd_args != NULL)
		{
			k = 0;
			while (pars->cmd_args[k])
			{
				printf("%s ", pars->cmd_args[k]);
				k++;
			}
		}
		printf("\n");
		printf("Args: ");
		if (pars->args != NULL)
		{
			j = 0;
			while (pars->args[j])
			{
				printf("%s ", pars->args[j]);
				j++;
			}
		}
		printf("\n");
		printf("----------------------\n");
		pars = pars->next;
		i++;
	}
}


int ft_lstsize(t_lexer *tokens)
{
	int count;

	count = 0;

	while ((tokens->next != NULL) && (tokens != NULL || tokens->type != TokenTypePipe))
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

int ft_can_be_cmd_args(t_lexer *lexer)
{
	t_lexer *tmp;

	tmp = lexer;
	if (tmp->type == TokenTypeInputRedirect || tmp->type == TokenTypeOutputRedirect
		|| tmp->type == TokenTypeOutputAppend || tmp->type == TokenTypeHeredoc)
		return (0);
	return (1);

}

char **ft_add_cmd_args(char **args)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	while(args[i])
	{
		//printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args[i])
	{
		if (args[i] == NULL)
			break ;
		if (args[i] && (ft_strncmp(args[i], ">>", 2) == 0 || ft_strncmp(args[i], "<<", 2) == 0
			|| ft_strncmp(args[i], ">", 1) == 0 || ft_strncmp(args[i], "<", 1) == 0))
		{
			i += 2;
			if (args[i] == NULL)
				break ;
		}
		else
		{
			tmp[j] = ft_strdup(args[i]);
			i++;
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

t_pars *node_for_word(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars	*node;
	t_lexer	*tmp1;
	int		i;

	i = 1;
	tmp1 = tmp;
	node = malloc(sizeof(t_pars));
	//printf("size to malloc:%d\n", ft_lstsize(tmp));
	node->args = malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	if ((tmp->type == TokenTypeHeredoc || tmp->type == TokenTypeOutputRedirect
		|| tmp->type == TokenTypeOutputAppend || tmp->type == TokenTypeInputRedirect)
		&& tmp->next && tmp->next->next)
	{
		if (tmp->next)
			tmp = tmp->next;
		if (tmp->next)
			tmp = tmp->next;
		node->command = ft_strdup(tmp->token);
		node->cmd_path = get_path_new(pars, tmp, tmp->token, info);
		node->args[0] = ft_strdup(tmp1->token);
		while (is_next_args(tmp1) == 1)
		{
			node->args[i++] = ft_strdup(tmp1->next->token);
			tmp1 = tmp1->next;
			}
		node->args[i] = NULL;
		node->cmd_args = ft_add_cmd_args(node->args);
	}
	else if ((tmp->type == TokenTypeHeredoc || tmp->type == TokenTypeOutputRedirect
		|| tmp->type == TokenTypeOutputAppend || tmp->type == TokenTypeInputRedirect))
	{
		node->command = NULL;
		node->cmd_path = NULL;
		node->args[0] = ft_strdup(tmp1->token);
		while (is_next_args(tmp1) == 1)
		{
			node->args[i++] = ft_strdup(tmp1->next->token);
			tmp1 = tmp1->next;
			}
		node->args[i] = NULL;
		node->cmd_args = ft_add_cmd_args(node->args);
	}
	else
	{
		node->command = ft_strdup(tmp->token);
		node->cmd_path = get_path_new(pars, tmp, tmp->token, info);
		node->args[0] = ft_strdup(tmp->token);
		while (is_next_args(tmp) == 1)
		{
			node->args[i++] = ft_strdup(tmp->next->token);
			tmp = tmp->next;
			}
		node->args[i] = NULL;
		node->cmd_args = ft_add_cmd_args(node->args);
	}
	node->in_file = NULL;
	node->out_file = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	return(node);
}



void add_pars_node(t_pars *pars, t_pars **head, t_lexer *tmp, t_info *info)
{
	t_pars *new_node = malloc(sizeof(t_pars));
	t_pars *last_node = *head;

	new_node = node_for_word(pars, tmp, info);
	new_node->next = NULL;
	new_node->prev = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	last_node->next = new_node;
	new_node->prev = last_node;

}

char *convert_to_cmd(char *str, t_info *info)
{
	(void)info;
	if (ft_strncmp(str, "/usr/bin/", 9) == 0)
		return (str = ft_substr(str, 9, ft_strlen(str) - 9));
	else if (ft_strncmp(str, "/bin/", 5) == 0)
		return (str = ft_substr(str, 5, ft_strlen(str) - 5));
	else 
		return (str);
}

void ft_redir_input(t_pars *pars, t_info *info, int i, int count)
{
	int fd;
	(void)info;
	fd = open(pars->args[i + 1], O_RDONLY);

	if (i == count)
	{
		pars->fd_in = fd;
		pars->in_file = ft_strdup(pars->args[i + 1]);
	}
}

void ft_redir_output(t_pars *pars, t_info *info, int i, int count)
{
	int fd;
	(void)info;
	fd = open(pars->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	

	if (i == count)
	{
		pars->fd_out = fd;
		pars->out_file = ft_strdup(pars->args[i + 1]);
	}
}

void ft_redir_output_app(t_pars *pars, t_info *info, int i, int count)
{
	int fd;
	(void)info;
	fd = open(pars->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	

	if (i == count)
	{
		pars->fd_out = fd;
		pars->out_file = ft_strdup(pars->args[i + 1]);
	}
}

void ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count)
{
	int fd;
	char *line;
	char *str;
	(void)info;
	(void)count;
	fd = open("/tmp/temp8726343", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", ".tmp");
		info->exit_status = 1;
		return ;
	}
	g_global.in_hd = 1;
	while (!g_global.stop_hd)
	{
		line = readline("> ");
		if (ft_strncmp(line, pars->args[i + 1], ft_strlen(pars->args[i + 1])) == 0)
			break ;
		str = ft_strjoin(line, "\n");
		write(fd, str, ft_strlen(str));
		free(line);
		free(str);	
	}
	close(fd);
	if (g_global.stop_hd || !line)
		return ;
	if (i == count)
	{
		pars->fd_in = open("/tmp/temp8726343", O_RDONLY);
		pars->in_file = ft_strdup("/tmp/temp8726343");
	}
}

int ft_check_num(char **str, char *c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], c, 1) == 0)
			count = i;
		i++;
	}
	return (count);
}

void ft_redir(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	int i;	

	tmp = pars;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{

			if (ft_strncmp(tmp->args[i], ">>", 2) == 0)
				ft_redir_output_app(tmp, info, i, ft_check_num(tmp->args, ">>"));
			else if (ft_strncmp(tmp->args[i], "<<", 2) == 0)
			{	
				g_global.stop_hd = 0;	
				ft_redir_heredoc(tmp, info, i, ft_check_num(tmp->args, "<<"));
				g_global.in_hd = 0;
			}
			else if (ft_strncmp(tmp->args[i], "<", 1) == 0)
				ft_redir_input(tmp, info, i, ft_check_num(tmp->args, "<"));
			else if (ft_strncmp(tmp->args[i], ">", 1)	== 0)	
				ft_redir_output(tmp, info, i,ft_check_num(tmp->args, ">"));
			i++;
		}	
		tmp = tmp->next;
	}
}

void ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info)
{
	t_lexer *tmp;
	/* t_pars *pars = NULL; */
	

	info->val = 0;
	tmp = tokens;
	while (tmp)
	{
		tmp->token = convert_to_cmd(tmp->token, info);
		add_pars_node(*pars, pars, tmp, info);
		while (tmp->next && tmp->type != TokenTypePipe)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	ft_redir(*pars, info);
}

/* 

echo "hello" > file1 > file2 < inflie1 < inflie2 | ls -l > file1 > file2

*/