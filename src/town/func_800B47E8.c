#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800D1640[];

/* Call the indexed dispatch handler with its table entry. */
void func_800B1F48(void *context, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1640;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}
