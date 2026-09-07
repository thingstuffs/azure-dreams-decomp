#include "common.h"

extern s16 D_8008146E;
extern u8 D_800E2970[];
extern s32 func_8009FBE8(u32 x, u32 y, u8 *record, s32 index);

s32 func_8009FB34(s32 arg0, s32 arg1) {
    volatile u8 *record;
    s32 index;
    register s32 initial_count ASM_REG("$2");
    register s32 tail_index ASM_REG("$2");
    register s32 bound ASM_REG("$2");
    s32 count;
    u32 x;
    u32 y;

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
            if ((*(s16 *)(record + 10) != 0) &&
                (x >= *(volatile u16 *)(record + 0)) &&
                ({
                    bound = *(volatile u16 *)(record + 0);
                    bound += *(volatile u16 *)(record + 4);
                    ASM_KEEP(bound);
                    (s32)x < bound;
                }) &&
                (y >= *(volatile u16 *)(record + 2)) &&
                ({
                    bound = *(volatile u16 *)(record + 2);
                    bound += *(volatile u16 *)(record + 6);
                    ASM_KEEP(bound);
                    (s32)y < bound;
                })) {
                tail_index = (s16)index;
                ASM_TAILSLOT_PIN(tail_index);
                return func_8009FBE8(x, y, record, index);
            }
            index++;
            record += 20;
        } while (index < count);
    }
    return -1;
}

/* MECHANISM: The frameless leaf splits the initial count through pinned $v0 and keeps volatile coordinate rereads.
   A pinned $v0 bound accumulator fixes both commutative load roles; the tail pin sinks the index sra into the sibling-j slot.
   ASM_KEEP(record) blocks the record+6 induction base, permitting the lone nonvolatile signed active access to emit lh. */
