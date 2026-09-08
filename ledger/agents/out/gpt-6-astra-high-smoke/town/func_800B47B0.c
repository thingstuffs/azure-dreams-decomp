#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800D1638[];

/* Dispatches the context to the indexed handler, passing its table entry. */
void func_800B1F10(void *context, s32 handler_index) {
    DispatchFunc *table;
    DispatchFunc *handler_entry;

    table = D_800D1638;
    handler_entry = table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}
