// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

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

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
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

    //access second to top eleemnt
    //duplicate element
    //push dup on stack
    //update stack size 
    //hint: use SLIT_NEXT macro to access second-2top elem 
    //2 args: 1st elem of list, name of entries in 
    //int_entry_t struct
}



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