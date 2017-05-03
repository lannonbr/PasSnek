%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "statement.h"
#include "tree.h"
#include "node.h"
#include "symtable.h"
#include "stmtstack.h"
#include "regstack.h"
#include "pygen.h"
#include "util.h"

sym_table_stack_t *top_scope;
node_t *tmp_nodes;
tree_list_t *tmp_tree_list;
stmt_stack_t *stmt_top_scope;
int stmt_scope_id;
int num_registers;
regstack_t * reg_stack;
int label_count;
FILE * output;
int tab_count;
%}

%union {
    int ival;
    float fval;
    int bopval;
    char* sval;
    tree_t *tval;
    node_t *nval;
    type_e tyval;
    statement_t *stval;
    tree_list_t *tlval;
}

%token <ival> INUM
%token <fval> RNUM
%token <sval> IDENT
%token PROGRAM
%token PROCEDURE FUNCTION
%token ARRAY
%token VAR
%token OF
%token INTEGER
%token REAL
%token BBEGIN END
%token DO
%token ASSIGNOP
%token IF THEN ELSE
%token WHILE
%token NOT
%token <bopval> RELOP
%token <bopval> ADDOP
%token <bopval> MULOP
%token DOTDOT

%type <tyval> type
%type <tyval> standard_type

%type <nval> identifier_list

%type <stval> compound_statement
%type <stval> optional_statements
%type <stval> statement_list
%type <stval> statement
%type <stval> procedure_statement

%type <nval> variable

%type <tlval> expression_list

%type <tval> expression
%type <tval> simple_expression
%type <tval> term
%type <tval> factor

%%

start: program;

program: PROGRAM
    IDENT
    '(' identifier_list ')' ';' 
    declarations
    subprogram_declarations
    compound_statement
    {
        /* stmt_list_print($9, 0); */
        /* gen_code_main_preamble(); */
        /* gen_code_stmt_list($9); */
        /* gen_code_main_ending(); */
		py_gen($9);
    }
    '.' { top_scope = pop_stack(top_scope); }
    ;

identifier_list: IDENT
    { 
        node_t * node = sts_insert(top_scope, 0, $1);
        node_t * tmp = tmp_nodes;
        tmp_nodes=node;
        tmp_nodes->next = tmp;

        $$ = tmp_nodes;
    }
    | identifier_list ',' IDENT 
    {
        node_t * node = sts_insert(top_scope, 0, $3);
        node_t * tmp = tmp_nodes;
        tmp_nodes=node;
        tmp_nodes->next = tmp;

        $$ = tmp_nodes;
    }
    ;

declarations: declarations VAR identifier_list ':' type ';'
    {
        node_t * node = tmp_nodes;
        while(node != NULL) {
            node->var_type = $5;
            node = node->next;
        }
    }
    | /* empty */
    ;

/* TODO: Pass size of Array up to declarations field */
type: standard_type { $$ = $1; }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type { $$ = ($8 == T_REAL) ? T_ARR_REAL : T_ARR_INT; }
    ;

standard_type: INTEGER { $$ = T_INT; }
    | REAL { $$ = T_REAL; }
    ;

subprogram_declarations: subprogram_declarations subprogram_declaration ';'
    | /* empty */
    ;

subprogram_declaration: subprogram_head
	declarations
	subprogram_declarations 
	compound_statement
	{
        /* stmt_list_print($4, 0); */
		/* gen_code_proc_preamble(); */
		/* gen_code_stmt_list($4); */
		/* gen_code_proc_ending(); */
		py_gen($4);
		top_scope = pop_stack(top_scope);
	}
    ;

subprogram_head: FUNCTION IDENT arguments ':' standard_type ';'
    | PROCEDURE
	IDENT
	{ 
		node_t* temp = sts_insert(top_scope, 2, $2);
		top_scope = push_stack(top_scope, $2); 
		top_scope->var_count++;
		/* printf("%s:\n", $2); */
	}
	arguments ';'
    ;

arguments: '(' parameter_list ')'
    | /* empty */
    ;

parameter_list: identifier_list ':' type
    | parameter_list ';' identifier_list ':' type
    ;

compound_statement: BBEGIN
    {
        stmt_scope_id++;
        stmt_top_scope = stmt_push_stack(stmt_scope_id, stmt_top_scope);
    }
    optional_statements
    END
    {
        stmt_scope_id--;
        $$ = stmt_pop_stack(stmt_top_scope);
    }
    ;

optional_statements: statement_list
    | /* empty */
    ;

