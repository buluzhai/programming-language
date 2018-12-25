#include <stdlib.h>
typedef struct {
    void *val;                  // result, when evaluated
    int evaluated;              // true if thunk has ever been evaluated
    void *(*thunk)(void*);      // deferred computation
    void *args;                 // args to pass to deferred computation
} lazy;
// given a thunk and args to pass to it, creates the lazy type above
lazy *make_lazy(void* (*thunk)(void*), void *args) {
    lazy *l = malloc(sizeof(lazy));
    l->val = NULL;
    l->evaluated = 0;
    l->thunk = thunk;
    l->args = args;
    return l;
}
// force evaluation of the thunk
void *force(lazy *l) {
    if (!l->evaluated) {
        // the thunk will only ever be evaluated once,
        // and only when the evaluation is forced via this function
        l->val = l->thunk(l->args);
        l->evaluated = 1;
    }
    return l->val;
}