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

void func_800B2A38(S_800B52D8 *arg0, void *arg1) {
    register S_800B52D8 *obj ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 scratch[64];
    UA32 *item;
    UA32 *scratch_ptr;
    UA32 *scratch_ptr_2;
    u8 *out_ptr;
    s32 *zero_ptr;
    s32 i;
    register s32 i2 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    obj = arg0;
    if (obj->items != 0) {
        i = 0;
        if (obj->count > 0) {
            scratch_ptr = scratch;
        loop_3:
            item = obj->items[i];
            i += 1;
            if (item != 0) {
                *scratch_ptr = *item;
                scratch_ptr += 1;
                if (i < obj->count) {
                    goto loop_3;
                }
            }
        }
        i2 = 0;
        if (obj->count > 0) {
            scratch_ptr_2 = scratch;
            out_ptr = (u8 *)0x80010000;
        loop_8:
            if (obj->items[i2] != 0) {
                *(UA32 *)(out_ptr + 0x1F80) = *scratch_ptr_2;
                scratch_ptr_2 += 1;
                out_ptr += 4;
                if (++i2 < obj->count) {
                    goto loop_8;
                }
            }
            if (i2 < obj->count) {
                zero_ptr = (s32 *)0x80011F80 + i2;
                while (i2 < obj->count) {
                    *zero_ptr = 0;
                    zero_ptr += 1;
                    i2 += 1;
                }
            }
        }
        func_8004B1A4(obj->items);
    }
}
