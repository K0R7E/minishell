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


char *remove_quotes(char *str)
{
	int i;
	int j;
	int in_dbl;
	int in_sgl;
	char *new_str;

	i = 0;
	j = 0;
	in_dbl = 0;
	in_sgl = 0;
	new_str = malloc(sizeof(char) * find_new_length(str) + 1);
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_sgl == 0)
		{
			if (in_dbl == 0)
				in_dbl = 1;
			else
				in_dbl = 0;
			i++;
			continue ;
		}
		else if (str[i] == '\'' && in_dbl == 0)
		{
			if (in_sgl == 0)
				in_sgl = 1;
			else
				in_sgl = 0;
			i++;
			continue ;
		}
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
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

void	remove_quotes_from_parsing_list(t_pars *pars)
{
	t_pars *tmp;
	char *tmp_token;
	int i;

	i = 0;
	tmp = pars;
	while (tmp != NULL)
	{
		while (tmp->cmd_args[i] != NULL)
		{
			tmp_token = remove_quotes(tmp->cmd_args[i]);
			free(tmp->cmd_args[i]);
			tmp->cmd_args[i] = strdup(tmp_token);
			free(tmp_token);
			tmp_token = remove_quotes(tmp->command);
			free(tmp->command);
			tmp->command = strdup(tmp_token);
			free(tmp_token);
			i++;

		}
		tmp = tmp->next;
	}

}