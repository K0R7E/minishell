#include "minishell.h"

void ft_free_1 (char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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

void ft_free_all(t_pars *pars, t_info *info)
{
	if (pars != NULL)
		free_pars_list(pars);
	(void)info;
/* 	if (info->lexer != NULL)
		free_lexer_list(info->lexer); */
}
