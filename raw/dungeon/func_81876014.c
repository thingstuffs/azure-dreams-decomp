#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s16 D_80026664;
extern s32 D_800814A0;

void func_81876014(void *arg0, void *arg1, void *arg2) {
    register s16 temp_a0 ASM_REG("$4");
    register s16 temp_a1 ASM_REG("$5");
    register s16 temp_a2 ASM_REG("$6");
    register u16 temp_v0_field ASM_REG("$2");
    register u16 temp_v1_base ASM_REG("$3");
    register s16 temp_v1_field64 ASM_REG("$3");
    register void *temp_v1_data ASM_REG("$3");
    register s32 temp_v0_3 ASM_REG("$2");
    register u16 temp_v0_tail ASM_REG("$2");
    s16 temp_v0_4;
    s32 temp_v0;
    s32 temp_product;
    u16 temp_v1;
    void *temp_s3;

    temp_s3 = FIELD(arg0, void *, 0x4C);
    D_80026664 = 1;
    if (FIELD(temp_s3, s16, 0x9C) == 0x37) {
        FIELD(arg0, u16, 0x50) =
            (u16)((FIELD(arg0, s16, 0xA) *
                   func_80064584(FIELD(arg0, s16, 0xC))) >> 12);
        temp_v0 = func_800644B8(FIELD(arg0, s16, 0xC));
        temp_product = FIELD(arg0, s16, 0xA) * temp_v0;
        FIELD(arg0, u16, 0x60) = 0;
        temp_a0 = (*(volatile u16 *)((u8 *)arg0 + 0x60));
        temp_v0_field = FIELD(arg0, u16, 0x50);
        ASM_KEEP(temp_v0_field);
        FIELD(arg0, u16, 0x62) = temp_a0;
        ASM_KEEP(temp_v0_field);
        temp_v1_base = temp_v0_field;
        ASM_KEEP(temp_v1_base);
        temp_v0_field += 0x10;
        ASM_KEEP(temp_v0_field);
        FIELD(arg0, s16, 0x52) = temp_v0_field;
        ASM_KEEP(temp_v0_field);
        temp_v0_field = temp_v1_base;
        ASM_KEEP(temp_v0_field);
        FIELD(arg0, u16, 0x54) = temp_v1_base;
        ASM_KEEP(temp_v1_base);
        temp_v1_field64 = temp_a0;
        ASM_KEEP(temp_v1_field64);
        temp_v1_field64 += 0x10;
        ASM_KEEP(temp_v1_field64);
        FIELD(arg0, s16, 0x64) = temp_v1_field64;
        ASM_KEEP(temp_v1_field64);
        temp_v0_field += 0x10;
        FIELD(arg0, s16, 0x56) = temp_v0_field;
        temp_v1_data = FIELD(arg0, void *, 0x44);
        ASM_KEEP(temp_v1_data);
        temp_v0_3 = temp_product >> 12;
        FIELD(arg0, s16, 0x58) = temp_v0_3;
        ASM_KEEP(temp_v0_3);
        temp_a0 = temp_v0_3;
        ASM_KEEP(temp_a0);
        temp_a1 = temp_v0_3;
        ASM_KEEP(temp_a1);
        temp_a2 = temp_v0_3;
        ASM_KEEP(temp_a2);
        temp_v0_tail = FIELD(arg0, u16, 0x60);
        FIELD(arg0, s16, 0x5A) = temp_a0;
        FIELD(arg0, s16, 0x5C) = temp_a1;
        FIELD(arg0, s16, 0x5E) = temp_a2;
        ASM_KEEP(temp_v0_tail);
        temp_v0_tail += 0x10;
        FIELD(arg0, s16, 0x66) = temp_v0_tail;
        FIELD(arg1, s32, 0) = FIELD(temp_v1_data, s32, 0);
        FIELD(arg1, s32, 4) = FIELD(FIELD(arg0, void *, 0x44), s32, 4);
        FIELD(arg1, s32, 8) = FIELD(FIELD(arg0, void *, 0x44), s32, 8);
        FIELD(arg2, u8, 0xC) = FIELD(FIELD(arg0, void *, 0x48), u8, 0xC);
        FIELD(arg2, u8, 0xD) = FIELD(FIELD(arg0, void *, 0x48), u8, 0xD);
        FIELD(arg2, u8, 0xE) = FIELD(FIELD(arg0, void *, 0x48), u8, 0xE);
        temp_v1 = FIELD(arg0, s16, 0xC);
        temp_v0_4 = temp_v1 - 0x64;
        FIELD(arg0, s16, 0xC) = temp_v0_4;
        if (temp_v0_4 < 0) {
            FIELD(arg0, s16, 0xC) = temp_v1 + 0xF9C;
        }
        if (FIELD(temp_s3, s16, 0xA) >= 5) {
            goto block_4;
        }
    } else {
block_4:
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
