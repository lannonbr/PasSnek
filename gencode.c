#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gencode.h"
#include "tree.h"
#include "pascal.tab.h"
#include "regstack.h"

extern int num_registers;
extern regstack_t * reg_stack;
extern int label_count;

tree_t * tree_label(tree_t *tree) {
	tree_t * curr_tree = tree;

	if(curr_tree->leaf) {
		if(curr_tree->side == S_LEFT) {
			curr_tree->label = 1;
		} else {
			curr_tree->label = 0;
		}
		return curr_tree;
	}

	int left_label = label_aux(curr_tree->left);
	int right_label = label_aux(curr_tree->right);

	if(left_label == right_label) {
		curr_tree->label = left_label + 1;
	} else {
		curr_tree->label = (left_label >= right_label) ? left_label : right_label;
	}
	return curr_tree;
}

int label_aux(tree_t *tree) {
	tree_t * curr_tree = tree;

	if(curr_tree->leaf) {
		if(curr_tree->side == S_LEFT) {
			return 1;
		} else {
			return 0;
		}
	}

	int left_label = label_aux(curr_tree->left);
	int right_label = label_aux(curr_tree->right);

	if(left_label == right_label) {
		return left_label + 1;
	} else {
		return (left_label >= right_label) ? left_label : right_label;
	}
}

void gen_code_io_strings() {
	printf("\t.section .rodata\n");
	printf(".LC0:\n");
	printf("\t.string \"%%d\\n\"\n");
	printf(".LC1:\n");
	printf("\t.string \"%%d\"\n");
	printf("\t.text\n");
}

void gen_code_main_preamble() {
	printf("\t.globl\tmain\n");
	printf("main:\n");
	// Push base pointer
	printf("\tpushq\t%%rbp\n");
	// move stack pointer
	printf("\tmovq\t%%rsp, %%rbp\n");
	printf("\tsubq\t$16, %%rsp\n");
}

void gen_code_main_ending() {
	// Move return value to %rax
	printf("\tmovq\t$0, %%rax\n");
	// Pop base pointer
	// Quit
	printf("\tleave\n");
	printf("\tret\n");
}

void gen_code_stmt_list(statement_t *list) {
	// Go through each statement and generate the code depending on the statement type
	statement_t *stmt = list;

	// If stmt is empty, just return
	if(stmt == NULL) {
		return;
	}
	
	switch(stmt->type) {
		case ST_ASSIGN:
			stmt->stmt.assign_stmt.tree = tree_label(stmt->stmt.assign_stmt.tree);
			gen_code_expr(stmt->stmt.assign_stmt.tree);
			printf("\tmovq\t%%rax, %d(%%rbp)\n", -4*stmt->stmt.assign_stmt.ident->offset);
			break;
		case ST_PROC:
			if(stmt->stmt.proc_stmt.proc_expr_list != NULL)
				stmt->stmt.proc_stmt.proc_expr_list->head = tree_label(stmt->stmt.proc_stmt.proc_expr_list->head);
			if(strcmp(stmt->stmt.proc_stmt.ident->name, "write") == 0)
				gen_code_write(stmt->stmt.proc_stmt.proc_expr_list->head);
			else if(strcmp(stmt->stmt.proc_stmt.ident->name, "read") == 0)
				gen_code_read(stmt->stmt.proc_stmt.proc_expr_list->head);
			else
				gen_code_proc_call(stmt);
			break;
        case ST_IFTHENELSE:
            gen_code_if_then_else(stmt);
            break;
		case ST_WHILE:
			gen_code_while(stmt);
			break;
		default:
			printf("Nope, don't care yet\n");
			break;
	}

	if(stmt->next != NULL)
		gen_code_stmt_list(stmt->next);
}

void gen_code_expr(tree_t *tree) {
	// GENCODE Algorithm from class
	if(tree->leaf && tree->side == S_LEFT) {
		// CASE 0
		printf("\tmovq\t%s, %s\n", get_val(tree), top_reg_stack(reg_stack));
	} else if(tree->right->leaf) {
		// CASE 1
		gen_code_expr(tree->left);
		gen_code_expr_op(tree->attribute.bopval, get_val(tree->right), top_reg_stack(reg_stack));
	} else if(tree->right->label > tree->left->label && num_registers > tree->left->label) {
		// CASE 2
		reg_stack = swap_reg_stack(reg_stack);
		gen_code_expr(tree->right);
		char* reg = pop_reg_stack(reg_stack);
		gen_code_expr(tree->left);
		gen_code_expr_op(tree->attribute.bopval, reg, top_reg_stack(reg_stack));
		reg_stack = push_reg_stack(reg_stack, reg);
		reg_stack = swap_reg_stack(reg_stack);
	} else if(tree->left->label >= tree->right->label && num_registers > tree->right->label) {
		// CASE 3
		gen_code_expr(tree->left);
		char* reg = pop_reg_stack(reg_stack);
		gen_code_expr(tree->right);
		gen_code_expr_op(tree->attribute.bopval, top_reg_stack(reg_stack), reg);
	} else {
		// CASE 4
		printf("This shouldn't run. If it does, oh dear\n");
		exit(-1);
	}
}

