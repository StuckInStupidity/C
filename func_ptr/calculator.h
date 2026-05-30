#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef int (*operator)(int, int);

enum operation
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
};

#endif /* ! CALCULATOR_H */
