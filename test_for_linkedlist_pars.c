#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void free_pars_list(t_pars *head)
{
	t_pars *current;
	t_pars *next;
	int i;

	i = 0;
	current = head;
	while (current != NULL)
	{
        next = current->next;
        free(current->cmd_path);
        free(current->command);
		free(current->other);
        if (current->args != NULL)
		{
            while (current->args[i])
                free(current->args[i++]);
            free(current->args);
        }
        free(current->in_file);
        free(current->out_file);
        free(current);
        current = next;
    }
}

/* void ft_get_input(t_info *info)
{
	char *line;

	line = readline(LIME"minishell>"OFF);
	wait(NULL);
	if (line == NULL)
	{
		rl_on_new_line();
	}
	else if (line[0] == '\0')
	{
		free(line);
		ft_get_input(info);
	}
	else //(line[0] != '\0')
		add_history(line);
	info->input = ft_strdup(line);
	free(line);
	if (ft_check_input(info) == 1)
		ft_get_input(info);	
} */

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

    i = -1;
	if (ft_check_word_type(pars, tokens, info) == 1)
		return (NULL);
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

int is_next_args(t_pars **pars, t_lexer *tokens, t_info *info)
{
	(void)info;
	(void)pars;
	if (tokens->next != NULL && (ft_check_word_type(*pars, tokens, info) == 1))
	{
		if (((strcmp(tokens->token, "echo") == 0) && tokens->next->token[0] == '-')
			|| ((strcmp(tokens->token, "echo") == 0) && tokens->next->token[0] != '-'))
			return (1);
		else if ((strcmp(tokens->token, "cd") == 0) && tokens->next->token[0] == '/')
			return (1);
		else if ((strcmp(tokens->token, "export") == 0) || (strcmp(tokens->token, "unset") == 0))
			return (1);
		else
		 	return (0);
	}
	else if (tokens->next != NULL && (tokens->next->type != TokenTypePipe
		&& tokens->next->type != TokenTypeInputRedirect && tokens->next->type != TokenTypeOutputRedirect
		&& tokens->next->type != TokenTypeOutputAppend && tokens->next->type != TokenTypeHeredoc)) 
		return (1);
	return (0);
}


