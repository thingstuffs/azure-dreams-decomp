#include "common.h"

extern s16 D_8008146E;
extern u8 D_800E2970[];

/* Return the first active record containing the coordinates, or -1 if none matches. */
s32 func_8009FBF0(s32 pos_x, s32 pos_y) {
    u8 *record;
    s32 index;
    s32 initial_count;
    s32 result;
    s32 x;
    s32 y;
    s32 count;

    initial_count = D_8008146E;
    index = 0;
    if (initial_count > 0) {
        x = pos_x & 0xFFFF;
        y = pos_y & 0xFFFF;
        count = initial_count;
        record = D_800E2970;
        do {
            {
                register u8 *record_reg ASM_REG("$6") = record;
                ASM_KEEP(record_reg);
                record = record_reg;
            }
            if (*(s16 *)(record + 10) != 0) {
                u16 left = *(u16 *)(record + 0);
                if (x >= left - 1 && left + *(u16 *)(record + 4) >= x) {
                    u16 top = *(u16 *)(record + 2);
                    if (y >= top - 1 && top + *(u16 *)(record + 6) >= y) {
                        result = (s16)index;
                        goto done;
                    }
                }
            }
            index++;
            record += 20;
        } while (index < count);
    }
    result = -1;
done:
    return result;
}
