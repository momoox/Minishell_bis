/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:19:24 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:43:25 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_index(char *str, int *index_tab)
{
	static char	quote;
	static int	i;
	static int	u;

	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			index_tab[u++] = i;
		}
		else if (quote != '\0' && str[i] == quote)
		{
			quote = '\0';
			index_tab[u++] = i;
		}
		i++;
	}
	quote = '\0';
	i = 0;
	u = 0;
}

char	*quote_remove(t_mall *mall, char *str)
{
	int		*index_tab;
	int		i;
	char	*new;

	i = 0;
	index_tab = malloc_plus_plus(&mall, sizeof(int) * 100);
	while (i < 100)
		index_tab[i++] = -1;
	i = -1;
	quote_index(str, index_tab);
	new = erase_quote(mall, str, index_tab);
	free(index_tab);
	return (new);
}

void	check_quote_remove(t_mall *mall, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		if (is_between_quote(temp->content, ft_strlen(temp->content)) != 0)
			temp->content = quote_remove(mall, temp->content);
		temp = temp->next;
	}
}

char	is_between_quote(char *str, int index)
{
	char	quote;
	int		i;

	quote = '0';
	i = 0;
	if (!str)
		return (1);
	while (str[i] && i <= index)
	{
		if (quote == '0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != '0' && str[i] == quote)
			quote = '0';
		i++;
	}
	return (quote);
}

char	check_quote(char *str, t_data *data)
{
	char	quote;
	int		i;

	quote = '0';
	i = 0;
	while (str[i])
	{
		if (quote == '0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = '0';
		i++;
	}
	if (quote != '0')
	{
		printf("Minishell : syntax error near unexpected token \'%c\'\n",
			quote);
		data->exit_code = 258;
		// ft_exit(258);
	}
	return (quote);
}
