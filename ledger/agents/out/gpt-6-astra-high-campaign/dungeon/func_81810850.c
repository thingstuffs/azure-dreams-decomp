#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800294D0[];

/* Dispatch the context through the indexed handler, passing its table entry. */
void func_80025850(void *context, s32 handler_index) {
    DispatchFunc *table;
    DispatchFunc *handler_entry;

    table = D_800294D0;
    handler_entry = table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}
