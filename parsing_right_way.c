#include "minishell.h"

void ft_free_node(t_pars *node)
{
    int i;

    i = 0;
    if (!node)
		return;
    if (node->args != NULL)
    {
        while (node->args[i])
        {
			//printf("node->args[%d]: %s\n", i, node->args[i]);
            free(node->args[i]);
            i++;
        }
    }
    if (node->cmd_args != NULL)
    {
        i = 0;
        while (node->cmd_args[i])
        {
            free(node->cmd_args[i]);
            i++;
        }
    }
	if (node->args != NULL)
    	free(node->args);
	if (node->cmd_args != NULL)
    	free(node->cmd_args);
	if (node->command != NULL)
    	free(node->command); // Freeing the command
	if (node->cmd_path != NULL)
		free(node->cmd_path);
	if (node->in_file != NULL)
		free(node->in_file);
	if (node->out_file != NULL)
    	free(node->out_file);
    free(node);
}

char **calloc_cmd(char **args, t_pars *pars, t_info *info)
{
	int		i;
	char	**tmp;

	i = 0;
	while (args[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (tmp == NULL)
	{
		//free(tmp);
		ft_free_node(pars);
		ft_free_1(args);
		ft_putstr_fd("minishell: malloc error\n", 2);
        ft_free_all(pars, info, 2);
		exit(1);
	}
	return (tmp);
}

char	**ft_add_cmd_args(char **args, t_pars *pars, t_info *info)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_cmd(args, pars, info);
	i = 0;
	while (args[i])
	{
		if (args[i] == NULL)
			break ;
		if (args[i] && (ft_strncmp(args[i], ">>", 2) == 0
				|| ft_strncmp(args[i], "<<", 2) == 0
				|| ft_strncmp(args[i], ">", 1) == 0
				|| ft_strncmp(args[i], "<", 1) == 0))
		{
			i += 2;
			if (args[i] == NULL)
				break ;
		}
		else
		{
			tmp[j] = ft_strdup(args[i]);
			if (tmp[j] == NULL)
			{
				ft_free_1(tmp);
				ft_free_1(args);
				ft_free_node(pars);
				ft_error_message(pars, info);
			}
			i++;
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

void fill_args(t_pars *node, t_lexer *tmp1, t_info *info, t_pars *pars)
{
	int i;

	i = 1;
	node->args[0] = ft_strdup(tmp1->token);
	if (node->args[0] == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
	}
	while (is_next_args(tmp1) == 1)
	{
		node->args[i++] = ft_strdup(tmp1->next->token);
		if (node->args[i - 1] == NULL)
		{
			ft_free_node(node);
			ft_error_message(pars, info);
		}
		tmp1 = tmp1->next;
	}
	node->args[i] = NULL;
}

void	init_node(t_pars *node)
{
	node->in_file = NULL;
	node->out_file = NULL;
	node->command = NULL;
	node->args = NULL;
	node->cmd_path = NULL;
	node->cmd_args = NULL;
	node->next = NULL;	
	node->fd_in = 0;
	node->fd_out = 1;
}

t_pars *allocate_node(t_pars *pars, t_info *info, int arg_size)
{
    t_pars *node;
	
	node = malloc(sizeof(t_pars));
    if (!node)
	{
		ft_free_node(node);
        ft_putstr_fd("minishell: malloc error\n", 2);
        ft_free_all(pars, info, 2);
        exit(1);
    }
	init_node(node);
    node->args = malloc(sizeof(char *) * arg_size);
    if (!node->args)
	{
		ft_free_node (node);
        ft_putstr_fd("minishell: malloc error\n", 2);
        ft_free_all(pars, info, 2);
        exit(1);
    }
    return (node);
}

void process_special_tokens(t_pars *node, t_pars *pars, t_lexer *tmp, t_info *info)
{
    int j;
	
	j = 0;
    while (tmp->type != TokenTypePipe)
	{
        if (tmp->next && tmp->next->next)
		{
            tmp = tmp->next;
            tmp = tmp->next;
            j = 1;
        }
		else
		{
            node->command = NULL;
            node->cmd_path = NULL;
            break;
        }
        if (j == 1 && tmp->type == TokenTypeWord)
		{
            node->command = ft_strdup(tmp->token);
			if (node->command == NULL)
			{
				ft_free_node(node);
				ft_error_message(pars, info);
			}
            node->cmd_path = get_path_new(pars, tmp->token, info);
            break;
        }
		else if (tmp->next == NULL || tmp->type == TokenTypePipe)
		{
            node->command = NULL;
            node->cmd_path = NULL;
            break;  
        }
    }
}

void initialize_node_files(t_pars *node)
{
    node->in_file = NULL;
    node->out_file = NULL;
    node->fd_in = 0;
    node->fd_out = 1;
}

t_pars	*node_for_word(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars	*node;
	t_lexer	*tmp1;

	tmp1 = tmp;
	node = allocate_node(pars, info, ft_lstsize(tmp) + 2);
	if ((tmp->type == TokenTypeHeredoc || tmp->type == TokenTypeOutputRedirect
			|| tmp->type == TokenTypeOutputAppend
			|| tmp->type == TokenTypeInputRedirect)
		&& tmp->next)
	{
		fill_args(node, tmp1, info, pars);
		process_special_tokens(node, pars, tmp, info);
		node->cmd_args = ft_add_cmd_args(node->args, pars, info);
	}
	else
	{
		fill_args(node, tmp, info, pars);
        node->command = ft_strdup(tmp->token);
		//node->command = NULL;
		if (node->command == NULL)
		{
			ft_free_node(node);
			ft_error_message(pars, info);
		}
		node->cmd_path = get_path_new(pars, tmp->token, info);
		node->cmd_args = ft_add_cmd_args(node->args, pars, info);
	}
	initialize_node_files(node);
	return (node);
}

void	add_pars_node(t_pars *pars, t_pars **head, t_lexer *tmp, t_info *info)
{
	t_pars	*new_node;
	t_pars	*last_node;

	last_node = *head;
	new_node = node_for_word(pars, tmp, info);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
}

int	ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info)
{
	t_lexer	*tmp;

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
	if (ft_redir(*pars, info) == 1)
		return (1);
	return (0);
}
