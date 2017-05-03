#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "tree.h"
#include "util.h"

tree_t * gen_tree() {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));
	new_tree->type = T_OTHER;
	return new_tree;
}

tree_t * gen_ident(node_t *sval) {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));
	new_tree->type = T_ID;
	new_tree->attribute.sval = sval;
	return new_tree;
}

tree_t * gen_int(int ival) {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));
	new_tree->type = T_INT;
	new_tree->attribute.ival = ival;
	return new_tree;
}

tree_t * gen_real(float fval) {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));
	new_tree->type = T_REAL;
	new_tree->attribute.fval = fval;
	return new_tree;
}

tree_t * gen_binop(binop opval, tree_t *left, tree_t *right) {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));;
	new_tree->type = T_BINOP;
	new_tree->attribute.bopval = opval;
	new_tree->left = left;
	new_tree->right = right;
	return new_tree;
}

tree_t * gen_unaryop(unaryop opval, tree_t *left) {
	tree_t * new_tree = (tree_t *) malloc(sizeof(tree_t));
	new_tree->type = T_UNOP;
	new_tree->attribute.uopval = opval;
	new_tree->left = left;
	return new_tree;
}

// Print out the tree for debugging purposes
void print_tree(tree_t * tree, int offset) {
	if(tree == NULL)
		return;

	print_spaces(offset);

	switch(tree->type) {
		case T_BINOP:
			printf("L(%d) BINOP: ", tree->leaf);
			print_binop(tree);
			break;
		case T_UNOP:
			printf("UNOP\n");
			break;
		case T_REAL:
			printf("REAL ");
			printf("%f\n", tree->attribute.fval);
			break;
		case T_INT:
			printf("INT ");
			printf("L(%d) %d\n", tree->leaf, tree->attribute.ival);
			break;
		case T_OTHER:
			printf("OTHER\n");
			break;
		case T_ID:
			printf("ID ");
			printf("%s\n", (tree->attribute.sval)->name);
			break;
		default:
			printf("NOPE\n");
			break;
	}

	if(tree->left != NULL)
		print_tree(tree->left, offset+4);

	if(tree->right != NULL)
		print_tree(tree->right, offset+4);
}

void print_binop(tree_t * tree) {
	switch(tree->attribute.bopval) {
		case OP_LT:
			printf("<\n");
			break;
		case OP_LE:
			printf("<=\n");
			break;
		case OP_GT:
			printf(">\n");
			break;
		case OP_GE:
			printf(">=\n");
			break;
		case OP_EQ:
			printf("=\n");
			break;
		case OP_NEQ:
			printf("<>\n");
			break;
		case OP_ADD:
			printf("+\n");
			break;
		case OP_SUB:
			printf("-\n");
			break;
		case OP_MUL:
			printf("*\n");
			break;
		case OP_DIV:
			printf("/\n");
			break;
		case OP_MOD:
			printf("MOD\n");
			break;
		case OP_AND:
			printf("and\n");
			break;
		case OP_OR:
			printf("or\n");
			break;
	}
}

void free_tree(tree_t *tree) {
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

tree_list_t * create_tree_list(tree_t *tree) {
	tree_list_t * tree_list = (tree_list_t *) malloc(sizeof(tree_list_t));

	tree_list->head = tree;

	return tree_list;
}

tree_list_t * tree_list_insert(tree_list_t *tree_list, tree_t *tree) {
	tree_list_t *curr_tree = tree_list;

	while(curr_tree->next != NULL)
		curr_tree->head = curr_tree->next;

	curr_tree->next = tree;

	return curr_tree;
}

void free_tree_list(tree_list_t *tree_list) {
	tree_list_t *curr_tree = tree_list; 
	tree_t *tmp;

	while(curr_tree->next != NULL) {
		tmp = curr_tree->head;
		curr_tree->head = curr_tree->next;
		free_tree(tmp);
	}
}
