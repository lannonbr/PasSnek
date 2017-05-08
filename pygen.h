#ifndef PYGEN_H
#define PYGEN_H

#include "statement.h"
#include "tree.h"

void py_funcproc_header(node_t *node);
void py_arg_list(node_t * nodes);
void py_gen(statement_t * list);

void py_print_expr(tree_t *tree);
void py_binop(tree_t *tree);
void py_call(char* name, tree_list_t* args);
void py_call_args(tree_list_t *args);
void py_write(tree_t * tree);
void py_read(tree_t *tree);
void py_if(statement_t *list);
void py_while(statement_t *list);

#endif
