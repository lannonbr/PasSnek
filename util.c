#include <stdio.h>
#include "util.h"

extern int tab_count;
extern FILE * output;

void print_spaces(int offset) {
	for(int i = 0; i < offset; i++)
		printf(" ");
}

void py_tab() {
	for(int i = 0; i < tab_count; i++) {
		POUT("\t");
	}
}
