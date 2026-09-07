#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800294D0[];

void func_80025850(void *arg0, s32 idx) {
    DispatchFunc *table;
    DispatchFunc *self;

    table = D_800294D0;
    self = table + idx;
    (*self)(arg0, (void *)self);
}
