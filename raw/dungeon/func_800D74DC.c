#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Template0 D_8002E5D8;
extern Vec3 D_8002E5E8;

void func_800DCC3C(u8 *arg0) {
    register u8 *header ASM_REG("$6");
    register s32 i ASM_REG("$7");
    register u8 *page0 ASM_REG("$11");
    register Template0 *src0 ASM_REG("$8");
    register u8 value ASM_REG("$12");
    register u8 *page1 ASM_REG("$10");
    register Vec3 *src1 ASM_REG("$9");
    register s32 offset1 ASM_REG("$5");
    register s32 offset0 ASM_REG("$4");
    register s32 final_base ASM_REG("$2");
    register s32 final_value ASM_REG("$3");

    header = arg0;
    ASM_KEEP(header);
    i = 0;
    ASM_KEEP(i);
    page0 = (u8 *)0x80030000;
    ASM_KEEP(page0);
    src0 = (Template0 *)(page0 - 0x1A28);
    ASM_KEEP(src0);
    value = 4;
    ASM_KEEP(value);
    page1 = (u8 *)0x80030000;
    ASM_KEEP(page1);
    src1 = (Vec3 *)(page1 - 0x1A18);
    ASM_KEEP(src1);
    offset1 = i;
    ASM_KEEP(offset1);

    do {
        offset0 = i * 0x10;
        ASM_KEEP(offset0);
        *(s32 *)(offset0 + *(s32 *)(header + 4)) =
            *(s32 *)(page0 - 0x1A28);
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 4) = src0->unk4;
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 8) = src0->unk8;
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 0xC) = src0->unkC;
        *(u8 *)(offset0 + *(s32 *)(header + 4) + 0xF) = value;
        i++;
        ASM_KEEP(i);
        *(s32 *)(offset1 + *(s32 *)(header + 8)) =
            *(s32 *)(page1 - 0x1A18);
        *(s32 *)(offset1 + *(s32 *)(header + 8) + 4) = src1->y;
        final_base = *(s32 *)(header + 8);
        final_value = src1->z;
        final_base = offset1 + final_base;
        ASM_KEEP(final_base);
        ASM_KEEP(final_value);
        *(s32 *)(final_base + 8) = final_value;
        offset1 += 0xC;
    } while (i < 9);
}

/* MECHANISM: Frameless leaf with pinned header/index/offset roles and two
   separately held 0x80030000 page bases; keep seams derive full bases by addiu.
   Reversed offset+base indexing and a final v0/v1 live-range split close the copy. */
