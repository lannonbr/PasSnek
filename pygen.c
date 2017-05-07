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

	py_tab();

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
		case ST_IFTHENELSE:
			printf("IFTHENELSE");
			py_if(list);	
			break;
		case ST_WHILE:
			printf("While");
			py_while(list);	
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
			py_binop(tree);
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

void py_binop(tree_t *tree) {
	switch(tree->attribute.bopval) {
		case OP_LT:
			POUT(" < ");
			break;
		case OP_LE:
			POUT(" <= ");
			break;
		case OP_GT:
			POUT(" > ");
			break;
		case OP_GE:
			POUT(" >= ");
			break;
		case OP_EQ:
			POUT(" == ");
			break;
		case OP_NEQ:
			POUT(" != ");
			break;
		case OP_ADD:
			POUT(" + ");
			break;
		case OP_SUB:
			POUT(" - ");
			break;
		case OP_OR:
			POUT(" or ");
			break;
		case OP_MUL:
			POUT(" * ");
			break;
		case OP_DIV:
			POUT(" / ");
			break;
		case OP_MOD:
			POUT(" % ");
			break;
		case OP_AND:
			POUT(" and ");
			break;
	}
}

void py_write(tree_t* tree) {
	POUT("print(");
	py_print_expr(tree);
	POUT(")\n");
}

void py_read(tree_t *tree){
	printf("i did a read\n"); 
	POUT("%s = int(input())\n",tree->attribute.sval->name);
	//print_tree(tree);

}

void py_if(statement_t * list) {
	POUT("if (");
	py_print_expr(list->stmt.if_then_else_stmt.tree);
	POUT("):\n");
	tab_count++;
	py_gen(list->stmt.if_then_else_stmt.if_stmt);
	tab_count--;
	POUT("else:\n");
	tab_count++;
	py_gen(list->stmt.if_then_else_stmt.else_stmt);
	tab_count--;
}

// tree
// do_stmt
void py_while(statement_t * list) {
	POUT("while (");
	py_print_expr(list->stmt.while_stmt.tree);
	POUT("):\n");
	tab_count++;
	py_gen(list->stmt.while_stmt.do_stmt);
	tab_count--;
}
