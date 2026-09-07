#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800198D0();
extern s32 D_80016470;
extern s32 D_80016608;
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017DBC(void)
{
    s32 var_s1;
    s32 var_s3;
    void *var_s0;
    void *var_s2;
    void *var_s4;
    s32 offset;

    if (D_80019BB0 == 2) {
        do { var_s1 = 1; } while (0);
        var_s3 = 0x400;
        var_s4 = &D_80016608;
        var_s2 = var_s4 + 0x14;
        do {
            offset = 0xC;
            var_s0 = (u8 *)&D_80016470 + offset;
        } while (0);
loop_2:
        if (func_800198D0(FIELD(var_s0, s16, 4)) != 0) {
            if (FIELD(var_s0, s32, 8) != 0) {
                FIELD(var_s2, s16, 2) = var_s3;
                if (var_s1 == 1) {
                    FIELD(var_s4, s16, 0xA2) = var_s3;
                    goto block_11;
                }
                FIELD(var_s4, s16, 0xB6) = var_s3;
                goto block_11;
            }
            if (D_80019BB4 == var_s1) {
                FIELD(var_s2, s16, 2) = var_s3;
            }
        }
block_11:
        var_s2 += 0x14;
        var_s1 += 1;
        var_s0 += 0xC;
        if (var_s1 >= 8) {
            return 0;
        }
        goto loop_2;
    }
    return 1;
}
