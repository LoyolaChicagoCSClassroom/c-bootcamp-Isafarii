#ifndef TOKEN_H
#define TOKEN_H
//no include stdio/lib. because its a constructing

typedef enum{
    //represents token types. these are the 'names'
    NUMBER=1,
    OPERATOR,//2
    SYMBOL,//3
    WORD//4
}token_type_t;

token_type_t whatType(char* start);

//makes it get text
typedef struct token_t{
    token_type_t type;
    char* text;
}token_t;

//make token; makes a token. two params: type and input: 
token_t* create_token(token_type_t t, const char* s);

//char* get_next_token(int l, char* cmd);
token_t* get_next_token(char* cmd);

extern void printfToken(token_t* token);
#endif



