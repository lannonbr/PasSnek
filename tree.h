#include "node.h"
#include "enums.h"
#include "util.h"

#ifndef TREE_H
#define TREE_H

typedef struct tree_s {
	type_e type;
	int leaf;
	side_e side;
	int label;
	union {
		int ival;
		float fval;
		node_t *sval;
		binop bopval;
		unaryop uopval;
	} attribute;
	struct tree_s *left, *right;
} tree_t;

typedef struct tree_list_s {
	tree_t * head;
	tree_t * next;
} tree_list_t;

tree_t * gen_tree();
tree_t * gen_ident(node_t *sval);
tree_t * gen_num(int ival);
tree_t * gen_real(float fval);
tree_t * gen_binop(binop opval, tree_t *left, tree_t *right);
tree_t * gen_unaryop(unaryop opval, tree_t *left);

void print_tree(tree_t *tree, int offset);
void print_binop(tree_t *tree);

void free_tree(tree_t *tree);

tree_list_t * create_tree_list(tree_t *tree);
tree_list_t * tree_list_insert(tree_list_t *tree_list, tree_t *tree);

void free_tree_list(tree_list_t *tree_list);

#endif
