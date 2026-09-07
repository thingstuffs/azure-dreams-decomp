#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();

extern s32 D_80024B98[3];
extern s32 D_80025854[3];
extern s32 D_80045C34[3];

void *func_80024D90(void *arg0, s16 arg1) {
    register void *saved_arg0 = arg0;
    register s16 saved_arg1 = arg1;
    register s32 var_s3 = 0;
    register s32 *callback = D_80024B98;
    register u16 *counter_page = (u16 *)0x80020000;
    register s32 var_s4 = -0x400;
    register void *temp_v0;
    register void *temp_s1 ASM_REG("$17");
    register s32 angle;
    register s32 work ASM_REG("$3");
    register void *component;
    register void *temp_a0 ASM_REG("$4");
    register s32 const_400 ASM_REG("$2");

    do {
        temp_v0 = func_8003FC64(0x202);
        if (temp_v0 != NULL) {
            FIELD(temp_v0, s32 *, 0x10) = callback;
            func_8004491C(temp_v0, D_80045C34);
            angle = var_s3 << 8;
            temp_s1 = FIELD(temp_v0, void *, 8);
            work = FIELD(saved_arg0, u16, 2) + (func_80064584(angle) >> 7);
            FIELD(temp_s1, s16, 2) = work;
            work = FIELD(saved_arg0, u16, 6) + (func_800644B8(angle) >> 7);
            FIELD(temp_s1, s16, 6) = work;
            FIELD(temp_s1, s16, 0xA) =
                (s16)(FIELD(saved_arg0, u16, 0xA) - 0x100);
            component = FIELD(temp_v0, void *, 0xC);
            FIELD(component, s16, 0x1C) = 0x800;
            FIELD(component, s16, 0x1E) = 0x1CCC;
            FIELD(component, s32, 0xC) = 0;
            func_8003DB94(component, D_80025854, 0);
            const_400 = 0x400;
            ASM_KEEP(const_400);
            work = counter_page[0x57CC / 2];
            temp_a0 = (u8 *)temp_v0 + 0x20;
            FIELD(component, s16, 0x16) = const_400;
            FIELD(component, s16, 0x18) = var_s4;
            FIELD(temp_a0, s16, 0x24) = var_s3;
            FIELD(temp_a0, s16, 0x14) = saved_arg1;
            FIELD(temp_a0, s16, 0x1E) = (s16)(var_s3 * 2);
            work += 1;
            counter_page[0x57CC / 2] = work;
        }
        var_s3 += 1;
        var_s4 += 0x100;
    } while (var_s3 < 0x10);
    return temp_v0;
}

/* MECHANISM: The 0x38 frame and ten saved roles come from the natural loop lifetimes.
   A short-lived $v0-held 0x400 local plus ASM_KEEP forces retail's li/lhu/addiu/sh order.
   The $s1/$v1/$a0 pins preserve the child, counter, and subobject-base live ranges. */
