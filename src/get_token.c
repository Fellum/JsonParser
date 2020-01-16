#include "libft.h"
#include "lex_defs.h"

static _Bool	eat(char **str, const char c)
{
	if (**str == c)
	{
		(*str)++;
		return (0);
	}
	else
		return (1);
}

static char 	get_string(char **str, t_token *token)
{
	char *res;
	char *tmp;

	(*str)++;
	tmp = *str;
	while (*tmp != '\"')
		tmp++;
	res = malloc((tmp - *str + 1) * sizeof(res));
	memcpy(res, *str, tmp - *str);
	res[tmp - *str] = '\0';
	*str = tmp;
	token->type = STRING;
	token->value = res;
	return ((char)eat(str, '\"'));
}

static _Bool 	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

static char 	get_number(char **str, t_token *token)
{
	int res;
	double	dres;

	res = 0;
	while (is_number(**str))
	{
		res = res * 10 + (**str - 48);
		(*str)++;
	}

	token->type = INTEGER;
	token->value = malloc(sizeof(int));
	*((int *)token->value) = res;
	return (0);
}

static int 	is_term_char(char c)
{
	return (ft_contain(TERM_CHARS, c));
}

static int 	get_term_char(char **str, t_token *token)
{
	char 	*tmp;

	tmp = ft_strchr(TERM_CHARS, **str);
	if (tmp)
	{
		token->type = tmp - TERM_CHARS;
		(*str)++;
		return (0);
	}
	else
		return (1);
}

static void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

int		read_token(char **str, t_token *token)
{
	skip_spaces(str);
	if (**str == '\0')
	{
		token->type = EOT;
		return (0);
	}
	else if (**str == '\"')
		return (get_string(str, token));
	else if (is_number(**str) || **str == '-' || **str == '+')
		return (get_number(str, token));
	else if (is_term_char(**str))
		return (get_term_char(str, token));
	else
		return (1);
}
