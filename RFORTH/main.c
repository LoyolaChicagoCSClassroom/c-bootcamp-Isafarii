#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include <string.h>
#include "int_stack.h"


//review below
#include <ctype.h>

#define MAX_FUNCTIONS 100 // If we need this


//assume having function that evaluates a condition
bool conditional(token_t* condition);

int main(){
    
    int_stack_t theStack;//initialize stack
    const int capacity = 10;//init cap of 10 
    int_stack_init(&theStack, capacity);//make stack with cap of 10 for now
    char s[1024];

    Node *functions[MAX_FUNCTIONS]; // Array for functs
    int function_count = 0;


    //do to keep repeating until exit
    do{
        printf("\nType QUIT to exit: \n");
        //printf(""); //in case wants to put 'enter content here: ' 
        fgets(s,1024,stdin); //gets the input
        s[strcspn(s,"\n")]=0;


        char *t=&s[0];
        // ...
        if (t[0]!='\0') {
            token_t *token=create_token(whatType(t),t);
            if (token->type==WORD) {
                // Check if the word is a function name and execute it
                execute_function(token->text,&theStack,functions,function_count);
            } else {
                // Handle other token types (e.g., numbers, operators)
            }
        }


        // function 
        if (strncmp(s, ":", 1) == 0) {
            char *function_definition = strdup(s + 1); // skips ':'
            int num_tokens; //  counting tokens
            token_t *tokens = tokenize(function_definition, &num_tokens); 
            Node *function_node = malloc(sizeof(Node));
            parse_definition(tokens, num_tokens, function_node); // set up function node
            functions[function_count++] = function_node;
            free(function_definition); // clean up
            free(tokens); 
        }

        
        //Variable
        if(strncmp(s,"VAR",3)==0){
            char variable_name[256];
            int variable_value;
            if (sscanf(s, "VAR %s %d", variable_name, &variable_value) == 2) {
                printf("Values: \n Variable name = %s \n Variable value = %d\n", variable_name,variable_value);
                def_variable(variable_name,variable_value);
            } else{
                printf("Invalid variable def\n");
            }
        }
        //Conditional
        // if(strncmp(s,"IF",2)==0){
        //     token_t conditions[MAX_TOKENS];
        //     int conditions_count = 0; 
        //     //continue
        //     char* next_token = strtok(NULL," ");//get the next after "IF"
        //     while(next_token != NULL && strncmp(next_token,"THEN", 4) != 0){
        //         conditions[conditions_count] = create_token(whatType(next_token), next_token);
        //         //get next token
        //         next_token = strtok(NULL, " ");
        //     }
        //     if(next_token == NULL){
        //         printf("Error: Missing THEN in conditional");
        //     }
        //     else{
        //         execute_conditional_block(conditions, conditions_count,&theStack);
        //     }
        // }

        //Condition
        if(strncmp(s,"COND",4)==0){
            char condition_name[256];
            int condition_value;
            if (sscanf(s, "COND %s %d", condition_name, &condition_value) == 2) {
                printf("Conditions: \n condition name = %s \n condition value = %d\n", condition_name,condition_value);
                def_condition(condition_name,condition_value);
            } else{
                printf("Invalid condition def\n");
            }
        }


        //for now: if PUSH's', push to stack
        if(strncmp(s,"PUSH",4)==0){
            //want to make length of strs like 
            //PUSH dynamic; easier to call and change
            char* t = &s[5]; //push_length + 1
            int value; //init some value 
            if(sscanf(t, "%d", &value) == 1){
                int_stack_push(&theStack, value);//push it on stack
                int_stack_print(&theStack, stdout); 
            }
        }
        //else
        if(strncmp(s, "QUIT",4)!= 0){
            char* t = &s[0]; //pointer for s
            int i = 0;
            while(*(t+i) !='\0'){
                if(*(t+i)==' ' || *(t+i) =='\n' || *(t+i) =='\0'){
                    //end of token
                    *(t+i) = '\0'; //end of it
                    //if token isn't empty
                    if(t[0] != '\0'){
                        token_t* token=create_token(whatType(t),t);//create token
                        printfToken(token);
                    }
                    t=t+i+1;//move to start of next token
                    while (*(t) == ' '){
                        t++;
                    }
                    i=-1; //reset iterator
                }
                i++;
            }
            //Observe null terminator
            if(t[0] != '\0'){
                token_t* token = create_token(whatType(t),t);
                printfToken(token);
            }
        }
        if(strncmp(s, "OVER", 4) == 0){
            int_stack_over(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "2OVER",5) ==0){
            int_stack_2over(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "ROT", 3) == 0){
            int_stack_rot(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "SWAP",4) ==0){
            int_stack_swap(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "2SWAP",4) ==0){
        int_stack_2swap(&theStack);
        int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "DUP",3) ==0){
            int_stack_dup(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "2DUP",4) ==0){
            int_stack_2dup(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "ADD",3) ==0){
            int_stack_add(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "SUB",3) ==0){
            int_stack_sub(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "MULT",4) ==0){
            int_stack_mult(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "DIV",3) ==0){
            int_stack_div(&theStack);
            int_stack_print(&theStack, stdout);
        }
        if(strncmp(s, "DROP",4) ==0){
            int_stack_drop(&theStack);
            int_stack_print(&theStack, stdout);
        }


        
        int top_value;
            if(strncmp(s, "POP",3) ==0){
                if(int_stack_pop(&theStack, &top_value) == 1){
                    printf("%d\n",top_value);
                    int_stack_print(&theStack, stdout);

                }
            } 
    } while(strncmp(s, "QUIT", 4) != 0);  
    // Clean up functions
    for (int i = 0; i < function_count; i++) {
        free_node(functions[i]); // Implement free_node to free the memory used by the function node
    } 
    return 0;
}

