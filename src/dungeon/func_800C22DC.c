#include "common.h"

extern s16 D_80083780[6];
extern s16 D_800E58F8[];
extern void func_800C77D0();

void func_800C7A3C(volatile u8 *arg0, volatile u8 *arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5) {
    volatile s32 frame_pad[2];
    s32 temp_t0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    s16 *dst;
    s16 *ref;

    temp_t0 = (arg0[0x24] << 6) + 0x20;
    temp_v1 = (arg1[0x24] << 6) + 0x20;
    temp_v1 = temp_v1 - temp_t0;
    temp_v1 = temp_v1 >> 1;
    temp_t0 = temp_t0 + temp_v1;
    temp_v1 = temp_t0;
    ref = D_80083780;
    var_v0 = ref[1] - temp_v1;
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    if (var_v0 < 0xC1) {
        dst = D_800E58F8;
        dst[1] = temp_v1;
        temp_t0 = (arg0[0x25] << 6) + 0x20;
        temp_v1 = (arg1[0x25] << 6) + 0x20;
        temp_v1 = temp_v1 - temp_t0;
        var_v0_2 = (u32)temp_v1 >> 31;
        temp_v1 = temp_v1 + var_v0_2;
        temp_v1 = temp_v1 >> 1;
        temp_t0 = temp_t0 + temp_v1;
        temp_v1 = temp_t0;
        var_v0_2 = ref[3] - temp_v1;
        if (var_v0_2 < 0) {
            var_v0_2 = -var_v0_2;
        }
        if (var_v0_2 < 0xC1) {
            dst[3] = temp_v1;
            dst[5] = arg2 + ((arg3 - arg2) / 2);
            func_800C77D0(0, dst, arg4, arg5);
        }
    }
}
