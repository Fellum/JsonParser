#include <libft.h>
#include "json_parser.h"

void	free_object(t_json_object *elem)
{

}

void	free_dentry(t_json_dentry *entry)
{

}

t_json_dentry	*parse_dentry()
{
	t_json_dentry	*res;

	if (!(res = ft_memalloc(sizeof(t_json_dentry)))||
		lex_get_token().type != STRING)
	{
		free(res);
		return (NULL);
	}
	res->key = lex_get_token().value;
	if (lex_next_token() != 0 || lex_get_token().type != SEMICOLON)
	{
		free(res->value);
		free(res);
		return (NULL);
	}
	if (lex_next_token() != 0 || !(res->value = parse_element()))
	{
		free(res->value);
		free(res);
		return (NULL);
	}
	return (res);
}

t_json_object	*parse_object()
{
	t_json_object	*res;
	t_json_dentry	*tmp;

	if (lex_next_token() != 0)
		return (NULL);
	if (!(res = ft_memalloc(sizeof(t_json_object))))
		return (NULL);
	if (lex_get_token().type == R_CBRACKET)
		return (res);
	if (!(tmp = parse_dentry()))
	{
		free(res);
		return (NULL);
	}
	ft_lstaddend(&(res->dict), ft_lstnew_node(tmp, sizeof(*tmp)));
	while (lex_get_token().type == COMA)
	{
		if (lex_next_token() != 0 || !(tmp = parse_dentry()))
		{
			free_object(res);
			return (NULL);
		}
		ft_lstaddend(&(res->dict), ft_lstnew_node(tmp, sizeof(*tmp)));
	}
	if (lex_get_token().type != R_CBRACKET)
	{
		free_object(res);
		return (NULL);
	}
	if (lex_next_token() != 0)
	{
		free_object(res);
		return (NULL);
	}
	return (res);
}