#include "common.h"

typedef void (*DispatchFunc)(void *context, void *self);

extern DispatchFunc D_800D1640[];

/* Call the indexed dispatch handler with its table entry. */
void dispatch_indexed_handler_alt(void *context, s32 handler_index) {
    DispatchFunc *dispatch_table;
    DispatchFunc *handler_entry;

    dispatch_table = D_800D1640;
    handler_entry = dispatch_table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}
