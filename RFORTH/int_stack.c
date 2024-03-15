// int_stack.c
#include "int_stack.h"
#include <stdlib.h>
#include <stdio.h>
//review below
#include <string.h>

condition conditions[MAX_CONDITIONS];
int condition_count = 0;

Variable variables[MAX_VARIABLES];
int variable_count = 0;
//review above


void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}
int int_stack_2swap(int_stack_t *stk) {
    if (stk->size < 4)
        return 0;
    int top_value, second_value,third_value,forth_value; // ;)
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);
    int_stack_pop(stk, &third_value);
    int_stack_pop(stk, &forth_value);
    int_stack_push(stk, second_value);
    int_stack_push(stk, top_value);
    int_stack_push(stk, forth_value);
    int_stack_push(stk, third_value);
    return 1;
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

int int_stack_rot(int_stack_t *stk){
    //takes the third to last element, puts it at the front
    if (stk->size <3){
        printf("ROT: Not enough elemts.\n");
        return 0; //fail
    }
    int_entry_t *thirdElem = SLIST_FIRST(&stk->head);
    thirdElem = SLIST_NEXT(thirdElem, entries);
    thirdElem = SLIST_NEXT(thirdElem, entries);

    int third_value = thirdElem->value;
    SLIST_REMOVE(&stk->head, thirdElem, int_entry, entries);
    free(thirdElem);
    stk->size--;

    return int_stack_push(stk,third_value);

}
int int_stack_drop(int_stack_t *stk) {
    if(stk->size < 1){
        printf("DROP: Stack is empty.\n");
        return 0; 
    }
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    SLIST_REMOVE_HEAD(&stk->head,entries);
    free(entry);
    stk->size--;
    return 1;
}
int int_stack_2drop(int_stack_t *stk){
    if(stk->size <2)
        return 0;
    int_stack_drop(stk);
    return int_stack_drop(stk);
}

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}
int int_stack_2dup(int_stack_t *stk) {
    if (stk->size < 2){
        printf("Not enough elemts.\n");
        return 0;
}
    int top_value;
    int second_top_value;
    int_stack_top(stk, &top_value);
    int_entry_t *secondElem = SLIST_NEXT(SLIST_FIRST(&stk->head), entries);
    second_top_value = secondElem->value;
    int_stack_push(stk,second_top_value);
    return int_stack_push(stk,top_value);
}

int int_stack_sub(int_stack_t *stk){
    if(stk->size <2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk,next_to_top_value-top_value);
}
int int_stack_mult(int_stack_t *stk){
    if(stk->size<2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk,&next_to_top_value);
    return int_stack_push(stk,top_value * next_to_top_value);
}
int int_stack_div(int_stack_t *stk){
    if(stk->size <2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    //case for divide by zero error
    if (top_value==0){
        printf("Error. Division by zero.\n");
        return 0;
    }
    return int_stack_push(stk,next_to_top_value/top_value);
}
int int_stack_over(int_stack_t *stk){
    //check stack size:
    // """: The operation first checks if there are 
    // at least two elements on the stack because it 
    // needs to access the second-to-top element. If 
    // there are fewer than two elements, the operation 
    // cannot proceed and should indicate an error or failure."""
    if (stk->size <2){
        printf("OVER: Not enough elemts.\n");
        return 0; //meaning error fail
    }
    int_entry_t *secondElem = SLIST_NEXT(SLIST_FIRST(&stk->head), entries);
    if(secondElem){
        return int_stack_push(stk, secondElem->value); //success if push is 1

    }
    return 0; //else fail
}
int int_stack_2over(int_stack_t *stk) {
    if (stk->size < 4) {
        printf("2OVER: Not enough elements.\n");
        return 0; // Error: not enough elements
    }
    int_entry_t *top = SLIST_FIRST(&stk->head);
    int_entry_t *second = SLIST_NEXT(top, entries);
    int_entry_t *third = SLIST_NEXT(second, entries);
    int_entry_t *fourth = SLIST_NEXT(third, entries);
    int_stack_push(stk, third->value);

    return int_stack_push(stk, second->value);
}

//review below
void def_variable(char* name, int value){
    variables[variable_count].name = strdup(name);
    variables[variable_count].value = value;
    variable_count++;
}

int def_variable_value(char* name){
    for (int i = 0; i < variable_count; i++){
        if(strcmp(variables[i].name,name)==0){
            return variables[i].value;
        }
    }
    printf("No variable %s\n",name);
    return 0;
}



void def_condition(char* name, int value){
    conditions[condition_count].name = strdup(name);
    conditions[condition_count].value = value;
    condition_count++;
}

int def_condition_value(char* name){
    for (int i = 0; i < condition_count; i++){
        if(strcmp(conditions[i].name,name)==0){
            return conditions[i].value;
        }
    }
    printf("No condition %s\n",name);
    return 0;
}


//review above


void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}