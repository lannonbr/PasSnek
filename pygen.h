#ifndef PYGEN_H
#define PYGEN_H

#include "statement.h"
#include "tree.h"

void py_func(statement_t * list);
void py_proc(statement_t * list);
void py_math(statement_t * list);
void py_array(statement_t * list);
void py_declrations(statement_t * list);
void py_relationals(statement_t * list);
void py_gen(statement_t * list);

void py_print_expr(tree_t *tree);
void py_write(tree_t * tree);

#endif