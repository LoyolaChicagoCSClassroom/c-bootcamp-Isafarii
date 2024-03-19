#ifndef FUNCTION_H
#define FUNCTION_H
#include "token.h"
#include "int_stack.h"
//create a limit for max-functions
//array stores all functions
#define MAX_FUNCTIONS 100


//Putting function in its own file
typedef struct{
    char* name;
    token_t* commands;
    int command_count;
} function_t;


extern function_t function[MAX_FUNCTIONS];
//make count variable
extern int function_count;


//function prototypes or making new function
//finding find function
//run function
extern void def_function(char* name, token_t* commands, int command_count);
extern function_t* find_function(char* name);
extern int run_function(function_t* function, int_stack_t* stk);

#endif //FUNCTION_H
