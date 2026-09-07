#include "common.h"

typedef struct S_8004FC2C {
    void (*func)(void *self);
} S_8004FC2C;

extern void func_8004FAA4(void *a0);

/* Call the object's callback, then run its follow-up routine. */
void func_8004FC2C(S_8004FC2C *object) {
    object->func(object);
    func_8004FAA4(object);
}
