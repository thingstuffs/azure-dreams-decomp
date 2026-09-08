#include "common.h"

typedef void (*DispatchFunc)(void *context, void *entry);

extern DispatchFunc D_800D1638[];

/* Calls the indexed handler with the context and its dispatch table entry. */
void func_800B1F10(void *context, s32 index) {
    DispatchFunc *table;
    DispatchFunc *entry;

    table = D_800D1638;
    entry = table + index;
    (*entry)(context, (void *)entry);
}
