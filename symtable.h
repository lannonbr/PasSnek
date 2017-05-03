#include "node.h"

#ifndef SYM_TAB_H
#define SYM_TAB_H

#define HASH_SIZE 211
#define EOS '\0'

typedef struct table_stack_s {
	node_t *table[HASH_SIZE]; // The symbol table itself
	char* name; // table_name
	struct table_stack_s *next;

	int var_count;

	struct table_stack_s *static_parent; // The static parent scope
} sym_table_stack_t;

sym_table_stack_t *create_stack();
sym_table_stack_t *pop_stack(sym_table_stack_t *head);
sym_table_stack_t *push_stack(sym_table_stack_t *head, char* name);

node_t * sts_search(sym_table_stack_t *head, char* name);
node_t * sts_global_search(sym_table_stack_t *head, char* name);
node_t * sts_insert(sym_table_stack_t *head, int type, char* name);

void free_sts(sym_table_stack_t *head);

int hashpjw(char *s);

#endif
