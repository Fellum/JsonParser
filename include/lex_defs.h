//
// Created by fellum on 12/22/19.
//

#ifndef JSONPARSER_LEX_DEFS_H
#define JSONPARSER_LEX_DEFS_H

typedef enum	e_token_type
{
	L_BRACKET,
	R_BRACKET,
	L_CBRACKET,
	R_CBRACKET,
	L_BBRACKET,
	R_BBRACKET,
	SEMICOLON,
	COMA,
	STRING,
	DOUBLE,
	INTEGER,
	EOT
}				t_token_type;

#define TERM_CHARS "(){}[]:,"

typedef struct	s_token
{
	t_token_type	type;
	void			*value;
}				t_token;

int 			lex_init(char *str);
t_token			lex_get_token();
int	 			lex_next_token();

#endif //JSONPARSER_LEX_DEFS_H
