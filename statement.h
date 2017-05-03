#ifndef STATEMENT_H
#define STATEMENT_H

#include "tree.h"
#include "node.h"

typedef struct statement_s {
	state_type_e type;
	int depth;
	struct statement_s *next;
	struct statement_s *next_depth;
	union {
		struct {
			node_t * ident;
			tree_t * tree;
		} assign_stmt;
		struct {
			node_t * ident;
			tree_list_t * proc_expr_list;
		} proc_stmt;
		struct {
			tree_t * tree;
			struct statement_s * if_stmt;
			struct statement_s * else_stmt;
		} if_then_else_stmt;
		struct {
			tree_t * tree;
			struct statement_s * do_stmt;
		} while_stmt;
	} stmt;
} statement_t;

statement_t * stmt_gen_assign(node_t *ident, tree_t *tree);
statement_t * stmt_gen_proc(node_t *ident, tree_list_t *proc_expr_list);
statement_t * stmt_gen_if_then_else(tree_t *tree, statement_t *if_stmt, statement_t *else_stmt);
statement_t * stmt_gen_while(tree_t *tree, statement_t *do_stmt);

statement_t * stmt_list_append(statement_t *list, statement_t *statment);

void stmt_list_print(statement_t *list, int offset);
void print_stmt_add(statement_t *stmt);

#endif
