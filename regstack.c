#include <stdlib.h>
#include "regstack.h"

regstack_t * create_reg_stack() {
	regstack_t * stack = (regstack_t *) malloc(sizeof(regstack_t));
	
	stack->head = NULL;
	stack->next = NULL;

	return stack;
}

regstack_t * swap_reg_stack(regstack_t * stack) {
	regstack_t * swapped_regs = create_reg_stack();	

	regstack_t * tmp_stack = create_reg_stack();

	while(stack != NULL) {
		tmp_stack = push_reg_stack(tmp_stack, stack->head);
		stack = stack->next;
	}

	return tmp_stack;
}

char* pop_reg_stack(regstack_t * stack) {
	char* reg = stack->head;

	stack = stack->next;

	return reg;
}

regstack_t * push_reg_stack(regstack_t * stack, char* reg) {
	regstack_t * new_stack = create_reg_stack();

	new_stack->head = reg;
	new_stack->next = stack;

	return new_stack;
}

char* top_reg_stack(regstack_t * stack) {
	return stack->head;
}
