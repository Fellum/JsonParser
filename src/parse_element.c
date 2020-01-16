//
// Created by fellum on 12/27/19.
//

#include <libft.h>
#include "json_parser.h"

void	free_element(t_json_element *elem)
{
	if (elem->type == ARRAY)
		free_array(elem->value);
	else if (elem->type == OBJECT)
		free_object(elem->value);
	else if (elem->type == VDOUBLE || elem->type == VINTEGER || elem->type == VSTRING)
		free(elem->value);
	free(elem);
}

t_json_element	*parse_element()
{
	t_json_element	*res;

	res = ft_memalloc(sizeof(t_json_element));
	if (lex_get_token().type == L_BBRACKET)
	{
		res->value = parse_array();
		res->type = ARRAY;
	}
	else if (lex_get_token().type == L_CBRACKET)
	{
		res->value = parse_object();
		res->type = OBJECT;
	}
	else if (lex_get_token().type == DOUBLE)
	{
		res->value = lex_get_token().value;
		res->type = VDOUBLE;
		lex_next_token();
	}
	else if (lex_get_token().type == STRING)
	{
		res->value = lex_get_token().value;
		res->type = VSTRING;
		lex_next_token();
	}
	else if (lex_get_token().type == INTEGER)
	{
		res->value = lex_get_token().value;
		res->type = VINTEGER;
		lex_next_token();
	}
	else
	{
		free(res);
		res = NULL;
	}
	return (res);
}

