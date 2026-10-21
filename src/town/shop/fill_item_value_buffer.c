#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

typedef struct {
    u8 pad[0x40];
    UA32 **items;
    s32 count;
} S_800B52D8;

extern void flag_object_for_removal(void *items);

/* Copy leading item values to the fixed output buffer and zero the remaining slots. */
void fill_item_value_buffer(S_800B52D8 *table, void *unused) {
    UA32 values[64];
    UA32 *item;
    s32 i;
    u8 *page;

    if (table->items != 0) {
        for (i = 0; i < table->count; i++) {
            item = table->items[i];
            if (item == 0) {
                break;
            }
            values[i] = *item;
        }
        page = (u8 *)0x80010000;
        for (i = 0; i < table->count; i++) {
            if (table->items[i] == 0) {
                break;
            }
            ((UA32 *)(page + 0x1F80))[i] = values[i];
        }
        for (; i < table->count; i++) {
            ((s32 *)0x80011F80)[i] = 0;
        }
        flag_object_for_removal(table->items);
    }
}