void gen_code_expr_op(binop op, char* fparam, char* sparam) {
	switch(op) {
		case OP_ADD:
			printf("\tadd\t%s, %s\n", fparam, sparam);
			break;
		case OP_MUL:
			printf("\timul\t%s, %s\n", fparam, sparam);
			break;
		case OP_SUB:
			printf("\tsub\t%s, %s\n", fparam, sparam);
			break;
		case OP_DIV:
			printf("\tdiv\t%s, %s\n", fparam, sparam);
			break;
	}
}

void gen_code_write(tree_t *expr) {
	// When generating a call to write, you can assume that it has one parameter,
	// if none, quit. if more, discard them

	// Empty expresssion
	if(expr == NULL) {
		fprintf(stderr, "[Error]: No parameter to write\n");
		exit(-1);
	}

	// gencode the top of the expr_list which is the only parameter
	gen_code_expr(expr);

	// move this value which is now in %rax into a parameter for printf
	printf("\tmovq\t%%rax, %%rsi\n");

	// Push string into register
	printf("\tmovq\t$.LC0, %%rdi\n");

	printf("\tmovq\t$0, %%rax\n");
	
	// Call printf
	printf("\tcall\tprintf\n");
}

void gen_code_read(tree_t *expr) {
	if(expr == NULL) {
		fprintf(stderr, "[Error]: No parameter to function read");
		exit(-1);
	}

	// Load the param's address into %rax
	printf("\tleaq\t%s, %rax\n", get_val(expr));

	printf("\tmovq\t%%rax, %%rsi\n");

	printf("\tmovq\t$.LC1, %%rdi\n");

	printf("\tmovq\t$0, %%rax\n");

	printf("\tcall\t__isoc99_scanf\n");
}

void gen_code_if_then_else(statement_t *stmt) {
    gen_code_expr(stmt->stmt.if_then_else_stmt.tree->left);
    printf("\tcmp\t%s, %s\n", get_val(stmt->stmt.if_then_else_stmt.tree->right), top_reg_stack(reg_stack));

    switch(stmt->stmt.if_then_else_stmt.tree->attribute.bopval) {
		case OP_LT:
			printf("\tjge .L%d\n", label_count);
			break;
		case OP_LE:
			printf("\tjg .L%d\n", label_count);
			break;
		case OP_GT:
			printf("\tjle .L%d\n", label_count);
			break;
		case OP_GE:
			printf("\tjl .L%d\n", label_count);
			break;
		case OP_EQ:
			printf("\tjne .L%d\n", label_count);
			break;
		case OP_NEQ:
			printf("\tje .L%d\n", label_count);
			break;
    }
    gen_code_stmt_list(stmt->stmt.if_then_else_stmt.if_stmt);
    printf("\tjmp .L%d\n", label_count+1);
    printf(".L%d:\n", label_count);
    label_count++;
    gen_code_stmt_list(stmt->stmt.if_then_else_stmt.else_stmt);
    printf(".L%d:\n", label_count);
    label_count++;
}

void gen_code_while(statement_t *stmt) {
	// write jmp to N (ex: .L2)
	printf("\tjmp\t.L%d\n", label_count);
	
	// write N+1 and body of loop
	printf(".L%d:\n", label_count+1);
	gen_code_stmt_list(stmt->stmt.while_stmt.do_stmt);	

	// write N and condition for this loop
	printf(".L%d:\n", label_count);

	char* left = get_val(stmt->stmt.while_stmt.tree->left);
	char* right = get_val(stmt->stmt.while_stmt.tree->right);

	printf("\tcmp\t%s, %s\n", right, left);

	// if the loop check returns true, jump back to N+1
    switch(stmt->stmt.if_then_else_stmt.tree->attribute.bopval) {
        case OP_GT:
            printf("\tjg .L%d\n", label_count+1);
            break;
        case OP_LT:
            printf("\tjl .L%d\n", label_count+1);
            break;
    }
	
}

void gen_code_proc_call(statement_t *stmt) {
	printf("\tmovq\t$0, %%rax\n");
	/* if(stmt->stmt.proc_stmt.proc_expr_list != NULL) { */
	/* 	push_parameters(stmt->stmt.proc_stmt.proc_expr_list); */
	/* } */
	printf("\tcall\t%s\n", stmt->stmt.proc_stmt.ident->name);
}

void gen_code_proc_preamble() {
	printf("\tpushq\t%%rbp\n");
	printf("\tmovq\t%%rsp, %%rbp\n");
	printf("\tsubq\t$16, %%rsp\n");
}

void gen_code_proc_ending() {
	printf("\tleave\n");
	printf("\tret\n");
}

void push_parameters(tree_list_t *list) {
	tree_list_t * loc_list = list;
	tree_t * tree = loc_list->head;
	
	while(tree != NULL) {
		print_tree(tree, 10);
		tree = loc_list->next;
		loc_list->head = loc_list->next;
	}
}

char* get_val(tree_t *tree) {
	char* str = malloc(50 * sizeof(char));
	
	switch(tree->type) {
		case T_INT: 
			sprintf(str, "$%d", tree->attribute.ival);
			break;
		case T_ID:
			sprintf(str, "%d(%%rbp)", -4*(tree->attribute.sval->offset));
			break;
	}

	return str;
}
