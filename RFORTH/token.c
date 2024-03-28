#include "token.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "int_stack.h"
// create for: numbers, arith ops( + - * / ); symbols: ( :  ; ); words 
//get the string and identify what string 

token_t* create_token(token_type_t t, const char* s){
    //allocates memory
    token_t* token = (token_t*)malloc(sizeof(token_t));
    //takes t and puts it in the token type field
    //puts stuff in type of token
    token->type=t;
    //puts stuff in text of token 
    token->text=strdup(s);
    return token;
}

token_type_t whatType(char* start){
//get what address is referencing
char ch = *(start); 
if (*(start+1) == '\0'){

    //if its true, then only 1 element because ends at elem 2
    if(ch == ':' || ch == ';' ){
        return 3;//symbol
    }
    else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' ){
        return 2;//operator
    }
}
//assume its word or number
int i = 0;
int num = 1; //initalize check for if a number
while( (ch = *(start+i)) != '\0'){
    //if not a digit (is a word)
    if (!isdigit(ch)){
      num = 0;
      break;
    }
    i++;
}
return num ? NUMBER: WORD;
}

//char* get_next_token(int l, char* cmd){
// token_t* get_next_token(int l, char* cmd){
//     token->l;
// }
// token.c

token_t* get_next_token(char* cmd) {
    if (cmd == NULL) {
        return NULL;
    }
    token_t* new_token = (token_t*)malloc(sizeof(token_t));
    if (new_token == NULL){
        return NULL;
    }
    new_token->type = whatType(cmd);
    //Duplicate
    new_token->text = strdup(cmd);

    if (new_token->text == NULL){
        free(new_token);
        return NULL;
    }
    return new_token;
}

Node *make_node(token_t token){
Node *node = malloc(sizeof(Node));
return node;
}

Node *parse_if(token_t *tokens,int *num_tokens)  {
    Node *if_node=malloc(sizeof(Node));
    if_node->type=IF;
    if_node->condition=make_node(tokens[1]);
    if_node->true_cond=make_node(tokens[3]);
    if_node->false_cond=NULL;

    *num_tokens=5; // Update the number of tokens consumed (e.g., "if", condition, "then", true branch, "then")
    return if_node;
}

void parse_definition(token_t *tokens, int num_tokens, Node *function_node)  {
    // set up function node
    function_node->type=FUNCTION;
    function_node->name=strdup(tokens[1].text);
    function_node->body=malloc(sizeof(token_t)*(num_tokens-4)); // skip function name, ':', and ';'
    function_node->body_length=num_tokens-4;
    for (int i=2;i<num_tokens-2;i++) { // skip ':' and function name; also skip ';' and '\0'
        function_node->body[i-2]=tokens[i];
    }
}
//run the function
void execute_function(const char* name, int_stack_t* stack, Node* functions[], int function_count) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i]->name, name) == 0) {
            // function found, now run
            for (int j = 0; j < functions[i]->body_length; j++) {
                token_t token = functions[i]->body[j];
                switch (token.type) {
                case NUMBER:
                    int_stack_push(stack, atoi(token.text));
                    break;
                case OPERATOR:
                    
                    if (strcmp(token.text, "+") == 0) {
                        int b, a;
                        int_stack_pop(stack, &b);
                        int_stack_pop(stack, &a);
                        int_stack_push(stack, a+b);
                    } else if (strcmp(token.text, "-") == 0) {
                        int b, a;
                        int_stack_pop(stack, &b);
                        int_stack_pop(stack, &a);
                        int_stack_push(stack, a-b);
                    } // more cases/operators?
                    break;
                default:
                    // other types if needed
                    break;
                }
            }
            return;
        }
    }
    printf("No function %s \n", name);
}



void free_node(Node *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < node->count_children; i++) {
        free_node(node->children[i]);
    }
    free(node->name);
    free(node->children);
    free(node);
}




token_t* tokenize(const char* function_definition, int* num_tokens){
    token_t* tokens = malloc(sizeof(token_t)* 100);
    char* token_str = strtok((char*)function_definition," "); //split the spaces
    int count=0;

    while (token_str != NULL && count < 100) {
        tokens[count++] = *create_token(whatType(token_str),token_str);
        token_str = strtok(NULL, " ");
    }

    *num_tokens = count;
    return tokens;
}

void printfToken(token_t* token){
    printf("Token:\n");
    printf("\"");
    char ch;
    for(int i =0; (ch=*(token->text+i))!='\0'; i++){
        printf("%c",ch);
    }
    printf("\"");
    printf("\n Type: ");
    switch(token->type){
        case 1:
            printf("NUMBER");
            break;

        case 2: 
            printf("OPERATION");
            break;
        case 3:
            printf("SYMBOL");
            break;

        case 4:
            printf("WORD");
            break;
    }
    printf("\n");
}





