#ifndef ENUMS_H
#define ENUMS_H

typedef enum { 
	OP_LT = 0,
	OP_LE = 1,
	OP_GT = 2,
	OP_GE,
	OP_EQ,
	OP_NEQ,
	OP_ADD,
	OP_SUB,
	OP_OR,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_AND,
} binop;

typedef enum {
	OP_NEG = 0,
	OP_NOT = 1
} unaryop;

typedef enum {
	T_BINOP = 0,
	T_UNOP = 1,
	T_REAL = 2,
	T_INT,
	T_ARR_INT,
	T_ARR_REAL,
	T_ID,
	T_OTHER
} type_e;

typedef enum {
	ST_ASSIGN = 0,
	ST_PROC = 1,
	ST_IFTHENELSE = 2,
	ST_WHILE = 3
} state_type_e;

typedef enum {
	S_LEFT = 0,
	S_RIGHT = 1
} side_e;

#endif