statement_list: statement { stmt_top_scope->head = stmt_list_append(stmt_top_scope->head, $1); }
    | statement_list ';' statement { stmt_top_scope->head = stmt_list_append(stmt_top_scope->head, $3); }
    ;

statement: variable ASSIGNOP expression { $$ = stmt_gen_assign($1, $3); }
    | procedure_statement { $$ = $1; }
    | compound_statement { $$ = $1; }
    | IF expression THEN statement ELSE statement { $$ = stmt_gen_if_then_else($2, $4, $6); }
    | WHILE expression DO statement { $$ = stmt_gen_while($2, $4); }
    ;

variable: IDENT { $$ = sts_global_search(top_scope, $1); /* printf("Assign to var\n"); */ }
    | IDENT '[' expression ']' { printf("Assign to array index\n"); }
    ;

procedure_statement: IDENT { $$ = stmt_gen_proc(sts_global_search(top_scope, $1), NULL); }
    | IDENT '(' expression_list ')' { $$ = stmt_gen_proc(sts_global_search(top_scope, $1), $3); tmp_tree_list = NULL; }
    ;

expression_list: expression
    {
        if(tmp_tree_list == NULL) {
            tmp_tree_list = create_tree_list($1);
	    $$ = tmp_tree_list;
        } else {
            tmp_tree_list = tree_list_insert(tmp_tree_list, $1);
	    $$ = tmp_tree_list;
        }
    }
    | expression_list ',' expression
    {
        if(tmp_tree_list == NULL) {
            tmp_tree_list = create_tree_list($3);
	    $$ = tmp_tree_list;
        } else {
            tmp_tree_list = tree_list_insert(tmp_tree_list, $3);
	    $$ = tmp_tree_list;
        }
    }
    ;

expression: simple_expression { $$ = $1; /* print_tree($$, 0); */ }
    | simple_expression RELOP simple_expression { $$ = gen_binop($2, $1, $3); $$->leaf = 0; $1->side = S_LEFT; $3->side = S_RIGHT; }
    ;

simple_expression: term { $$ = $1; }
    | ADDOP term { $$ = gen_unaryop($1, $2); }
    | simple_expression ADDOP term { $$ = gen_binop($2, $1, $3); $1->side = S_LEFT; $3->side = S_RIGHT; $$->leaf = 0; }
    ;

term: factor { $$ = $1; }
    | term MULOP factor { $$ = gen_binop($2, $1, $3); $1->side = S_LEFT; $3->side = S_RIGHT; }
    ;

factor: IDENT { $$ = gen_ident(sts_global_search(top_scope, $1)); $$->side = S_LEFT; $$->leaf = 1; }
    | IDENT '(' expression_list ')' { printf("[Parser] Function Call\n"); $$ = gen_tree(); tmp_tree_list = NULL;}
    | IDENT '[' expression ']' { printf("[Parser] Array Access\n"); $$ = gen_tree(); }
    | INUM { $$ = gen_int($1); $$->leaf = 1; $$->side = S_LEFT; }
    | RNUM { $$ = gen_real($1); $$->leaf = 1; $$->side = S_LEFT; }
    | '(' expression ')' { $$ = $2; }
    | NOT factor { $$ = gen_tree(); }
    ;

%%

int main() {
    top_scope = NULL;
    tmp_nodes = NULL;
    tmp_tree_list = NULL;
    stmt_top_scope = NULL;
    stmt_scope_id = 0;
	num_registers = 8;
	reg_stack = push_reg_stack(NULL, "%r15");
	reg_stack = push_reg_stack(reg_stack, "%r14");
	reg_stack = push_reg_stack(reg_stack, "%r13");
	reg_stack = push_reg_stack(reg_stack, "%r12");
	reg_stack = push_reg_stack(reg_stack, "%r11");
	reg_stack = push_reg_stack(reg_stack, "%r10");
	reg_stack = push_reg_stack(reg_stack, "%r9");
	reg_stack = push_reg_stack(reg_stack, "%r8");
	reg_stack = push_reg_stack(reg_stack, "%rdi");
	reg_stack = push_reg_stack(reg_stack, "%rsi");
	reg_stack = push_reg_stack(reg_stack, "%rdx");
	reg_stack = push_reg_stack(reg_stack, "%rcx");
	reg_stack = push_reg_stack(reg_stack, "%rbx");
	reg_stack = push_reg_stack(reg_stack, "%rax");
	label_count = 2;
	tab_count = 0;
    
	top_scope = push_stack(top_scope, "main");

	/* gen_code_io_strings(); */

	output = fopen("pyout.py", "w");

    yyparse();

	fclose(output);
}
