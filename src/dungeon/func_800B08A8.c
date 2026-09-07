#include "common.h"

typedef struct {
    s8 unused0;
    u8 active;
    u8 unused2[2];
} Slot;

typedef struct {
    u8 unused0[6];
    u8 x;
    u8 y;
    u8 unused8[0x10];
} Status;

extern Status D_800E39C8[];
extern Slot D_800E3648[];
extern void func_800B5F80(s32 arg0);

void func_800B6008(s32 arg0, s32 arg1) {
    s32 var_s1;
    s16 var_s3;
    s16 var_s4;

    var_s1 = 0;
    var_s4 = arg0;
    var_s3 = arg1;
    do {
        if ((D_800E3648[var_s1].active != 0) &&
            (D_800E39C8[var_s1].x == var_s4) &&
            (D_800E39C8[var_s1].y == var_s3)) {
            func_800B5F80(var_s1);
        }
        var_s1 += 1;
    } while (var_s1 < 0x20);
}
