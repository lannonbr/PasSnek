#include "statement.h"

#ifndef STMTSTACK_H
#define STMTSTACK_H

typedef struct stmtstck_s {
	statement_t * head;
	struct stmtstck_s * next;
	int id;
} stmt_stack_t;

stmt_stack_t * new_stmt_stack();
statement_t * stmt_pop_stack(stmt_stack_t *head);
stmt_stack_t * stmt_push_stack(int id, stmt_stack_t *head);

#endif
