#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D808(); /* extern */
M2C_UNK func_8009D940(); /* extern */
M2C_UNK func_8009DA50();    /* extern */
extern u16 D_80082D08[];
extern s32 D_801007F8[];
extern s32 D_80100900[];

typedef struct S_8009CEE8_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x8];
    s32 * unk_0C;
} S_8009CEE8_0;   /* temp_v1 in func_8009CEE8 */

/* Builds the entry list and processes each entry's items at its coordinates. */
void func_8009CEE8(void) {
    register u16 *call_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 call_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 call_y ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    M2C_UNK setup_a[2];
    M2C_UNK setup_b[2];
    s32 *item_cursor;
    s32 coord_x;
    s32 coord_y;
    void **entry_cursor;
    S_8009CEE8_0 *entry;
    u16 *base;

    base = D_80082D08;
    func_8009D808(base, setup_a, setup_b);
    func_8009D940(setup_a, setup_b, D_80100900, D_801007F8);
    entry_cursor = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
        do {
            entry = *entry_cursor;
            item_cursor = entry->unk_0C;
            if (item_cursor != NULL) {
                coord_x = entry->unk_00;
                coord_y = entry->unk_02;
                while (*item_cursor != 0) {
                    call_base = base;
                    call_x = (s16)coord_x;
                    call_y = (s16)coord_y;
                    func_8009DA50(*item_cursor++, call_base, call_x, call_y);
                }
            }
            entry_cursor = (void **)((s8 *)((void **)((s8 *)entry_cursor + 4)));
        } while (*entry_cursor != NULL);
    }
}

/* MECHANISM: Two sibling 8-byte stack arrays force the retail 0x38 frame and save contract.
   Held D_80082D08 plus the split D_801007F8 call/traversal live ranges recover s4/s0/s1.
   Nested guards keep raw u16 coordinates until the sentinel branch, avoiding two load nops.
   Guarded a1/a2/a3 call-register lives pipeline the exact inner-loop argument/delay order. */
