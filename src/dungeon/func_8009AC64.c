#include "common.h"

extern u16 D_8008347E;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A540(s32, u8, u8, s16);
s32 func_8009B25C(void *, u16, u16, s16);
s32 func_800A2CB8(void *, s32);

s32 func_800A03C4(void *arg0, u16 arg1, u16 arg2) {
    u16 *var_fp;
    u16 *var_s7;
    void *temp_s4;
    void *temp_s2;
    u16 temp_s6;
    u16 temp_s5;
    s32 temp_v0;
    s32 var_s3;
    s32 var_s1;

    temp_s2 = arg0;
    temp_s6 = arg1;
    temp_s5 = arg2;
    var_fp = D_8006CCD8;
    var_s7 = D_8006CCE8;
    temp_s4 = *(void **)((s8 *)temp_s2 - 0x14);
    var_s1 = D_8008347E & 7;
    for (var_s3 = 0; var_s3 < 8; var_s3++, var_s1 = (var_s1 + 1) & 7) {
        temp_v0 = func_8009B25C(temp_s2, (temp_s6 + var_fp[var_s1]) & 0xFFFF, (temp_s5 + var_s7[var_s1]) & 0xFFFF, *(s16 *)((s8 *)temp_s2 + 0x88));
        if (temp_v0 != 0 && ((func_800A2CB8(temp_s2, temp_v0) << 16) != 0)) {
            if (((func_8009A540(var_s1, *(u8 *)((s8 *)temp_s4 + 0x24), *(u8 *)((s8 *)temp_s4 + 0x25), (s16)((u16)*(s16 *)((s8 *)temp_s2 + 0x88) - 0x20)) << 16) == 0)) {
                continue;
            }
            temp_s2 = arg0;
            return temp_v0;
        }
    }
    return 0;
}
