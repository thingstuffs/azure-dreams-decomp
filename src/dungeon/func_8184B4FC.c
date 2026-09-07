#include "common.h"

extern s32 func_800644B8(s32);
extern void func_80024930(void *, s32, s32, s32, s32, s32, s32, s32);

s32 func_80024CFC(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_s3;

    var_s3 = *(u8 *)((u8 *)arg0 + 0x10) * 0x10;
    if (var_s3 & 0xFF) {
        var_s3 = 0xFF;
    }
    temp_s1 = ((func_800644B8(*(s16 *)((u8 *)arg0 + 0x10) << 6) >> 4) * 0x140) >> 8;
    temp_s0 = (func_800644B8(*(s16 *)((u8 *)arg0 + 0x10) << 6) * 2) >> 8;
    temp_s0_2 = ((func_800644B8(*(s16 *)((u8 *)arg0 + 0x10) << 6) >> 4) * 0x18) >> 8;
    func_80024930(arg0, arg1, arg2, (s16)(*(u16 *)((u8 *)arg0 + 0x14) << 5), (s16)temp_s1,
                  (s16)temp_s0, 3, 0x40);
    func_80024930(arg0, arg1, arg2, (s16)((-( *(u16 *)((u8 *)arg0 + 0x14) << 0x16)) >> 0x10),
                  (s16)temp_s1, (s16)temp_s0_2, 1, var_s3 & 0xFF);
    return 0;
}
