#include "minishell.h"

void ft_free_1 (char **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return ;
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

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd_path);
		free(current->command);
		ft_free_1(current->cmd_args);
		ft_free_1(current->args);
		free(current->in_file);
		free(current->out_file);
		free(current);
		current = next;
	}
}

void free_lexer_list(t_lexer *head)
{
	t_lexer *current;
	t_lexer *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}

void ft_free_all(t_pars *pars, t_info *info)
{
	t_lexer *lexer;

	lexer = &info->lexer;
	if (pars)
		free_pars_list(pars);
 	if (lexer)
		free_lexer_list(lexer);
}
