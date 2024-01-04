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

void free_lexer_list(t_info *info)
{
	t_lexer *current;
	t_lexer *next;

	current = info->lexer;
	//printf("token: %s\n", current->token);
	while (current != NULL)
	{
		next = current->next;
		//printf("token: %s\n", current->token);
		free(current->token);
		free(current);
		current = next;
	}
}

void ft_free_env(t_env *env)
{
	t_env *current;
	t_env *next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		free(current->var);
		free(current->value);
		free(current);
		current = next;
	}
}

void free_input(t_info *info)
{
	ft_free_env(info->env_list);
	ft_free_array(info->env);
	free(info->old_pwd);
	free(info->pwd);
	free(info->path);
	free(info->home);
	free(info);
}



void ft_free_all(t_pars *pars, t_info *info, int flag)
{
	if (info && flag == 2)
	{
		free_input(info);
	}
	(void)flag;
	if (info->lexer != NULL)
		free_lexer_list(info);
	if (pars != NULL)
		free_pars_list(pars);
}
