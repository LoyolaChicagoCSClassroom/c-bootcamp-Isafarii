#ifndef TOKEN_H
#define TOKEN_H
//no include stdio/lib. because its a constructing

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
token_type_t type;
char* name;
struct Node *condition;
struct Node *true_cond;
struct Node *false_cond;
struct Node **children;
int count_children;
token_t *body; // array of tokens 
int body_length; 
}Node;


token_t* tokenize(const char* function_definition,int* num_tokens );
void parse_definition(token_t *tokens,int num_tokens,Node *function_node);
void free_node(Node *node);


//make node
Node *make_node(token_t token);

//make token; makes a token. two params: type and input: 
token_t* create_token(token_type_t t, const char* s);

//char* get_next_token(int l, char* cmd);
token_t* get_next_token(char* cmd);

extern void printfToken(token_t* token);
#endif



