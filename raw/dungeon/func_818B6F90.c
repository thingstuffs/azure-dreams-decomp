#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80083160[];
extern s16 func_80066460(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80065590(
    void *arg0, void *arg1, void *arg2, void *arg3,
    void *arg4, void *arg5, void *arg6, void *arg7,
    void *arg8, void *arg9);

s32 func_818B6F90(s32 arg0, u8 *arg1)
{
    u8 *base;
    u8 *packet;
    u8 *scratch;
    s32 xpos;
    s32 shade;
    register s16 tpage ASM_REG("$2");
    u32 *ot;
    u32 *ot2;
    u32 index;
    u32 index2;
    u32 otword;
    u8 *a70;
    u8 *a74;
    u8 *a78;
    u8 *a7C;
    u8 *a08;
    u8 *a0C;

    scratch = (u8 *)0x1F800000;
    base = *(u8 **)D_80083160;
    FIELD(scratch, u8 *, 0x00) = base + 0xB0;
    packet = FIELD(base, u8 *, 0x8D0);
    FIELD(base, u8 *, 0x8D0) = packet + 0x34;
    FIELD(packet, u8, 0x03) = 0x0C;
    FIELD(packet, u8, 0x07) = 0x3E;

    tpage = func_80066460(0, 3, 0x300, 0x100);
    xpos = (arg0 << 16) >> 13;
    xpos += 0x80;
    a70 = scratch + 0x70;
    a74 = scratch + 0x74;
    a78 = scratch + 0x78;
    a7C = scratch + 0x7C;
    a08 = scratch + 0x08;
    a0C = scratch + 0x0C;

    FIELD(packet, s16, 0x1A) = tpage;
    tpage = 0x7DCF;
    shade = 0x40;
    ASM_KEEP_NV(shade);
    FIELD(packet, s16, 0x0E) = tpage;
    FIELD(packet, u8, 0x18) = xpos | 7;
    FIELD(packet, u8, 0x24) = xpos | 7;
    FIELD(packet, u8, 0x0C) = xpos;
    FIELD(packet, u8, 0x0D) = shade;
    FIELD(packet, u8, 0x19) = shade;
    FIELD(packet, u8, 0x25) = 0x7F;
    FIELD(packet, u8, 0x30) = xpos;
    FIELD(packet, u8, 0x31) = 0x7F;
    FIELD(packet, u8, 0x04) = 0;
    FIELD(packet, u8, 0x05) = 0;
    FIELD(packet, u8, 0x06) = 0;
    FIELD(packet, u8, 0x10) = 0;
    FIELD(packet, u8, 0x11) = 0;
    FIELD(packet, u8, 0x12) = 0;

    FIELD(packet, u8, 0x1C) = FIELD(arg1, u8, 0x0C);
    FIELD(packet, u8, 0x1D) = FIELD(arg1, u8, 0x0D);
    FIELD(packet, u8, 0x1E) = FIELD(arg1, u8, 0x0E);
    FIELD(packet, u8, 0x28) = FIELD(arg1, u8, 0x0C);
    FIELD(packet, u8, 0x29) = FIELD(arg1, u8, 0x0D);
    FIELD(packet, u8, 0x2A) = FIELD(arg1, u8, 0x0E);

    FIELD(scratch, s16, 0x10) = FIELD(scratch, s32, 0x30) >> 16;
    FIELD(scratch, s16, 0x18) = FIELD(scratch, s32, 0x40) >> 16;
    FIELD(scratch, s16, 0x20) = FIELD(scratch, s32, 0x50) >> 16;
    FIELD(scratch, s16, 0x28) = FIELD(scratch, s32, 0x60) >> 16;

    FIELD(scratch, s16, 0x12) = FIELD(scratch, s32, 0x34) >> 16;
    FIELD(scratch, s16, 0x1A) = FIELD(scratch, s32, 0x44) >> 16;
    FIELD(scratch, s16, 0x22) = FIELD(scratch, s32, 0x54) >> 16;
    FIELD(scratch, s16, 0x2A) = FIELD(scratch, s32, 0x64) >> 16;

    FIELD(scratch, s16, 0x14) = FIELD(scratch, s32, 0x38) >> 16;
    FIELD(scratch, s16, 0x1C) = FIELD(scratch, s32, 0x48) >> 16;
    FIELD(scratch, s16, 0x24) = FIELD(scratch, s32, 0x58) >> 16;
    FIELD(scratch, s16, 0x2C) = FIELD(scratch, s32, 0x68) >> 16;

    FIELD(scratch, volatile s32, 0x04) = func_80065590(
        scratch + 0x10, scratch + 0x18, scratch + 0x20, scratch + 0x28,
        a70, a74, a78, a7C,
        a08, a0C);

    FIELD(packet, u16, 0x08) = FIELD(scratch, u16, 0x70);
    FIELD(packet, u16, 0x0A) = FIELD(scratch, u16, 0x72);
    FIELD(packet, u16, 0x14) = FIELD(scratch, u16, 0x74);
    FIELD(packet, u16, 0x16) = FIELD(scratch, u16, 0x76);
    FIELD(packet, u16, 0x20) = FIELD(scratch, u16, 0x78);
    FIELD(packet, u16, 0x22) = FIELD(scratch, u16, 0x7A);
    FIELD(packet, u16, 0x2C) = FIELD(scratch, u16, 0x7C);
    FIELD(packet, u16, 0x2E) = FIELD(scratch, u16, 0x7E);

    index = FIELD(scratch, volatile u32, 0x04);
    if (index < 0x1E0) {
        ot = FIELD(scratch, u32 * volatile, 0x00);
        otword = ot[index];
        FIELD(packet, u32, 0x00) =
            (FIELD(packet, u32, 0x00) & 0xFF000000) |
            (otword & 0x00FFFFFF);
        index2 = FIELD(scratch, volatile u32, 0x04);
        ot2 = FIELD(scratch, u32 * volatile, 0x00);
        ot2[index2] =
            (ot2[index2] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}
