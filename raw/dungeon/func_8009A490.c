#include "common.h"

extern s16 D_8008146E;
extern u8 D_800E2970[];
extern s32 func_8009FCA4(s32 x, s32 y, u8 *record, s32 index);

s32 func_8009FBF0(s32 arg0, s32 arg1) {
    u8 *record;
    s32 index;
    register s32 initial_count ASM_REG("$2");
    register s32 tail_index ASM_REG("$2");
    s32 x;
    s32 y;
    s32 count;

    do {
        initial_count = D_8008146E;
    } while (0);
    ASM_KEEP(initial_count);
    index = 0;
    if (initial_count > 0) {
        x = arg0 & 0xFFFF;
        y = arg1 & 0xFFFF;
        count = initial_count;
        record = D_800E2970;
        do {
            ASM_KEEP(record);
            if (*(s16 *)(record + 10) != 0) {
                u16 x0 = *(u16 *)(record + 0);
                if (x >= x0 - 1 && x0 + *(u16 *)(record + 4) >= x) {
                    u16 y0 = *(u16 *)(record + 2);
                    if (y >= y0 - 1 && y0 + *(u16 *)(record + 6) >= y) {
                        tail_index = (s16)index;
                        ASM_TAILSLOT_PIN(tail_index);
                        return func_8009FCA4(x, y, record, index);
                    }
                }
            }
            index++;
            record += 20;
        } while (index < count);
    }
    return -1;
}

/* MECHANISM: The frameless leaf pins the initial count in $v0 so the blez/a3-zero slot and later $t0 hold match.
   ASM_KEEP(record) prevents the record+6 induction base, retaining direct $a2 field displacements.
   The signed tail-index pin emits the retail sll/sra pair around the sibling j. */
