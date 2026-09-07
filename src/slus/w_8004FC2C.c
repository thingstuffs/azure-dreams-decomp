#include "common.h"

/* Vtable-style dispatch: call the object's first function-pointer member with
 * itself as the argument, then call a fixed follow-up routine on the same
 * object. */
typedef struct S_8004FC2C {
    void (*func)(void *self);
} S_8004FC2C;

extern void func_8004FAA4(void *a0);

void func_8004FC2C(S_8004FC2C *a0) {
    a0->func(a0);
    func_8004FAA4(a0);
}
