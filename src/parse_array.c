//
// Created by fellum on 12/27/19.
//

#include <libft.h>
#include "json_parser.h"

void	free_array(t_json_array *arr)
{
	t_list_node	*tmp;

	while ((tmp = ft_lsttake(&(arr->elements))))
	{
		free_element(tmp->content);
		free(tmp);
	}
	free(arr);
}

t_json_array	*parse_array()
{
	t_json_array	*res;
	t_json_element	*tmp;

	if (lex_next_token() != 0)
		return (NULL);
	if (!(res = ft_memalloc(sizeof(t_json_array))))
		return (NULL);
	if (lex_get_token().type == R_BBRACKET)
		return (res);
	if (!(tmp = parse_element()))
	{
		free(res);
		return (NULL);
	}
	ft_lstaddend(&(res->elements), ft_lstnew_node(tmp, sizeof(*tmp)));
	while (lex_get_token().type == COMA)
	{
		if (lex_next_token() != 0 || !(tmp = parse_element()))
		{
			free_array(res);
			return (NULL);
		}
		ft_lstaddend(&(res->elements), ft_lstnew_node(tmp, sizeof(*tmp)));
	}
	if (lex_get_token().type != R_BBRACKET)
	{
		free_array(res);
		return (NULL);
	}
	if (lex_next_token() != 0)
	{
		free_array(res);
		return (NULL);
	}
	return (res);
}

