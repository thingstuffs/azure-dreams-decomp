#include "common.h"

typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void func_800673A0(Rect *rect, s32 x, s32 width);
extern u8 D_800244B8[][12];

void func_80023578(s16 arg0, s16 arg1, s16 arg2)
{
    Rect rect;
    s32 temp_s3;
    s16 temp_s4;
    s16 temp_v0;
    s32 temp_a0;
    s32 var_a2;
    s32 var_s0;
    s32 temp_v1;

    temp_s4 = arg1 + 0xC;
    temp_s3 = (arg0 * 0x10) + 0x180;
    var_s0 = -1;
    rect.w = 0x10;
    rect.h = 0x20;
    do {
        if ((var_s0 >= 0) || (arg2 != 0)) {
            temp_v1 = D_800244B8[arg0][(temp_s4 + var_s0) % 12];
            temp_a0 = ((2 - var_s0) << 5) - arg2;
            var_a2 = temp_a0 + 0x80;
            rect.x = ((temp_v1 & 3) * 0x10) + 0x180;
            temp_v0 = ((s32) temp_v1 >> 2) << 5;
            rect.y = temp_v0;
            if (temp_a0 < 0) {
                var_a2 = 0x80;
                rect.y = temp_v0 - temp_a0;
                rect.h = temp_a0 + 0x20;
            }
            func_800673A0(&rect, temp_s3, var_a2);
        }
        var_s0 += 1;
    } while (var_s0 < 3);
}
