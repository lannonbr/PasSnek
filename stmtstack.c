#include <stdio.h>
#include <stdlib.h>
#include "stmtstack.h"
#include "pascal.tab.h"

extern stmt_stack_t *stmt_top_scope;

// Create a new scope on the statement stack
stmt_stack_t * new_stmt_stack() {
	stmt_stack_t * stack = (stmt_stack_t*) malloc(sizeof(stmt_stack_t));

	stack->head = NULL;
	stack->next = NULL;

	return stack;
}

// Pop the top scope and return the list inside the scope
statement_t * stmt_pop_stack(stmt_stack_t *head) {
	statement_t *head_stmt = head->head;
	stmt_top_scope = head->next;
	return head_stmt;
}

stmt_stack_t * stmt_push_stack(int id, stmt_stack_t *head) {
	stmt_stack_t * new_stack = new_stmt_stack();
	new_stack->next = head;
	new_stack->id = id;
	return new_stack;
}
