#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A5720(s32);
extern s32 func_800A6D30(void);
extern s32 func_800C8500(void *);
extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern s32 D_8008942C[];
extern s32 D_800E196F[];
extern s32 D_800E1987[];
extern s32 D_800E1996[];
extern s32 D_800E19AA[];

u32 func_800C857C(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 temp_a0;

    var_s1 = -1;
    if (func_800C8500(arg1) != 0) {
        if (*(s32 *)((s8 *)arg1 + 0x14) & 0x4000) {
            func_80099844(arg1, &D_800E196F);
        }
        return 0;
    }
    temp_a1 = func_800A6D30() & 0xFFFF;
    temp_a0 = *(u8 *)((s8 *)arg0 + 0x11) >> 2;
    if (*(u8 *)((s8 *)arg0 + 3) != 0) {
        var_v0_2 = temp_a1 % *(u8 *)((s8 *)arg0 + 3) + temp_a0;
    } else {
        var_v0_2 = temp_a0;
    }
    if (var_v0_2 >= 0x30) {
        if (*(s32 *)((s8 *)arg0 + 0x1C) & 0x2000) {
            if (!(*(s32 *)((s8 *)arg1 + 0x1C) & 0x2000)) {
                if ((func_80042900(arg1, 0xC) << 0x10) != 0) {
                    func_80042B68(arg1, 0xC);
                    var_s1 = 0;
                    goto block_success;
                }
                var_s1 = func_800A48F0(arg1, 0xB, 0x10);
                if ((var_s1 << 0x10) < 0) {
                    goto block_error;
                }
                {
                    s32 ret = func_800990FC();
                    void *p;
                    register s32 a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    p = &D_800E1987;
                    ASM_KEEP_NV(p);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    a1 = ret;
                    arg0 = a1;
                    func_80099290(func_80099194(&D_8008942C, func_80099734(arg1, func_80099194(p, a1))));
                    func_800A5720(arg0);
                }
                goto block_success;
            }
        } else if (*(s32 *)((s8 *)arg1 + 0x1C) & 0x2000) {
            if ((func_80042900(arg1, 0xB) << 0x10) != 0) {
                func_80042B68(arg1, 0xB);
                var_s1 = 0;
                goto block_success;
            }
            var_s1 = func_800A48F0(arg1, 0xC, 0x10);
            if ((var_s1 << 0x10) < 0) {
                goto block_error;
            }
            func_80099844(arg1, &D_800E1996);
        }
    }
block_success:
    var_v0 = var_s1 << 0x10;
    if (var_v0 < 0) {
block_error:
        if (*(s32 *)((s8 *)arg1 + 0x14) & 0x4000) {
            func_80099844(arg1, &D_800E19AA);
        }
        var_v0 = var_s1 << 0x10;
    }
    var_v0 = var_s1 << 0x10;
    return (u32) ~(var_v0 >> 0x10) >> 0x1F;
}
