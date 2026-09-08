#include "common.h"

typedef void (*DispatchFunc)(void *arg0, void *self);

extern DispatchFunc D_800D1638[];

/* Calls the indexed handler with the supplied data and its table entry. */
void func_800B1F10(void *data, s32 handler_index) {
    DispatchFunc *table;
    DispatchFunc *handler_entry;

    table = D_800D1638;
    handler_entry = table + handler_index;
    (*handler_entry)(data, (void *)handler_entry);
}
