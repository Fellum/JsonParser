#include "lex_defs.h"
#include "read_token.h"

static char		*text;
static t_token	cur_token;

int 			lex_init(char *str)
{
	text = str;
	return (read_token(&text, &cur_token));
}

t_token			lex_get_token()
{
	return (cur_token);
}

int	 			lex_next_token()
{
	return (read_token(&text, &cur_token));
}

