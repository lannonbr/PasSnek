#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "util.h"
#include "statement.h"
#include "tree.h"
#include "pascal.tab.h"
#include "pygen.h"

extern int tab_count;
extern FILE * output;

void py_func(statement_t * list){
//deals with python function calls when they show upp in the tree

}

void py_proc(statement_t * stmt){
	POUT("def %s ():\n" , stmt->stmt.proc_stmt.ident->name);
	tab_count++;
	stmt_pop_stack(stmt->stmt.proc_stmt.proc_expr_list->head);
	py_tab();
	py_gen(stmt->stmt.proc_stmt.proc_expr_list->head);
	tab_count--;
}

void py_math(statement_t * list){

}

void py_array(statement_t * list){

}

void py_relationals(statement_t * list){


}

void py_declrations(statement_t * list){

}

void py_gen(statement_t * list){
//walks thought the tree dealing with cases as they come
	printf("FUCKING FUCK THE GEN DO THE PYTHONS\n");

	switch(list->type) {
		case ST_ASSIGN:
			printf("ASSIGN :D\n");
			POUT("%s = ", list->stmt.assign_stmt.ident->name);
			py_print_expr(list->stmt.assign_stmt.tree);
			POUT("\n");
			break;
		case ST_PROC:
			if(strcmp(list->stmt.proc_stmt.ident->name, "write") == 0) {
				py_write(list->stmt.proc_stmt.proc_expr_list->head);
			}else if(strcmp(list->stmt.proc_stmt.ident->name, "read") == 0){
				py_read(list->stmt.proc_stmt.proc_expr_list->head);
			}else{
				printf("else\n");
				py_proc(list->stmt.proc_stmt.proc_expr_list->head);
			}
			break;
		default:
			printf("LULZ\n");
			break;
	}

	if(list->next != NULL) {
		py_gen(list->next);
	}

}

void py_print_expr(tree_t *tree) {

	printf("do the print\n");
	if(tree->left != NULL) {
		py_print_expr(tree->left);
	}
	switch(tree->type) {
		case T_INT:
			printf("Printing expr out\n");
			POUT("%d", tree->attribute.ival);
			break;
		case T_BINOP:
			break;
		case T_ID:
			POUT("%s", tree->attribute.sval->name);
			break;
		default:
			POUT("Case Not Handled in print_exprt\n");
			break;

	}
	if(tree->right != NULL) {
		py_print_expr(tree->right);
	}
}

void py_write(tree_t* tree) {
	POUT("print(");
	py_print_expr(tree);
	POUT(")\n");
}

void py_read(tree_t *tree){
	printf("i did a read\n"); 
	POUT("%s =",tree->attribute.sval->name);
	POUT("input()\n");
	//print_tree(tree);

}