void ft_print_pars(t_pars *pars)
{
	int i = 0;
	int j = 0;

	while (pars != NULL)
	{
		printf("Node: %d\n", i);
		printf("----------------------\n");
		printf("Fd_in: %d\n", pars->fd_in);
		printf("Fd_out: %d\n", pars->fd_out);
		printf("Fd_pipe[0]: %d\n", pars->fd_pipe[0]);
		printf("Fd_pipe[1]: %d\n", pars->fd_pipe[1]);
		printf("In_file: %s\n", pars->in_file);
		printf("Out_file: %s\n", pars->out_file);
		printf("Cmd_path: %s\n", pars->cmd_path);
		printf("Command: %s\n", pars->command);
		printf("Other: %s\n", pars->other);
		printf("Type: %d\n", pars->type);
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

t_pars *node_for_inputredirect(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars *node;

	(void)info;
	(void)pars;
	node = malloc(sizeof(t_pars));
	node->cmd_path = NULL;
	node->command = NULL;
	node->other = NULL;
	node->type = tmp->type;
	node->in_file = ft_strdup(tmp->next->token);
	node->out_file = NULL;	
	node->fd_in = open(node->in_file, O_RDONLY);
	node->fd_out = -1;
	node->fd_pipe[0] = -1;
	node->fd_pipe[1] = -1;	
	if (node->fd_in == -1)
	{
		printf("minishell: %s: No such file or directory\n", pars->in_file);
		info->exit_status = 1;
		return NULL;
	}
	tmp = tmp->next;
	return(node);
}

t_pars *node_for_outputredirect(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars *node;

	(void)info;
	(void)pars;
	node = malloc(sizeof(t_pars));
	node->cmd_path = NULL;
	node->command = NULL;
	node->other = NULL;
	node->type = tmp->type;
	node->in_file = NULL;
	node->out_file = ft_strdup(tmp->next->token);
	node->fd_in = -1;
	node->fd_out = open(node->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	node->fd_pipe[0] = -1;
	node->fd_pipe[1] = -1;	
	if (node->fd_out == -1)
	{
		printf("minishell: %s: No such file or directory\n", node->out_file);
		info->exit_status = 1;
		return NULL;
	}
	tmp = tmp->next;
	return (node);
}

t_pars *node_for_outputappend(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars *node;

	(void)info;
	(void)pars;
	node = malloc(sizeof(t_pars));
	node->cmd_path = NULL;
	node->command = NULL;
	node->other = NULL;
	node->type = tmp->type;
	node->in_file = NULL;
	node->out_file = ft_strdup(tmp->next->token);
	node->fd_in = -1;
	node->fd_out = open(node->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	node->fd_pipe[0] = -1;
	node->fd_pipe[1] = -1;
	if (node->fd_out == -1)
	{
		printf("minishell: %s: No such file or directory\n", node->out_file);
		info->exit_status = 1;
		return NULL;
	}
	tmp = tmp->next;
	return(node);
}

t_pars *node_for_pipe(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars *node;

	(void)info;
	(void)pars;
	(void)tmp;
	node = malloc(sizeof(t_pars));
	node->cmd_path = NULL;
	node->command = ft_strdup(tmp->token);
	node->other = NULL;
	node->type = tmp->type;
	node->in_file = NULL;
	node->out_file = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fd_pipe[0] = -1;
	node->fd_pipe[1] = -1;
	info->command_count++;
	return(node);
}

t_pars *node_for_heredoc(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars *node;

	(void)info;
	(void)pars;
	node = malloc(sizeof(t_pars));
	node->cmd_path = NULL;
	node->command = ft_strdup(tmp->next->token);
	node->other = NULL;
	node->type = tmp->type;
	node->in_file = NULL;
	node->out_file = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fd_pipe[0] = -1;
	node->fd_pipe[1] = -1;
	tmp = tmp->next;
	return(node);
}

int ft_lstsize(t_lexer *tokens)
{
	int count;

	count = 0;

	while ((tokens->next != NULL) && (tokens != NULL || tokens->type != TokenTypePipe || tokens->type != TokenTypeInputRedirect
		|| tokens->type != TokenTypeOutputRedirect || tokens->type != TokenTypeOutputAppend
		|| tokens->type != TokenTypeHeredoc))
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

t_pars *node_for_word(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars	*node;
	int		i;
	int 	j;	

	i = 1;
	j = 0;
	node = malloc(sizeof(t_pars));
	//printf("size to malloc:%d\n", ft_lstsize(tmp));
	node->args = malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	if (((ft_check_word_type(pars, tmp, info) == 1) || info->val == 1)
		|| info->val == 2 || info->val == 3)
	{
		node->command = ft_strdup(tmp->token);
		node->other = NULL;
		node->cmd_path = get_path_new(pars, tmp, tmp->token, info);
		node->args[0] = ft_strdup(tmp->token);
		while (is_next_args(&pars, tmp, info) == 1)
		{
			node->args[i++] = ft_strdup(tmp->next->token);
			tmp = tmp->next;
		}
		//node->args[i] = NULL;
	}
	else
	{
		node->command = NULL;
		node->other = ft_strdup(tmp->token);
		node->cmd_path = NULL;
		node->args = NULL;
	}
	node->type = tmp->type;
	node->in_file = NULL;
	node->out_file = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fd_pipe[0] = 0;
	node->fd_pipe[1] = 1;	
	return(node);
}

t_pars *parsing_decision(t_pars *pars, t_lexer *tmp, t_info *info)
{
	if (tmp->type == TokenTypeInputRedirect)
		return(node_for_inputredirect(pars, tmp, info));
	else if (tmp->type == TokenTypeOutputRedirect)
		return(node_for_outputredirect(pars, tmp, info));
	else if (tmp->type == TokenTypeOutputAppend)
		return(node_for_outputappend(pars, tmp, info));
	else if (tmp->type == TokenTypePipe)
		return(node_for_pipe(pars, tmp, info));
	else if (tmp->type == TokenTypeHeredoc)
		return(node_for_heredoc(pars, tmp, info));
	else if (tmp->type == TokenTypeWord)
		return(node_for_word(pars, tmp, info));
	return NULL;
}

void add_pars_node(t_pars *pars, t_pars **head, t_lexer *tmp, t_info *info)
{
	t_pars *new_node = malloc(sizeof(t_pars));
	t_pars *last_node = *head;

	new_node = parsing_decision(pars, tmp, info);
	new_node->next = NULL;

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

}

void ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info)
{
	t_lexer *tmp;
	/* t_pars *pars = NULL; */
	
	info->val = 2;
	tmp = tokens;
	while (tmp)
	{
		
		if (tmp->type == TokenTypeInputRedirect || tmp->type == TokenTypeOutputRedirect
			|| tmp->type == TokenTypeOutputAppend || tmp->type == TokenTypeHeredoc)
			{
				add_pars_node(*pars, pars, tmp, info);
				info->val = 1;
				tmp = tmp->next;	
			}
		else if (tmp->type == TokenTypePipe) 
		{
			add_pars_node(*pars, pars, tmp, info);
			info->val = 3;
		}
		else
		{
			add_pars_node(*pars, pars, tmp, info);
			if (tmp->next != NULL)
			{
				while(is_next_args(pars, tmp, info) == 1)
					tmp = tmp->next;
			}
			info->val = 4;
		}
		tmp = tmp->next;
	}
}
/* 
int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_parsing *parsing;
	t_pars *pars;

	info = malloc(sizeof(t_info));
	parsing = malloc(sizeof(t_parsing));


	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		return (1);
	}
	info->env = ft_arrycpy(envp);
	env_conversion(info);
	get_pwd(info);
	info->exit_status = 0;
	printf("\033[2J\033[1;1H");
 	while (1)
	{
		pars = malloc(sizeof(t_pars));
		pars = NULL;
		info->builtin_command_count = 0;
		ft_get_input(info);
		ft_lexer(info, parsing);
		ft_parsing(&pars, &parsing->lexer, info);
		ft_print_pars(pars);
		free_pars_list(pars);
	}
	return (0);
} */


/*

cc -Wall -Wextra -Werror -g -lreadline -o test test_for_linkedlist_pars.c env_conversion.c ft_cpyarry.c change_env_var.c change_env_var_utils.c lexer.c lexer_utils.c ft_getpwd.c input_check.c libft/libft.a

  0     1    2   3   4  5  6   7   8  9  10 11  12 13  14  15  16 17 18 1920 21 
echo "hello" > file1 | cat < file1 | cat -e > file2 | cat file2 | ls -l | wc -l

*/
