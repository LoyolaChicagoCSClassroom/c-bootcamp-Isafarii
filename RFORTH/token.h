#ifndef TOKEN_H
#define TOKEN_H
//no include stdio/lib. because its a constructing

#include <stdbool.h>
//forward declare
struct int_stack;
typedef struct int_stack int_stack_t;

//#include "int_stack.h"  

typedef enum{
    //represents token types. these are the 'names'
    NUMBER=1,
    OPERATOR,//2
    SYMBOL,//3
    WORD,//4
    FUNCTION,
    IF
}token_type_t;

token_type_t whatType(char* start);

//makes it get text
typedef struct token_t{
    token_type_t type;
    char* text;
}token_t;


typedef struct Node {
    token_type_t type;   // Add this line
    char* name;
    struct Node *condition;
    struct Node *true_cond;
    struct Node *false_cond;
    struct Node **children;
    int count_children;
    token_t *body;       // Add this line
    int body_length;     // Add this line
} Node;





token_t* tokenize(const char* function_definition,int* num_tokens );

//functions
bool is_function_name(const char* name, Node* functions[], int function_count);
void parse_definition(token_t* tokens, int num_tokens, Node* function_node);
void execute_function(const char* name, int_stack_t* stack, Node* functions[], int function_count);


//make node
Node *make_node(token_t token);

//make token; makes a token. two params: type and input: 
token_t* create_token(token_type_t t, const char* s);

//char* get_next_token(int l, char* cmd);
token_t* get_next_token(char* cmd);

extern void printfToken(token_t* token);
#endif // TOKEN_H


