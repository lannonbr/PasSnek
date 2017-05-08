#ifndef NODE_H
#define NODE_H

#include "enums.h"

typedef struct node_s {
	char *name;
	int type; /* variable, function, procedure */

	/* variable only things */
	int offset;
	type_e var_type;
	int arr_size;

	struct node_s *arguments;

	/* function only things */
	type_e ret_type;
	int param_count;

	/* procedure only things */

	struct node_s *next;
} node_t;

node_t *make_node(int type, char *name);

node_t *insert_node(node_t * head, int type, char* name, int offset);
node_t *search_node(node_t * head, char* name);

void free_node(node_t *node);

#endif
