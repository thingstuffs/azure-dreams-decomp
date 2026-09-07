#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_80024694(void) __attribute__((noreturn));
extern void func_800246A4(void) __attribute__((noreturn));
extern s32 func_800A45D8(s32, s32, s16);
extern u16 func_800BCAD0(void *);

extern void func_80024374(void);
extern u8 D_80045340[];
extern u8 D_800DE9D0[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

void func_81862C28(s32 arg0, void *arg1, s32 arg2, u8 *arg3) {
    register void *held_arg1 ASM_REG("$22");
    register s32 held_arg2 ASM_REG("$23");
    s16 temp_s3;
    s16 temp_s4;
    s32 var_a1;
    s32 var_v1;
    register s32 temp_a2 ASM_REG("$6");
    s32 var_s2;
    register void *var_s5 ASM_REG("$21");
    register u8 *page_8007 ASM_REG("$2");
    void *temp_s0;
    void *temp_v0;
    s32 xSum;
    s32 yProduct;
    s32 yOffset;
    s16 zValue;

    held_arg1 = arg1;
    ASM_KEEP_NV(held_arg1);
    held_arg2 = temp_a2;
    temp_a2 <<= 0x10;
    if (temp_a2 == 0) {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != 0) {
            temp_s0 = FIELD(temp_v0, void *, 0xC);
            FIELD(temp_v0, void *, 0x10) = func_80024374;
            FIELD(temp_v0, s32, 0x20) = arg0;
            FIELD(temp_v0, s16, 0x24) = 0;
            FIELD(temp_s0, u8, 0xE) = 0x80;
            FIELD(temp_s0, u8, 0xD) = 0x80;
            FIELD(temp_s0, u8, 0xC) = 0x80;
            func_8003DB94(temp_s0, D_800DE9D0, 0);
            FIELD(temp_s0, s16, 0x1C) = 0x1000;
            FIELD(temp_s0, s16, 0x1E) = 0x3000;
            FIELD(temp_s0, s16, 0x12) = 0x7E0B;
            FIELD(temp_s0, u16, 0x10) |= 0x20;
            FIELD(temp_s0, u16, 0x14) |= 0x10C;
            func_8004491C(temp_v0, D_80045340);
            temp_s0 = FIELD(temp_v0, void *, 8);
            FIELD(temp_s0, u16, 2) = FIELD(held_arg1, u16, 2);
            FIELD(temp_s0, u16, 6) = FIELD(held_arg1, u16, 6);
            FIELD(temp_s0, u16, 0xA) = FIELD(held_arg1, u16, 0xA);
            func_800246A4();
        }
    } else {
        var_s2 = 0;
        page_8007 = (u8 *)0x80070000;
        ASM_KEEP(page_8007);
        var_s5 = page_8007 - 0x3328;
loop_5:
        temp_s0 = arg3 + var_s2;
        if (FIELD(temp_s0, u8, 0) == 0) {
            var_v1 = FIELD(held_arg1, s16, 2);
            if (var_v1 < 0) {
                var_v1 += 0x3F;
            }
            xSum = (var_v1 >> 6) + (*(u16 *)var_s5 * held_arg2);
            yOffset = var_s2 << 1;
            var_a1 = FIELD(held_arg1, s16, 6);
            if (var_a1 < 0) {
                var_a1 += 0x3F;
            }
            yProduct = *(u16 *)((u8 *)D_8006CCE8 + yOffset) * held_arg2;
            zValue = FIELD(held_arg1, s16, 0xA);
            temp_s4 = ((xSum << 0x10) >> 0xA) + 0x20;
            temp_s3 = ((((var_a1 >> 6) + yProduct) << 0x10) >> 0xA) + 0x20;
            if ((func_800A45D8(temp_s4 & 0xFFE0, temp_s3 & 0xFFE0, zValue) << 0x10) != 0) {
                FIELD(temp_s0, u8, 0) = 1;
                func_80024694();
            }
            temp_v0 = func_8003FC64(0x212);
            if (temp_v0 != 0) {
                temp_s0 = FIELD(temp_v0, void *, 0xC);
                FIELD(temp_v0, void *, 0x10) = func_80024374;
                FIELD(temp_v0, s32, 0x20) = arg0;
                FIELD(temp_v0, s16, 0x24) = 0;
                FIELD(temp_s0, u8, 0xE) = 0x40;
                FIELD(temp_s0, u8, 0xD) = 0x40;
                FIELD(temp_s0, u8, 0xC) = 0x40;
                func_8003DB94(temp_s0, D_800DE9D0, 0);
                FIELD(temp_s0, s16, 0x1C) = 0x1000;
                FIELD(temp_s0, s16, 0x1E) = 0x1800;
                FIELD(temp_s0, s16, 0x12) = 0x7E0B;
                FIELD(temp_s0, u16, 0x10) |= 0x20;
                FIELD(temp_s0, u16, 0x14) |= 0x10C;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = FIELD(temp_v0, void *, 8);
                FIELD(temp_s0, s16, 2) = temp_s4;
                FIELD(temp_s0, s16, 6) = temp_s3;
                FIELD(temp_s0, u16, 0xA) = FIELD(held_arg1, u16, 0xA);
                FIELD(temp_s0, u16, 0xA) = func_800BCAD0(temp_s0);
            }
        }
        var_s2 += 1;
        var_s5 += 2;
        if (var_s2 < 8) {
            goto loop_5;
        }
    }
}
