/* NOT TREATING NEGATIVE NUMBERS / TREATING ONLY ALPHANUMERIC VARIABLES / TREATING ONLY A SAMPLE OF TYPES AND OPERATORS AND ARITHMETIC */
/* TAKE A FILE THAT CONTAINS LINES WRITTEN IN C / WITH NO HEADERS OR DATASTRCTURES OR FUNCTIONS OR COMMENTS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

Tokens tok[4096];
int cnt=0;
char *p;
Scope *scope_stack = NULL;
AsmVar *var_list = NULL;
int var_count = 0;

void add_asm_var(char *name){
	AsmVar *v = malloc(sizeof(AsmVar));
	v->name = name;
	v->offset = -4 * (var_count + 1);
	v->next = var_list;
	var_list = v;
	var_count++;
}

int find_offset(char *name){
	for (AsmVar *v = var_list; v; v = v->next) if (strcmp(v->name, name) == 0) return v->offset;
	fprintf(stderr, "codegen: unknown variable %s\n", name); return 0;
}

Node *new(What what){
	Node *n = malloc(sizeof(Node));
	n->what = what;
	n->left = NULL;
	n->right = NULL;
	n->else_branch = NULL;
	n->next = NULL;
	n->s = NULL;
	n->len = 0;
	n->val = 0;
	return n;
}

void add(What what, char *s, int len, int val){
	tok[cnt].what = what;
	tok[cnt].s = strndup(s, len);
	tok[cnt].len = len;
	tok[cnt].val = val;
	cnt++;
}

What check(char *s, int len){
	if (len == 2 && strncmp(s, "if", 2) == 0) return TK_IF;
	if (len == 4 && strncmp(s, "else", 4) == 0) return TK_ELSE;
	if (len == 6 && strncmp(s, "printf", 6) == 0) return TK_PRINT;
	if (len == 6 && strncmp(s, "return", 6) == 0) return TK_RETURN;
	if (len == 5 && strncmp(s, "while", 5) == 0) return TK_WHILE;
	if (len == 3 && strncmp(s, "int", 3) == 0) return TK_INT;
	if (len == 4 && strncmp(s, "char", 4) == 0) return TK_CHAR_STR;
	return TK_ID;
}

void lexer(char *f){
	p = f;
	while(*p){
		if(isspace(*p)) {p++; continue;} // skip \n \t \r and space
		if(isalpha(*p)){
			char *s = p;
			while(isalnum(*p)) p++;
			int len = p - s;
			What w = check(s, len);
			add(w, s, len, 0);
			continue;
		}
		if(isdigit(*p)){
			char *end = p;
			long val = strtol(p, &end, 10);
			p = end;
			add(TK_INT_VAL, NULL, 0, (int)(val));
			continue;
		}
		if(*p=='\''){
			p++; char c = *p; p+=2;
			add(TK_CHAR_STR_VAL, NULL, 0, c);
			continue;
		}
		if(*p=='"'){
			p++;
			char *s = p;
			while(*p && *p!='"') p++;
			int len = p - s;
			add(TK_CHAR_STR_VAL, s, len, 0);
			if(*p=='"') p++;
			continue;
		}
		if(*p=='='){
			if(*(p+1)=='=') {p+=2; add(TK_EQ, NULL, 0, 0);}
			else {p++; add(TK_ASSIGN, NULL, 0, 0);}
			continue;
		}
		if(*p=='&' && *(p+1)=='&'){
			add(TK_AND, NULL, 0, 0);
			p+=2; continue;
		}
		if(*p=='|' && *(p+1)=='|'){
			add(TK_OR, NULL, 0, 0);
			p+=2; continue;
		}
		if(*p=='!' && *(p+1)=='='){
			add(TK_NOT_EQ, NULL, 0, 0);
			p+=2; continue;
		}
		if(*p == '<') {add(TK_INF, NULL, 0, 0); p++; continue;}
		if(*p == '>') {add(TK_SUP, NULL, 0, 0); p++; continue;}
		if(*p == '+') {add(TK_PLUS, NULL, 0, 0); p++; continue;}
		if(*p == '-') {add(TK_MINUS, NULL, 0, 0); p++; continue;}
		if(*p == '*') {add(TK_MULT, NULL, 0, 0); p++; continue;}
		if(*p == '/') {add(TK_DIV, NULL, 0, 0); p++; continue;}
		if(*p == '%') {add(TK_MOD, NULL, 0, 0); p++; continue;}
		if(*p == ';') {add(TK_SC, NULL, 0, 0); p++; continue;}
		if(*p == '(') {add(TK_LP, NULL, 0, 0); p++; continue;}
		if(*p == ')') {add(TK_RP, NULL, 0, 0); p++; continue;}
		if(*p == '{') {add(TK_LA, NULL, 0, 0); p++; continue;}
		if(*p == '}') {add(TK_RA, NULL, 0, 0); p++; continue;}
		
		p++;
	}
	add(TK_EOF, NULL, 0, 0);
	cnt = 0;
}

void free_tokens(){
	for(int i = 0; i < cnt; i++) if(tok[i].s) free(tok[i].s);
}

void free_ast(Node *n){
	if(!n) return;
	free_ast(n->left);
	free_ast(n->right);
	free_ast(n->else_branch);
	free_ast(n->next);
	free(n);
}

int accept(What what){
	if(tok[cnt].what == what){
		cnt++;
		return 1;
	}
	return 0;
}

void expect(What what){
    if(tok[cnt].what != what){
        fprintf(stderr, "Parse error: expected %d got %d\n", what, tok[cnt].what);
        exit(1);
    }
    cnt++;
}

Node *parse_expr();

Node *parse_primary(){
	Tokens *t = &tok[cnt];
	if(t->what == TK_INT_VAL){
		Node *n = new(TK_INT_VAL);
		n->val = t->val;
		cnt++;
		return n;
	}
	if(t->what == TK_ID){
		Node *n = new(TK_ID);
		n->s = t->s;
		n->len = t->len;
		cnt++;
		return n;
	}
	if(t->what == TK_CHAR_STR_VAL){
		Node *n = new(TK_CHAR_STR_VAL);
		n->s = t->s;
		n->len = t->len;
		n->val = t->val;
		cnt++;
		return n;
	}
	if(accept(TK_LP)){
		Node *n = parse_expr();
		expect(TK_RP);
		return n;
	}
	fprintf(stderr,"Parse error\n");
	exit(1);
}

Node *parse_mult(){
	Node *left = parse_primary();
	while(1){
		What op;
		if(accept(TK_MULT)) op = TK_MULT;
		else if(accept(TK_DIV)) op = TK_DIV;
		else if(accept(TK_MOD)) op = TK_MOD;
		else break;
		Node *n = new(op);
		n->left = left;
		n->right = parse_primary();
		left = n;
	}
	return left;
}

Node *parse_add(){
	Node *left = parse_mult();
	while(1) {
		What op;
		if(accept(TK_PLUS)) op = TK_PLUS;
		else if(accept(TK_MINUS)) op = TK_MINUS;
		else break;
		Node *n = new(op);
		n->left = left;
		n->right = parse_mult();
		left = n;
	}
	return left;
}

Node *parse_rel(){
	Node *left = parse_add();
	while(1){
		What op;
		if(accept(TK_INF)) op = TK_INF;
		else if(accept(TK_SUP)) op = TK_SUP;
		else break;
		Node *n = new(op);
		n->left = left;
		n->right = parse_add();
		left = n;
	}
	return left;
}

Node *parse_eq(){
	Node *left = parse_rel();
	while(1){
		What op;
		if(accept(TK_EQ)) op = TK_EQ;
		else if(accept(TK_NOT_EQ)) op = TK_NOT_EQ;
		else break;
		Node *n = new(op);
		n->left = left;
		n->right = parse_rel();
		left = n;
	}
	return left;
}

Node *parse_and(){
	Node *left = parse_eq();
	while(accept(TK_AND)){
		Node *n = new(TK_AND);
		n->left = left;
		n->right = parse_eq();
		left = n;
	}
	return left;
}

Node *parse_or(){
	Node *left = parse_and();
	while(accept(TK_OR)){
		Node *n = new(TK_OR);
		n->left = left;
		n->right = parse_and();
		left = n;
	}
	return left;
}

Node *parse_expr() { return parse_or(); }

Node *parse_smt();

Node *parse_print() {
	expect(TK_PRINT);
	expect(TK_LP);
	Node *n = new(TK_PRINT);
	n->left = parse_expr();
	expect(TK_RP);
	expect(TK_SC);
	return n;
}

Node *parse_return() {
	expect(TK_RETURN);
	Node *n = new(TK_RETURN);
	n->left = parse_expr();
	expect(TK_SC);
	return n;
}

Node *parse_block() {
	expect(TK_LA);
	Node *head = NULL;
	Node *last = NULL;
	while(tok[cnt].what != TK_RA && tok[cnt].what != TK_EOF) {
		Node *smt = parse_smt();
		if(!head) {head = smt; last = smt;}
		else {last->next = smt; last = smt;}
	}
	expect(TK_RA);
	Node *n = new(TK_BLOCK);
	n->left = head;
	return n;
}

Node *parse_if(){
	expect(TK_IF);
	expect(TK_LP);
	Node *n = new(TK_IF);
	n->left = parse_expr();
	expect(TK_RP);
	n->right = parse_block();
	if(accept(TK_ELSE)) n->else_branch = parse_block();
	return n;
}

Node *parse_while() {
	expect(TK_WHILE);
	expect(TK_LP);
	Node *n = new(TK_WHILE);
	n->left = parse_expr();
	expect(TK_RP);
	n->right = parse_block();
	return n;
}

Node *parse_decla(){
	What type = tok[cnt].what;
	cnt++;
	Tokens *id = &tok[cnt];
	expect(TK_ID);
	Node *n = new(type);
	n->s = id->s;
	n->len = id->len;
	if(accept(TK_ASSIGN)) n->left = parse_expr();
	expect(TK_SC);
	return n;
}

Node *parse_assign(){
	Tokens *t = &tok[cnt];
	Node *n = new(TK_ASSIGN);
	n->s = t->s;
	n->len = t->len;
	cnt += 2;
	n->left = parse_expr();
	expect(TK_SC);
	return n;
}

Node *parse_expr_smt(){
	Node *n = parse_expr();
	expect(TK_SC);
	return n;
}

Node *parse_smt() {
	if(tok[cnt].what == TK_PRINT) return parse_print();
	if(tok[cnt].what == TK_RETURN) return parse_return();
	if(tok[cnt].what == TK_IF) return parse_if();
	if(tok[cnt].what == TK_WHILE) return parse_while();
	if(tok[cnt].what == TK_LA) return parse_block();
	if(tok[cnt].what == TK_INT || tok[cnt].what == TK_CHAR_STR) return parse_decla();
	if(tok[cnt].what == TK_ID && tok[cnt+1].what == TK_ASSIGN) return parse_assign();
	return parse_expr_smt();
}

Node *parse_start(){
	Node *head = NULL; Node *last = NULL;
	while(tok[cnt].what != TK_EOF){
		Node *smt = parse_smt();
		if(!head) {head = smt; last = smt;}
		else {last->next = smt; last = smt;}
	}
	return head;
}

void push_scope(){
    Scope *s = malloc(sizeof(Scope));
    s->vars = NULL;
    s->next = scope_stack;
    scope_stack = s;
}

void pop_scope(){
    Scope *s = scope_stack;
    scope_stack = s->next;
    Var *v = s->vars;
    while (v) {
        Var *tmp = v;
        v = v->next;
        free(tmp);
    }
    free(s);
}

void add_var(char *name, What type){
    for (Var *v = scope_stack->vars; v; v = v->next) {
        if (strcmp(v->name, name) == 0) {
            fprintf(stderr, "Semantic error: redeclaration of %s\n", name);
            exit(1);
        }
    }
    Var *v = malloc(sizeof(Var));
    v->name = name;
    v->what = type;
    v->next = scope_stack->vars;
    scope_stack->vars = v;
}

What lookup(char *name){
    for (Scope *s = scope_stack; s; s = s->next) {
        for (Var *v = s->vars; v; v = v->next) {
            if (strcmp(v->name, name) == 0) return v->what;
        }
    }
    fprintf(stderr, "Semantic error: undeclared variable %s\n", name);
    exit(1);
}

What check_expr(Node *n) {
    if (!n) return TK_INT;
    switch (n->what) {
        case TK_INT_VAL: return TK_INT;
        case TK_CHAR_STR_VAL: return TK_CHAR_STR;
        case TK_ID: return lookup(n->s);
        case TK_PLUS:
        case TK_MINUS:
        case TK_MULT:
        case TK_DIV:
        case TK_MOD: {
            What L = check_expr(n->left);
            What R = check_expr(n->right);
            if (L != TK_INT || R != TK_INT) {
                fprintf(stderr, "Type error: arithmetic requires int\n");
                exit(1);
            }
            return TK_INT;
        }
        case TK_EQ:
        case TK_NOT_EQ:
        case TK_INF:
        case TK_SUP:
            check_expr(n->left);
            check_expr(n->right);
            return TK_INT;

        case TK_AND:
        case TK_OR:
            if (check_expr(n->left) != TK_INT ||
                check_expr(n->right) != TK_INT) {
                fprintf(stderr, "Type error: logical ops require int\n");
                exit(1);
            }
            return TK_INT;

        default:
            return TK_INT;
    }
}

void check_smt(Node *n){
    if (!n) return;
    switch (n->what) {
        case TK_PRINT:
            check_expr(n->left);
            break;
        case TK_RETURN:
            check_expr(n->left);
            break;
        case TK_INT:
        case TK_CHAR_STR:
            add_var(n->s, n->what);
            if (n->left) {
                What t = check_expr(n->left);
                if (t != n->what) {
                    fprintf(stderr, "Type error: invalid initializer for %s\n", n->s);
                    exit(1);
                }
            }
            break;
        case TK_ASSIGN: {
            What var_type = lookup(n->s);
            What expr_type = check_expr(n->left);
            if (var_type != expr_type) {
                fprintf(stderr, "Type error: cannot assign to %s\n", n->s);
                exit(1);
            }
            break;
        }
        case TK_IF:
            if (check_expr(n->left) != TK_INT) {
                fprintf(stderr, "Type error: if condition must be int\n");
                exit(1);
            }
            push_scope();
            check_smt(n->right);
            pop_scope();
            if (n->else_branch) {
                push_scope();
                check_smt(n->else_branch);
                pop_scope();
            }
            break;
        case TK_WHILE:
            if (check_expr(n->left) != TK_INT) {
                fprintf(stderr, "Type error: while condition must be int\n");
                exit(1);
            }
            push_scope();
            check_smt(n->right);
            pop_scope();
            break;
        case TK_BLOCK:
            push_scope();
            for (Node *s = n->left; s; s = s->next)
                check_smt(s);
            pop_scope();
            break;
        default:
            check_expr(n);
            break;
    }
}

void semantic(Node *root){
    push_scope();
    for (Node *n = root; n; n = n->next) check_smt(n);
    pop_scope();
}

void collect_decls(Node *n){
	for(;n;n=n->next){
		if(n->what == TK_INT || n->what == TK_CHAR_STR) add_asm_var(n->s);
		if(n->what == TK_BLOCK) collect_decls(n->left);
		if(n->what == TK_IF) {
			collect_decls(n->right);
			if (n->else_branch) collect_decls(n->else_branch);
		}
		if(n->what == TK_WHILE) collect_decls(n->right);
	}
}

void gen_expr(Node *n){
	switch(n->what) {
	case TK_INT_VAL:
        	printf("    movl $%d, %%eax\n", n->val);
		break;

	case TK_ID: {
        	int off = find_offset(n->s);
        	printf("    movl %d(%%rbp), %%eax\n", off);
        	break;
	}

	case TK_PLUS:
        	gen_expr(n->left);
        	printf("    pushq %%rax\n");
        	gen_expr(n->right);
        	printf("    movl %%eax, %%ecx\n");
        	printf("    popq %%rax\n");
        	printf("    addl %%ecx, %%eax\n");
        	break;

	case TK_MINUS:
        	gen_expr(n->left);
        	printf("    pushq %%rax\n");
        	gen_expr(n->right);
        	printf("    movl %%eax, %%ecx\n");
        	printf("    popq %%rax\n");
        	printf("    subl %%ecx, %%eax\n");
        	break;

	case TK_MULT:
        	gen_expr(n->left);
        	printf("    pushq %%rax\n");
        	gen_expr(n->right);
        	printf("    movl %%eax, %%ecx\n");
        	printf("    popq %%rax\n");
        	printf("    imull %%ecx, %%eax\n");
        	break;

	case TK_DIV:
        	gen_expr(n->left);
        	printf("    pushq %%rax\n");
        	gen_expr(n->right);
        	printf("    movl %%eax, %%ecx\n");
        	printf("    popq %%rax\n");
        	printf("    cdq\n");
        	printf("    idivl %%ecx\n");
        	break;

	default:
        	printf("    movl $0, %%eax\n");
        	break;
	}
}

void gen_smt(Node *n){
	switch(n->what) {
	case TK_INT:
	case TK_CHAR_STR:
		if(n->left) {
		gen_expr(n->left);
		int off = find_offset(n->s);
		printf("    movl %%eax, %d(%%rbp)\n", off);
		}
		break;

	case TK_ASSIGN: {
		gen_expr(n->left);
		int off = find_offset(n->s);
		printf("    movl %%eax, %d(%%rbp)\n", off);
		break;
	}

	case TK_PRINT:
		if (n->left->what == TK_CHAR_STR_VAL && n->left->s != NULL) {
		printf("    leaq .LCSTR%d(%%rip), %%rsi\n", n->left->val);
		printf("    leaq .LC2(%%rip), %%rdi\n"); 
		printf("    movl $0, %%eax\n");
		printf("    call printf\n");
		break;
		}
		
		if (n->left->what == TK_CHAR_STR_VAL && n->left->s == NULL) {
		gen_expr(n->left);
		printf("    movl %%eax, %%esi\n");
		printf("    leaq .LC1(%%rip), %%rdi\n");
        	printf("    movl $0, %%eax\n");
        	printf("    call printf\n");
        	break;
		}

		gen_expr(n->left);
		printf("    movl %%eax, %%esi\n");
		printf("    leaq .LC0(%%rip), %%rdi\n");
		printf("    movl $0, %%eax\n");
		printf("    call printf\n");
		break;

	case TK_BLOCK:
        	for(Node *s = n->left; s; s = s->next) gen_smt(s);
		break;

	case TK_IF: {
        	int Lelse = var_count + 100;
        	int Lend  = var_count + 200;
        	gen_expr(n->left);
        	printf("    cmpl $0, %%eax\n");
        	printf("    je .L%d\n", Lelse);
        	gen_smt(n->right);
        	printf("    jmp .L%d\n", Lend);
        	printf(".L%d:\n", Lelse);
        	if (n->else_branch) gen_smt(n->else_branch);
        	printf(".L%d:\n", Lend);
        	break;
	}

	case TK_WHILE: {
		int Lstart = var_count + 300;
        	int Lend   = var_count + 400;
        	printf(".L%d:\n", Lstart);
        	gen_expr(n->left);
        	printf("    cmpl $0, %%eax\n");
        	printf("    je .L%d\n", Lend);
        	gen_smt(n->right);
        	printf("    jmp .L%d\n", Lstart);
        	printf(".L%d:\n", Lend);
        	break;
	}

	case TK_RETURN:
        	gen_expr(n->left);
        	printf("    movq %%rbp, %%rsp\n");
        	printf("    popq %%rbp\n");
        	printf("    ret\n");
        	break;

	default:
        	gen_expr(n);
        	break;
	}
}

void gen_program(Node *root){
	collect_decls(root);
	printf("    .text\n");
	printf("    .globl main\n");
	printf("main:\n");
	printf("    pushq %%rbp\n");
	printf("    movq %%rsp, %%rbp\n");
	printf("    subq $%d, %%rsp\n", var_count * 4);
	printf("    .section .rodata\n");
	printf(".LC0:\n");
	printf("    .string \"%%d\"\n");
	printf(".LC1:\n");
	printf("    .string \"%%c\"\n");
	printf(".LC2:\n");
	printf("    .string \"%%s\"\n");
	int str_id = 0;
	for (Node *n = root; n; n = n->next) {
    		if (n->what == TK_PRINT && n->left->what == TK_CHAR_STR_VAL && n->left->s != NULL) {
			printf(".LCSTR%d:\n", str_id);
			printf("    .string \"%.*s\"\n", n->left->len, n->left->s);
			n->left->val = str_id;   // store ID for later
			str_id++;
		}
	}
	printf("    .text\n");
	for (Node *n = root; n; n = n->next) gen_smt(n);
	printf("    movl $0, %%eax\n");
	printf("    movq %%rbp, %%rsp\n");
	printf("    popq %%rbp\n");
	printf("    ret\n");
}

int main(int argc, char *argv[]){
	if(argc < 2) {fprintf(stderr, "no accessible file .c given to compile"); return 1;}
	FILE *file = fopen(argv[1], "r");
	if(!file) {fprintf(stderr, "no accessible file .c given to compile"); return 1;}
	
	//because this lexer reads a char buffer not a FILE *file
	//because else we needed to call fgetc which would result in a way lot more system calls
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	char *buff = malloc(size+1);
	fread(buff, 1, size, file);
	buff[size] = '\0';
	
	lexer(buff);
	//print_tokens();
	Node *root = parse_start();
	//print_ast(root, 0);
	semantic(root);
	gen_program(root);

	free_ast(root);
	free_tokens();
	free(buff);
	fclose(file);
	return 0;	
}
/*
To run the program : 

gcc main.c -o main
./main test.txt > out.s
gcc out.s -o out
./out
echo $?
*/

