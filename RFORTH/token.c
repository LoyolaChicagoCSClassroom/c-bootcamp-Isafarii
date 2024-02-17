#include "token.h"
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
        return 3;
    }
    else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' ){
        return 2;
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





