#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

typedef struct {
    u8 pad[0x40];
    UA32 **items;
    s32 count;
} S_800B52D8;

extern void func_8004B1A4(void *items);

/* Copy leading item values to the fixed output buffer and zero the remaining slots. */
void func_800B2A38(S_800B52D8 *source, void *unused) {
    register S_800B52D8 *table ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 values[64];
    UA32 *item;
    UA32 *value_write;
    UA32 *value_read;
    u8 *dest_base;
    s32 *zero_write;
    s32 read_index;
    register s32 write_index ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    table = source;
    if (table->items != 0) {
        read_index = 0;
        if (table->count > 0) {
            value_write = values;
        copy_items:
            item = table->items[read_index];
            read_index += 1;
            if (item != 0) {
                *value_write = *item;
                value_write += 1;
                if (read_index < table->count) {
                    goto copy_items;
                }
            }
        }
        write_index = 0;
        if (table->count > 0) {
            value_read = values;
            dest_base = (u8 *)0x80010000;
        write_values:
            if (table->items[write_index] != 0) {
                *(UA32 *)(dest_base + 0x1F80) = *value_read;
                value_read += 1;
                dest_base += 4;
                if (++write_index < table->count) {
                    goto write_values;
                }
            }
            if (write_index < table->count) {
                zero_write = (s32 *)0x80011F80 + write_index;
                while (write_index < table->count) {
                    *zero_write = 0;
                    zero_write += 1;
                    write_index += 1;
                }
            }
        }
        func_8004B1A4(table->items);
    }
}
