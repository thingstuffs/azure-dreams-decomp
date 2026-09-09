#include "common.h"

extern s16 D_8008146E;
extern u8 D_800E2970[];

s32 func_8009FBF0(s32 arg0, s32 arg1) {
    u8 *record;
    s32 index;
    s32 initial_count;
    s32 tail_index;
    s32 x;
    s32 y;
    s32 count;

    do {
        initial_count = D_8008146E;
    } while (0);
    index = 0;
    if (initial_count > 0) {
        x = arg0 & 0xFFFF;
        y = arg1 & 0xFFFF;
        count = initial_count;
        record = D_800E2970;
        do {
            {
                /* MATCH: Keep the record in retail's $a2 without pinning its address materialization. */
                register u8 *record_reg ASM_REG("$6") = record;
                ASM_KEEP(record_reg);
                record = record_reg;
            }
            if (*(s16 *)(record + 10) != 0) {
                u16 x0 = *(u16 *)(record + 0);
                if (x >= x0 - 1 && x0 + *(u16 *)(record + 4) >= x) {
                    u16 y0 = *(u16 *)(record + 2);
                    if (y >= y0 - 1 && y0 + *(u16 *)(record + 6) >= y) {
                        tail_index = (s16)index;
                        goto done;
                    }
                }
            }
            index++;
            record += 20;
        } while (index < count);
    }
    tail_index = -1;
done:
    ASM_SCHED_BARRIER(); /* MATCH: Keep the successful lookup and miss on one shared epilogue. */
    return tail_index;
}

/* MECHANISM: The frameless leaf pins the initial count in $v0 so the blez/a3-zero slot and later $t0 hold match.
   ASM_KEEP(record) prevents the record+6 induction base, retaining direct $a2 field displacements.
   The signed tail-index pin emits the retail sll/sra pair around the sibling j. */
