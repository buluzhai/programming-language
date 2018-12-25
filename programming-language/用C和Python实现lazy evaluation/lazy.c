#include <stdlib.h>
#include <stdio.h>
#include "lazy.h"   // or whatever you named it
// the function to make lazy
int id(int x) {
    // the following puts() gives an obvious indication
    // that this function is being evaluated
    puts("Evaluating id!");
    return x;
}
// create the thunk; when forced, it evaluates id()
void* id_thunk(void *x_vp) {
    int *x = malloc(sizeof(int));
    *x = id(*(int*)x_vp);
    return (void*)x;
}
int main(void) {
    // create a lazily-evaluated call to "id(10)"
    int *ten_arg = malloc(sizeof(int));
    *ten_arg = 10;
    lazy *ten = make_lazy(id_thunk, (void*)ten_arg);
    puts("Evaluating lazy ten:");
    // the first time the lazy value is evaluated,
    // the thunk will be evaluated, which should
    // produce the side-effect of outputting
    // "Evaluating id!" to the console
    int *ten_evaluated = (int*)force(ten);
    printf("Result: %d\n", *ten_evaluated);
    puts("\nEvaluating lazy ten again:");
    // the second evaluation of the lazy value
    // should not cause id() to be run again,
    // so we're expecting to NOT see the
    // "Evaluating id!" message
    ten_evaluated = (int*)force(ten);
    printf("Result: %d\n", *ten_evaluated);
    return 0;
}