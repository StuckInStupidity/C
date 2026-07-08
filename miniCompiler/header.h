#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	TK_ID,
	TK_ASSIGN, // =
	TK_EQ, // ==
	TK_NOT_EQ, // !=
	TK_INF, // <
	TK_SUP, // >
	TK_AND, // &&
	TK_OR, // ||
	TK_IF,
	TK_ELSE,
	TK_PRINT,
	TK_RETURN,
	TK_WHILE,
	TK_INT,
	TK_INT_VAL,
	TK_CHAR_STR,
	TK_CHAR_STR_VAL,
	TK_PLUS, // +
	TK_MINUS, // -
	TK_MULT, // *
	TK_DIV, // /
	TK_MOD, // %
	TK_SC, // ;
	TK_LP, // (
	TK_RP, // )
	TK_LA, // {
	TK_RA, // }
	TK_BLOCK,  // only used for parser
	TK_EOF
} What;

typedef struct Node Node;

struct Node {
	What what;
	char *s;
	int len;
	int val;
	Node *left;
	Node *right;
	Node *else_branch;
	Node *next;
};

typedef struct {
	What what;
	char *s;
	int len;
	int val;
} Tokens;

typedef struct Var Var;

struct Var {
	char *name;
	What what;
	Var *next;
};

typedef struct Scope Scope;

struct Scope {
	Var *vars;
	Scope *next;
};

typedef struct AsmVar {
	char *name;
	int offset;
	struct AsmVar *next;
} AsmVar;

Node *new(What what);
void add(What what, char *s, int len, int val);
What check(char *s, int len);
void lexer(char *f);
void free_tokens();
void free_ast(Node *n);

int accept(What what);
void expect(What what);

Node *parse_expr();
Node *parse_primary();
Node *parse_mult();
Node *parse_add();
Node *parse_rel();
Node *parse_eq();
Node *parse_and();
Node *parse_or();

Node *parse_smt();
Node *parse_print();
Node *parse_return();
Node *parse_block();
Node *parse_if();
Node *parse_while();
Node *parse_decla();
Node *parse_assign();
Node *parse_expr_smt();
Node *parse_start();

void push_scope();
void pop_scope();
void add_var(char *name, What type);
What lookup(char *name);
What check_expr(Node *n);
void check_smt(Node *n);
void semantic(Node *root);

void add_asm_var(char *name);
int find_offset(char *name);
void gen_smt(Node *n);
void gen_expr(Node *n);
void collect_decls(Node *n);
void collect_decls(Node *n);

void print_tokens();
void indent(int depth);
void print_ast(Node *n, int depth);

#endif
