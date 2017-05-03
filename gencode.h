#ifndef GENCODE_H
#define GENCODE_H

#include "statement.h"
#include "tree.h"

tree_t * tree_label(tree_t *tree);
int label_aux(tree_t *tree);

void gen_code_io_strings();
void gen_code_main_preamble();
void gen_code_main_ending();
void gen_code_stmt_list(statement_t *list);
void gen_code_expr(tree_t *tree);
void gen_code_expr_op(binop op, char* fparam, char* sparam);
void gen_code_write(tree_t *expr);
void gen_code_read(tree_t *expr);
void gen_code_if_then_else(statement_t *stmt);
void gen_code_while(statement_t *stmt);
void gen_code_proc_call(statement_t *stmt);
void gen_code_proc_preamble();
void gen_code_proc_ending();

void push_parameters(tree_list_t *list);
char* get_val(tree_t *tree);

#endif
