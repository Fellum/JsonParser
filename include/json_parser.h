//
// Created by fellum on 12/27/19.
//

#ifndef JSONPARSER_JSON_PARSER_H
#define JSONPARSER_JSON_PARSER_H

#include "ft_list.h"
#include "lex_defs.h"

typedef enum		e_json_type
{
	ARRAY,
	OBJECT,
	VSTRING,
	VINTEGER,
	VDOUBLE
}					t_json_type;

typedef struct		s_json_element
{
	void			*value;
	t_json_type		type;
}					t_json_element;

typedef struct		s_json_array
{
	t_list			elements;		//typeof t_json_element
}					t_json_array;

typedef struct		s_json_object
{
	t_list			dict;			//typeof t_json_dentry
}					t_json_object;

typedef struct		s_json_dentry
{
	char 			*key;
	t_json_element	*value;
}					t_json_dentry;

void	free_array(t_json_array *arr);
t_json_array	*parse_array();

void	free_element(t_json_element *elem);
t_json_element	*parse_element();

void	free_object(t_json_object *elem);
t_json_object	*parse_object();

#endif //JSONPARSER_JSON_PARSER_H
