#include "minishell.h"

int	find_new_length(char *str)
{
	int in_dbl;
	int in_sgl;
	int i;
	int j;

	i = 0;
	j = 0;
	in_dbl = 0;
	in_sgl = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_sgl == 0)
		{
			if (in_dbl == 0)
				in_dbl = 1;
			else
				in_dbl = 0;
			i++;
		}
		if (str[i] == '\'' && in_dbl == 0)
		{
			if (in_sgl == 0)
				in_sgl = 1;
			else
				in_sgl = 0;
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}


char	*remove_quotes(char *str)
{
	int				i;
	int				j;
	t_quote_state	qs;
	char			*new_str;

	qs.state_d = 0;
	qs.state_s = 0;
	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * find_new_length(str) + 1);
	if (new_str == NULL)
		return (NULL);
	while (str && str[i] != '\0')
	{
		if (str[i] == '\"' && qs.state_s == 0)
		{
			qs.state_d = update_quote_state(qs.state_d);
			i++;
			continue ;
		}
		else if (str[i] == '\'' && qs.state_d == 0)
		{
			qs.state_s = update_quote_state(qs.state_s);
			i++;
			continue ;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

/*
void	remove_quotes_from_lexer_list(t_lexer *lexer)
{
	t_lexer *tmp;
	char *tmp_token;

	tmp = lexer;
	while (tmp != NULL)
	{
		tmp_token = remove_quotes(tmp->token);
		free(tmp->token);
		tmp->token = tmp_token;
		tmp = tmp->next;
	}
}
*/

void	remove_quotes_from_parsing_list(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	char *tmp_token;
	int i;

	tmp = pars;
	while (tmp != NULL)
	{
		tmp_token = remove_quotes(tmp->command);
		if (tmp_token == NULL)
			ft_error_message(*info->pars_ptr, info);
		//free(tmp->command); something is wrong here
		tmp->command = strdup(tmp_token);
		if (tmp->command == NULL)
			ft_error_message(*info->pars_ptr, info);
		free(tmp_token);
		i = 0;
		while (tmp->cmd_args[i] != NULL)
		{
			tmp_token = remove_quotes(tmp->cmd_args[i]);
			if (tmp_token == NULL)
				ft_error_message(*info->pars_ptr, info);
			free(tmp->cmd_args[i]);
			tmp->cmd_args[i] = strdup(tmp_token);
			if (tmp->cmd_args[i] == NULL)
				ft_error_message(*info->pars_ptr, info);
			free(tmp_token);
			i++;
		}
		tmp = tmp->next;
	}
}