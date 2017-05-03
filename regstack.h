#ifndef REGSTACK_H
#define REGSTACK_H

typedef struct regstack_s {
	char* head;
	struct regstack_s * next;
} regstack_t;

regstack_t * create_reg_stack();
regstack_t * swap_reg_stack(regstack_t * stack);
char* pop_reg_stack(regstack_t * stack);
regstack_t * push_reg_stack(regstack_t * stack, char* reg);
char* top_reg_stack(regstack_t * stack);

#endif
