#include "modules/dungeon_ovl_1830850.h"

void inventory_dispatch_indexed_handler(void *context, s32 handler_index) {
    DispatchFunc *table;
    DispatchFunc *handler_entry;

    table = D_800294D0;
    handler_entry = table + handler_index;
    (*handler_entry)(context, (void *)handler_entry);
}
