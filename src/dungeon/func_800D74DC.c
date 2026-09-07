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
    u8 *header;
    s32 i;
    u8 *page0;
    Template0 *src0;
    u8 value;
    u8 *page1;
    Vec3 *src1;
    register s32 offset1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 offset0;
    register s32 final_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 final_value;

    header = arg0;
    i = 0;
    ASM_KEEP(i);   /* MATCH pin: load-bearing for the whole function shape */
    page0 = (u8 *)0x80030000;
    ASM_KEEP(page0);   /* MATCH pin: load-bearing for the whole function shape */
    src0 = (Template0 *)(page0 - 0x1A28);
    ASM_KEEP(src0);   /* MATCH pin: load-bearing for the whole function shape */
    value = 4;
    ASM_KEEP(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    page1 = (u8 *)0x80030000;
    ASM_KEEP(page1);   /* MATCH pin: retail immediate-load split depends on it */
    src1 = (Vec3 *)(page1 - 0x1A18);
    ASM_KEEP(src1);   /* MATCH pin: retail register colouring depends on it */
    offset1 = i;

    do {
        offset0 = i * 0x10;
        *(s32 *)(offset0 + *(s32 *)(header + 4)) =
            *(s32 *)(page0 - 0x1A28);
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 4) = src0->unk4;
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 8) = src0->unk8;
        *(s32 *)(offset0 + *(s32 *)(header + 4) + 0xC) = src0->unkC;
        *(u8 *)(offset0 + *(s32 *)(header + 4) + 0xF) = value;
        i++;
        *(s32 *)(offset1 + *(s32 *)(header + 8)) =
            *(s32 *)(page1 - 0x1A18);
        *(s32 *)(offset1 + *(s32 *)(header + 8) + 4) = src1->y;
        final_base = *(s32 *)(header + 8);
        final_value = src1->z;
        final_base = offset1 + final_base;
        *(s32 *)(final_base + 8) = final_value;
        offset1 += 0xC;
    } while (i < 9);
}

/* MECHANISM: Frameless leaf with pinned header/index/offset roles and two
   separately held 0x80030000 page bases; keep seams derive full bases by addiu.
   Reversed offset+base indexing and a final v0/v1 live-range split close the copy. */
