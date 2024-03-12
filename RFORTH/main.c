#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <string.h>
#include "int_stack.h"

//review below
#include <ctype.h>

int main(){
    
    int_stack_t theStack;//initialize stack
    const int capacity = 10;//init cap of 10 
    int_stack_init(&theStack, capacity);//make stack with cap of 10 for now

    char s[1024];
    //do to keep repeating until exit
    do{
        printf("\nType QUIT to exit: \n");
        //printf(""); //in case wants to put 'enter content here: ' 
        fgets(s,1024,stdin); //gets the input

        s[strcspn(s,"\n")]=0;

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
                    i=-1; //reset iterator
                }
                i++;
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
    return 0;
}

