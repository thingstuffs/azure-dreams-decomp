#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800D1638[];

void func_800B1F10(void *arg0, s32 idx) {
    DispatchFunc *table;
    DispatchFunc *self;

    table = D_800D1638;
    self = table + idx;
    (*self)(arg0, (void *)self);
}
