#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtable.h"

// Generate a new scope to the symbol table stack
sym_table_stack_t *create_stack() {
	int i;
	sym_table_stack_t * stack = (sym_table_stack_t*) malloc(sizeof(sym_table_stack_t));

	stack->var_count = 1;

	for(int i = 0; i < HASH_SIZE; i++) {
		stack->table[i] = NULL;
	}

	stack->next = NULL;

	return stack;
}

sym_table_stack_t *pop_stack(sym_table_stack_t *head) {
	sym_table_stack_t *temp_stack;

	if(head != NULL) {
		temp_stack = head;
		head = head->next;

		/* printf("Popping stack [%s]\n", temp_stack->name); */

		if(head != NULL) {
			/* printf("Now Top: [%s]\n", head->name); */
		}

		/* free_sts(temp_stack); */

		return head;
	}


	return NULL;
}

sym_table_stack_t *push_stack(sym_table_stack_t *head, char* name) {
	sym_table_stack_t *new_stack = create_stack();

	if(new_stack == NULL) {
		fprintf(stderr, "Error: empty symbol table stack");
		exit(1);
	}

	new_stack->next = head;
	new_stack->name = name;

	/* printf("New stack [%s] created\n", name); */

	return new_stack;
}

// Search for a node within a single scope
node_t * sts_search(sym_table_stack_t *head, char* name) {
	int idx;
	node_t *node;

	if(head != NULL) {
		idx = hashpjw(name);
		/* printf("HASHPJW[%s]: %d\n", name, idx); */
		node = head->table[idx];

		return search_node(node, name);
	}

	return NULL;
}

// Search for a node through all scopes going top-down
node_t * sts_global_search(sym_table_stack_t *head, char* name) {
	node_t * node;
	sym_table_stack_t *scope = head;

	while(scope != NULL) {
		node = sts_search(scope, name);
		if(node != NULL) {
			// printf("Found %s in symbol table\n", node->name);
			return node;
		}
		scope = scope->next;
	}
	fprintf(stderr, "Error: %s not found in any symbol table\n", name);
	exit(1);
}

// Insert a node into the top scope
node_t * sts_insert(sym_table_stack_t *head, int type, char* name) {
	int idx;

	node_t *node;

	char* tmp_name;

	// Handle the translations between input->read and output->write
	if(!strcmp(name, "input")) {
		tmp_name = "read";
	} else if(!strcmp(name, "output")) {
		tmp_name = "write";
	} else {
		tmp_name = name;
	}

	if(head != NULL) {
		idx = hashpjw(tmp_name);
		/* printf("HASHPJW[%s]: %d\n", tmp_name, idx); */

		node = head->table[idx];

		// Insert only if the node doesn't already exist in the current scope
		if(search_node(node, tmp_name) == NULL) {
			head->table[idx] = insert_node(node, type, tmp_name, head->var_count);
			/* printf("Inserted %s into %s\n", tmp_name, head->name); */
			head->var_count += 1;
			return head->table[idx];
		} else {
			fprintf(stderr, "%s is already in current symbol table\n", tmp_name);
			exit(1);
		}
	}

	return NULL;
}

void free_sts(sym_table_stack_t *head) {
	for(int i = 0; i < HASH_SIZE; i++) {
		// printf("%p\t%p\n", head, head->table[i]);
		free_node(head->table[i]);
	}
	if(head->next != NULL)
		free_sts(head->next);
}

// The hashpjw algorithm from the Dragon book
int hashpjw( char *s )
{
	char *p; 
	unsigned h = 0, g; 

	for ( p = s; *p != EOS; p++ ) 
	{ 
		h = (h << 4) + (*p); 
		if ( (g = (h & 0xf0000000)) != 0) 
		{ 
			h = h ^ ( g >> 24 ); 
			h = h ^ g; 
		} 
	} 
	return h % HASH_SIZE; 
}
