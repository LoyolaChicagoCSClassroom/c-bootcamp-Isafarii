#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
//initialize count
int function_count = 0;
function_t function[MAX_FUNCTIONS];
int funct_count =0;

void def_function(char* name, token_t* commands, int command_count){
    //if at limit of function size
    if(funct_count >=MAX_FUNCTIONS){
        return;
    }
    //duplicate function attributes into the array
    function[funct_count].name =strdup(name);
    function[funct_count].commands =commands;
    function[funct_count].command_count =command_count;
    function_count++;
}


function_t* find_function(char* name){
    for (int i = 0;i<function_count; i++) {
        if (strcmp(function[i].name, name) == 0) {
            return &function[i];

        }
    }
    //if not found
    return NULL;
}
int run_function(function_t* function, int_stack_t* stk) {
    if (function == NULL) {
        return 0;
    }
    //loop through each command
    for (int i = 0; i < function->command_count; i++){
        token_t* cmd = &(function->commands[i]);
        switch (cmd->type){
            //check different cases of symbols
            case OPERATOR:
                if (strcmp(cmd->text,"+") == 0){
                    int a, b;
                    int_stack_pop(stk, &a);
                    int_stack_pop(stk, &b);
                    int_stack_push(stk, a + b);
                } 
                else if (strcmp(cmd->text, "-") == 0) {
                    int a,b;
                    int_stack_pop(stk, &a);
                    int_stack_pop(stk, &b);
                    int_stack_push(stk, b - a);
                } 
                else if (strcmp(cmd->text, "*") == 0) {
                    int a,b;
                    int_stack_pop(stk, &a);
                    int_stack_pop(stk,&b);
                    int_stack_push(stk, a * b);
                } 
                else if (strcmp(cmd->text,"/") == 0) {
                    int a, b;
                    int_stack_pop(stk, &a);
                    int_stack_pop(stk, &b);
                    if (a == 0){
                        printf("Div 0 error.\n");
                        return 0;
                    }

                    int_stack_push(stk, b/a);
                }
                break;

            case NUMBER:
                int_stack_push(stk,atoi(cmd->text));
                break;
        }
    }
    return 1;
}

void run_command(token_t* tokens, int num_token, int_stack_t* stack){
    for(int i = 0; i < num_token; i++){
        token_t token = tokens[1];
        switch(token.type){
            case NUMBER:
                int_stack_push(stack,atoi(token.text));
                break;
            case OPERATOR:
                break;
            case WORD:
                break;
    }

//add tests
//need to add other types, like: OR NOT IF ELSE etc.
//had a huge linker error problem with run_function because
// of a misplaced paranthesis. hours to figure out..
}
}