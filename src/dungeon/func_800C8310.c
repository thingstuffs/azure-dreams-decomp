#include "common.h"

extern u8 D_800E3D40[];
extern s32 D_80083460[3];
extern s32 func_80042900(void *, s32);
extern s32 func_8003FA44(s32);
extern void *func_8003FC64(s32);
extern void func_800C5E5C(s32, s32, s16, void *, s32);
extern s32 func_800A56E0(s32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800CD994(void *, s32);
extern u8 D_800CD910[];
extern u8 D_800DF820[];

s32 func_800CDA70(void *arg0) {
    s32 temp_v0;
    s16 var_v1;
    s32 temp_a0;
    s32 var_v0;
    void *temp_s0;
    void *temp_v0_2;

    var_v0 = 1;
    if ((func_80042900(arg0, 0xA) << 0x10) == 0) {
        var_v1 = 0;
loop_2:
        if (*(s8 *)((u8 *)arg0 + ((var_v1 << 0x10) >> 0xF) + 0x2C) != 0) {
            var_v1 += 1;
            if (var_v1 < 4) {
                goto loop_2;
            }
        }
        if (var_v1 >= 4) goto done;
            if (*D_800E3D40 == 0) {
                temp_a0 = func_800A6D30() & 0xFFFF;
                if (*(u8 *)((u8 *)arg0 + 3) != 0) {
                    var_v1 = temp_a0 % *(u8 *)((u8 *)arg0 + 3);
                } else {
                    var_v1 = 0;
                }
            } else {
                var_v1 = 0;
            }
            if (var_v1 < 0x40) {
                temp_s0 = *(void **)((u8 *)arg0 - 0x14);
                if (*(u16 *)((u8 *)temp_s0 + 0x14) & 0x8000) {
                    func_800CD994(arg0, 0x10);
                    return -1;
                }
                var_v0 = 0;
                if (func_8003FA44(2) != 0) {
                    temp_v0_2 = func_8003FC64(2);
                    *(u8 **)((u8 *)temp_v0_2 + 0x10) = D_800CD910;
                    *(void **)((u8 *)temp_v0_2 + 0x20) = arg0;
                    *(s16 *)((u8 *)temp_v0_2 + 0x26) = 0xC;
                    func_800C5E5C(
                        ((*(u8 *)((u8 *)temp_s0 + 0x24)) << 6) | 0x20,
                        ((*(u8 *)((u8 *)temp_s0 + 0x25)) << 6) | 0x20,
                        *(s16 *)((u8 *)arg0 + 0x88), D_800DF820, 0);
                    func_800A56E0(0x613);
                    {
                        u8 *counter_base = (u8 *)D_80083460;
                        (*(u16 *)(counter_base + 0xA))++;
                    }
                    return -1;
                }
                return var_v0;
            }
        if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
            func_800A6508();
        }
done:
        return var_v0;
    }
    return var_v0;
}
