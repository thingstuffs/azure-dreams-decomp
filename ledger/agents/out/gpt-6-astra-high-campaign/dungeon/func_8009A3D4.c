#include "common.h"

extern s16 D_8008146E;
extern u8 D_800E2970[];

/* Returns the first active rectangle containing the point, or -1 if none does. */
s32 func_8009FB34(s32 point_x, s32 point_y) {
    volatile u8 *record;
    s32 index;
    s32 initial_count;
    register s32 upper_bound ASM_REG("$2");
    s32 count;
    u32 x;
    u32 y;

    initial_count = D_8008146E;
    index = 0;
    if (initial_count > 0) {
        x = point_x & 0xFFFF;
        y = point_y & 0xFFFF;
        count = initial_count;
        record = D_800E2970;
        do {
            ASM_KEEP(record);
            if ((*(s16 *)(record + 10) != 0) &&
                (x >= *(volatile u16 *)(record + 0)) &&
                ({
                    upper_bound = *(volatile u16 *)(record + 0);
                    upper_bound += *(volatile u16 *)(record + 4);
                    (s32)x < upper_bound;
                }) &&
                (y >= *(volatile u16 *)(record + 2)) &&
                ({
                    upper_bound = *(volatile u16 *)(record + 2);
                    upper_bound += *(volatile u16 *)(record + 6);
                    (s32)y < upper_bound;
                })) {
                return (s16)index;
            }
            index++;
            record += 20;
        } while (index < count);
    }
    return -1;
}
