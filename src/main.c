#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <json_parser.h>

#include "lex_defs.h"

char 	*token_type_as_str(t_token_type type)
{
	static char		*type_names[] = {
			"LBRACKET",
			"RBRACKET",
			"LCBRACKET",
			"RCBRACKET",
			"LBBRACKET",
			"RBBRACKET",
			"SEMICOLON",
			"COMA",
			"STRING",
			"DOUBLE",
			"INTEGER",
			"EOT"
	};

	return (type_names[type]);
}

void	print_token(t_token *token)
{
	printf("type: %s\n", token_type_as_str(token->type));
	if (token->type == STRING)
		printf("value: \"%s\"\n\n", (char *)token->value);
	else if (token->type == INTEGER)
		printf("value: \"%d\"\n\n", *((int *)token->value));
}

char	*json_type_as_str(t_json_type type)
{
	static char *type_names[] = {
			"ARRAY",
			"OBJECT",
			"STRING",
			"INTEGER",
			"DOUBLE",
	};
	return (type_names[type]);
}

void	print_json_element(t_json_element *elem);

void	print_json_array(t_json_array *array)
{
	t_list_node	*cur;

	cur = array->elements.begin;
	while (cur)
	{
		print_json_element(cur->content);
		cur = cur->next;
	}
}

void	print_json_object(t_json_object *object)
{
	t_list_node	*cur;

	cur = object->dict.begin;
	while (cur)
	{
		printf("KEY: %s\n", ((t_json_dentry *)(cur->content))->key);
		print_json_element(((t_json_dentry *)(cur->content))->value);
		cur = cur->next;
	}
}

void	print_json_element(t_json_element *elem)
{
	printf("TYPE: %s\n", json_type_as_str(elem->type));
	if (elem->type == ARRAY)
		print_json_array(elem->value);
	else if (elem->type == OBJECT)
		print_json_object(elem->value);
	else if (elem->type == VSTRING)
		printf("VALUE: %s\n", elem->value);
	else if (elem->type == VINTEGER)
		printf("VALUE: %d\n", *(int *)(elem->value));
	printf("\n");
}

int		test_parse(char *str)
{
	lex_init(str);
	t_json_element *res = parse_element();
	if (res)
		print_json_element(res);
	return (0);
}

int main()
{
	int res = test_parse("{"
					  "\"ARRAY\" : [\"HELLO\", 1, 2, 123],"
	   "\"STRING_TYPE\" : \"IM STRING!\","
	"\"OBJECT\": {}"
					  "}");

	printf("RES: %d\n", res);
	return (0);
}
