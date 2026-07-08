#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_tokens(){
	for (int i = 0; i < cnt; i++) {
		Tokens t = tok[i];
		switch (t.what) {
			case TK_ID:
				printf("[TK_ID](%.*s) ", t.len, t.s); break;

			case TK_ASSIGN:
				printf("[=] "); break;

			case TK_EQ:
				printf("[==] "); break;

			case TK_NOT_EQ:
				printf("[!=] "); break;

			case TK_INF:
				printf("[<] "); break;

			case TK_SUP:
				printf("[>] "); break;

			case TK_AND:
				printf("[&&] "); break;

			case TK_OR:
				printf("[||] "); break;

			case TK_IF:
				printf("[TK_IF] "); break;

			case TK_ELSE:
				printf("[TK_ELSE] "); break;

			case TK_PRINT:
				printf("[TK_PRINT] "); break;

			case TK_RETURN:
				printf("[TK_RETURN] "); break;

			case TK_WHILE:
				printf("[TK_WHILE] "); break;

			case TK_INT:
				printf("[TK_INT] "); break;

			case TK_INT_VAL:
				printf("[TK_INT_VAL](%d) ", t.val); break;

			case TK_CHAR_STR:
				printf("[TK_CHAR_STR] "); break;

			case TK_CHAR_STR_VAL:
				if (t.s) printf("[TK_CHAR_STR_VAL](%.*s) ", t.len, t.s);
				else printf("[TK_CHAR_STR_VAL](%c) ", t.val);
				break;

			case TK_PLUS:
				printf("[+] "); break;

			case TK_MINUS:
				printf("[-] "); break;

			case TK_MULT:
				printf("[*] "); break;

			case TK_DIV:
				printf("[/] "); break;

			case TK_MOD:
				printf("[%%] "); break;

			case TK_SC:
				printf("[;]\n"); break;

			case TK_LP:
				printf("[(] "); break;

			case TK_RP:
				printf("[)] "); break;

			case TK_LA:
				printf("[{]\n"); break;

			case TK_RA:
				printf("[}]\n"); break;

			case TK_EOF:
				printf("[TK_EOF] "); break;

			default:
				break;
		}
	}
	printf("\n");
}

void indent(int depth){
	while(depth--) printf("  ");
}

void print_ast(Node *n, int depth){
	if(!n) return;
	indent(depth);
	switch(n->what){
	case TK_INT_VAL:
		printf("INT %d\n", n->val);
		break;

	case TK_ID:
 		printf("ID %s\n", n->s);
		break;

	case TK_CHAR_STR_VAL:
		printf("STRING\n");
		break;

	case TK_ASSIGN:
		printf("ASSIGN %s\n", n->s);
		break;

	case TK_PRINT:
		printf("PRINT\n");
		break;

	case TK_RETURN:
		printf("RETURN\n");
		break;

	case TK_IF:
		printf("IF\n");
		break;

	case TK_WHILE:
		printf("WHILE\n");
		break;

	case TK_BLOCK:
		printf("BLOCK\n");
		break;

	case TK_INT:
		printf("DECL INT %s\n", n->s);
		break;

	case TK_CHAR_STR:
		printf("DECL CHAR %s\n", n->s);
		break;

	case TK_PLUS:
		printf("+\n");
		break;

	case TK_MINUS:
		printf("-\n");
		break;

	case TK_MULT:
		printf("*\n");
		break;

	case TK_DIV:
		printf("/\n");
		break;

	case TK_MOD:
		printf("%%\n");
		break;

	case TK_EQ:
		printf("==\n");
		break;

	case TK_NOT_EQ:
		printf("!=\n");
		break;

	case TK_INF:
		printf("<\n");
		break;

	case TK_SUP:
		printf(">\n");
		break;

	case TK_AND:
		printf("&&\n");
		break;

	case TK_OR:
		printf("||\n");
		break;

	default:
		printf("%d\n", n->what);
		break;
	}
	print_ast(n->left, depth + 1);
	print_ast(n->right, depth + 1);
	print_ast(n->third, depth + 1);
	print_ast(n->next, depth);
}
