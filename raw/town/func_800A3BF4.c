#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define SCALE255(value) ((u32)(value) / 255)

extern u8 D_80083160[];
extern s32 func_80069EF8(void);
extern void func_80066844(void *);
extern void func_80066640(void *, s32);
extern void func_800A130C(void *, void *);
extern void func_800A1330(void *, void *);
extern s32 func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_8006658C(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);

void func_800A1354(u8 *arg0)
{
    u8 **ctx_addr = (u8 **)D_80083160;
    s32 i = 0;
    u32 mask = 0xFFFFFF;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *obj;
    s32 scale;
    u8 *poly;
    s32 rand1;
    s32 color3;

    scale = FIELD(arg0, s16, 0x10);
    FIELD(scratch, u8 *, 0x24) = *ctx_addr + 0xB0;
    do {
        u8 *ctx = *ctx_addr;
        u8 *packet;
        obj = arg0 + (i * 4);

        poly = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = poly + 0x28;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x04) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x0C) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        FIELD(poly, u32, 0x14) = (rand1 * func_80069EF8()) & mask;
        rand1 = func_80069EF8();
        color3 = rand1 * func_80069EF8();
        FIELD(poly, u32, 0x1C) = color3 & mask;

        FIELD(poly, u8, 0x04) = SCALE255(FIELD(poly, u8, 0x04) * scale);
        FIELD(poly, u8, 0x05) = SCALE255(FIELD(poly, u8, 0x05) * scale);
        FIELD(poly, u8, 0x06) = SCALE255(FIELD(poly, u8, 0x06) * scale);
        FIELD(poly, u8, 0x0C) = SCALE255(FIELD(poly, u8, 0x0C) * scale);
        FIELD(poly, u8, 0x0D) = SCALE255(FIELD(poly, u8, 0x0D) * scale);
        FIELD(poly, u8, 0x0E) = SCALE255(FIELD(poly, u8, 0x0E) * scale);
        FIELD(poly, u8, 0x14) = SCALE255(FIELD(poly, u8, 0x14) * scale);
        FIELD(poly, u8, 0x15) = SCALE255(FIELD(poly, u8, 0x15) * scale);
        FIELD(poly, u8, 0x16) = SCALE255(FIELD(poly, u8, 0x16) * scale);
        FIELD(poly, u8, 0x1C) = FIELD(poly, u8, 0x04);
        FIELD(poly, u8, 0x1D) = FIELD(poly, u8, 0x05);
        FIELD(poly, u8, 0x1E) = FIELD(poly, u8, 0x06);
        func_80066844(poly);
        func_80066640(poly, 1);

        func_800A130C(scratch + 0x74, FIELD(FIELD(obj, u8 *, 0x54), void *, 8));
        func_800A130C(scratch + 0x7C, FIELD(FIELD(obj, u8 *, 0x58), void *, 8));
        func_800A130C(scratch + 0x84, FIELD(FIELD(obj, u8 *, 0x5C), void *, 8));
        func_800A1330(scratch + 0x8C, scratch + 0x74);
        FIELD(scratch, s32, 0xC4) = func_800654B0(
            scratch + 0x74, scratch + 0x7C, scratch + 0x84, scratch + 0x8C, scratch + 0xE8, scratch + 0xEC,
            scratch + 0xF0, scratch + 0xF4, scratch + 0x94, scratch + 0x98) - 0x30;

        FIELD(poly, u16, 0x08) = FIELD(scratch, u16, 0xE8);
        FIELD(poly, u16, 0x0A) = FIELD(scratch, u16, 0xEA);
        FIELD(poly, u16, 0x10) = FIELD(scratch, u16, 0xEC);
        FIELD(poly, u16, 0x12) = FIELD(scratch, u16, 0xEE);
        FIELD(poly, u16, 0x18) = FIELD(scratch, u16, 0xF0);
        FIELD(poly, u16, 0x1A) = FIELD(scratch, u16, 0xF2);
        FIELD(poly, u16, 0x20) = FIELD(scratch, u16, 0xF4);
        FIELD(poly, u16, 0x22) = FIELD(scratch, u16, 0xF6);
        if (FIELD(scratch, s32, 0xC4) >= 0x1E0)
            FIELD(scratch, s32, 0xC4) = 0x1DF;
        if (FIELD(scratch, s32, 0xC4) < 0)
            FIELD(scratch, s32, 0xC4) = 0;
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, poly);
        i += 3;
        ctx = *ctx_addr;
        packet = FIELD(ctx, u8 *, 0x8D0);
        FIELD(ctx, u8 *, 0x8D0) = packet + 0xC;
        func_80067F20(packet, 1, 0, func_80066460(0, 1, 0x140, 0), 0);
        func_8006658C(FIELD(scratch, u8 *, 0x24) + FIELD(scratch, s32, 0xC4) * 4, packet);
    } while (i < 6);
}
