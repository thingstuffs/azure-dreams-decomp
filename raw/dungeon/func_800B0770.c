#include "common.h"

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_800E3648[];

extern s16 func_800B500C(s32, s32, s16);
extern s32 func_800B5F70(void);

s32 func_800B5ED0(s32 arg0, s32 arg1, u32 arg2, s16 arg3) {
    s32 index;
    u8 *base;
    s32 x;
    s32 y;
    s16 result;
    u8 *table;
    u8 *record;
    u8 flags;

    index = arg2 >> 8;
    base = (u8 *)&D_8006CCD8;
    index &= 0xE;
    x = (*(u16 *)(base + index) + arg0) << 16;
    base = (u8 *)&D_8006CCE8;
    y = (*(u16 *)(base + index) + arg1) << 16;
    result = func_800B500C(x >> 16, y >> 16, arg3);
    if (result >= 0) {
        table = D_800E3648;
        record = table + result * 4;
        flags = record[3];
        if (!(flags & 0x40)) {
            if (flags & 0x80) {
                register s32 tail_result ASM_REG("$2");

                record[3] = flags & 0x7F;
                tail_result = result;
                ASM_TAILSLOT_PIN(tail_result);
                return func_800B5F70();
            }
        }
    }
    return -1;
}

/* MECHANISM: A 24-byte ra-only frame and shared scalar-global base reproduce the
   prologue; shifted s32 x/y lifetimes delay x's sra until both sums are formed.
   The unpinned table keeps symbolic BASE[index] order, while ASM_TAILSLOT_PIN
   carries the s16 result into $v0 in the zero-argument sibling-call delay slot. */
