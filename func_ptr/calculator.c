#include "calculator.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b)
{
	return a+b;
}

int sub(int a, int b)
{
	return a-b;
}

int mul(int a, int b)
{
	return a*b;
}

int d(int a, int b)
{
	return a/b;
}

int mod(int a, int b)
{
	return a%b;
}


int calculator(int a, int b, enum operation op)
{
	operator opp[] = {add, sub, mul, d, mod};
	return opp[op](a, b);
}

/*
int compute(int input, int (*executor)(int))
{
    return executor(input);
}

void isa(void){
	printf("Hello Isabelle!\n");
}

void tom(void){
	printf("Hi Tom Nook.\n");
}

void blah(void){
	printf("Good night Blathers!\n");
}

void res(void){
	printf("How are you doing Mr. Resetti?\n");
}

void other(void){
	printf("I don't know you!\n");
}

void (*greet(char *name))(void)
{
	if(name){
	if(strcmp(name, "Isabelle")==0) return isa;
	else if(strcmp(name, "Tom Nook")==0) return tom;
	else if(strcmp(name, "Blathers")==0) return blah;
	else if(strcmp(name, "Mr. Resetti")==0) return res;
	}
	return other;
}
*/