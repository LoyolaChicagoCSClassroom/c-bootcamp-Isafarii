#include "token.h"
#include "int_stack.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

bool is_function_name(const char* name, Node* functions[], int function_count) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i]->name, name) == 0) {
            return true;
        }
    }
    return false;
}


void parse_definition(token_t* tokens, int num_tokens, Node* function_node) {
    function_node->type = FUNCTION;
    function_node->name = strdup(tokens[0].text); // Use the first token as the function name
    int body_length = num_tokens - 3; // Exclude the function name, ':' symbol, and ';'
    if (body_length > 0) {
        function_node->body = malloc(sizeof(token_t) * body_length);
        function_node->body_length = body_length;
        for (int i = 1; i < num_tokens - 2; i++) { // Start from the second token and exclude the last ';'
            function_node->body[i - 1] = tokens[i];
        }
    } else {
        function_node->body = NULL;
        function_node->body_length = 0;
    }
}





//run the function
void execute_function(const char* name, int_stack_t* stack, Node* functions[], int function_count) {
    printf("Executing function: %s\n", name);
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i]->name, name) == 0) {
            printf("Function found: %s\n", name);
            for (int j = 0; j < functions[i]->body_length; j++) {
                token_t token = functions[i]->body[j];
                printf("Executing token: %s\n", token.text);
                if (strcmp(token.text, "PUSH") == 0 && j + 1 < functions[i]->body_length) {
                    int value = atoi(functions[i]->body[++j].text);
                    int_stack_push(stack, value);
                }
                // Add more operations here as needed
            }
            int_stack_print(stack, stdout); // Print the stack after executing the function
            return;
        }
    }
    printf("No function %s \n", name);
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





