#include "common.h"

extern s16 D_800E3CD8[8];
extern void func_8009EEAC(void);
extern void func_8009F3D4(s16 x, s16 y, s32 color, s32 size, s32 count);

void func_8009EF04(void) {
    s16 *record;
    s32 x;
    s32 y;
    s32 count;
    s32 color;

    func_8009EEAC();
    count = 0;
    record = D_800E3CD8;
loop:
    if (record[0] == 2) {
        color = 0x208020;
        ASM_KEEP(color);
        x = record[1];
        y = record[2];
        record += 4;
        count += 1;
        func_8009F3D4(x, y, color, 1, 0);
        if (count < 4) {
            goto loop;
        }
    }
}

/* MECHANISM: The seed already supplied retail's 0x28 frame and s0/s1 lifetimes.
   A named color local plus ASM_KEEP makes the lui/ori pair the earliest fallthrough work,
   filling the conditional delay slot before the halfword loads and loop increment. */
