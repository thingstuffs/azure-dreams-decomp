#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern void func_80166BD8(void) __attribute__((noreturn));
extern u8 *D_80083160;

void func_80166968(void *arg0, void *arg1, u8 *arg2, s32 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *preloaded = D_80083160;
    register u32 tailValue ASM_REG("$2");
    u8 **global;
    u8 *packet;
    s8 *texture;
    u32 packetSource;
    s32 zero;
    s32 index;
    s32 average0;
    s32 average1;
    s32 average2;
    s32 average3;
    s32 average4;
    s32 average5;
    u8 *coord0;
    u8 *coord1;
    u8 *coord2;
    u8 *coord3;
    u32 lowMask;
    u32 highMask;
    u16 flags;
    s32 heldArg3;
    MATRIX matrix;

    FIELD(scratch, u8 *, 0x24) = preloaded + 0xB0;
    lowMask = 0x00FFFFFF;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    heldArg3 = arg3;
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    FIELD(arg2, u16, 0x14) |= 0x8000;
    global = &D_80083160;
    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = FIELD(arg2, s8 *, 8);
    highMask = 0xFF000000;
    FIELD(scratch, u16, 0x28) = FIELD(arg2, u16, 0x14);

    for (;;) {
        packet = FIELD(*global, u8 *, 0x8D0);
        FIELD(*global, u8 *, 0x8D0) = packet + 0x10;

        coord0 = scratch + 0xB0;
        average0 = (FIELD(arg0, s16, 0x74) + FIELD(arg0, s16, 0x7A)) / 2;
        FIELD(scratch, s16, 0xC0) = average0;
        FIELD(scratch, s16, 0xB0) = average0;
        coord1 = scratch + 0xB8;
        average1 = (FIELD(arg0, s16, 0x80) + FIELD(arg0, s16, 0x86)) / 2;
        FIELD(scratch, s16, 0xC8) = average1;
        FIELD(scratch, s16, 0xB8) = average1;
        coord2 = scratch + 0xC0;
        average2 = (FIELD(arg0, s16, 0x76) + FIELD(arg0, s16, 0x7C)) / 2;
        FIELD(scratch, s16, 0xC2) = average2;
        FIELD(scratch, s16, 0xB2) = average2;
        coord3 = scratch + 0xC8;
        average3 = (FIELD(arg0, s16, 0x82) + FIELD(arg0, s16, 0x88)) / 2;
        FIELD(scratch, s16, 0xCA) = average3;
        FIELD(scratch, s16, 0xBA) = average3;
        average4 = (FIELD(arg0, s16, 0x78) + FIELD(arg0, s16, 0x7E)) / 2;
        FIELD(scratch, s16, 0xC4) = average4;
        FIELD(scratch, s16, 0xB4) = average4;
        average5 = (FIELD(arg0, s16, 0x84) + FIELD(arg0, s16, 0x8A)) / 2;
        FIELD(scratch, s16, 0xCC) = average5;
        FIELD(scratch, s16, 0xBC) = average5;

        index = func_80065590(coord0, coord1, coord2, coord3,
                              packet + 8, packet + 0xC,
                              packet + 8, packet + 0xC,
                              scratch + 0xD0, scratch + 0xD4) - (s16)heldArg3 - 6;
        FIELD(scratch, s32, 0x100) = index;

        flags = FIELD(scratch, u16, 0x28);
        if (flags & 8) {
            if (flags & 4) {
                tailValue = FIELD(arg2, u8, 0xF) | 2;
                ASM_TAILSLOT_PIN(tailValue);
                func_80166BD8();
            } else {
                FIELD(arg2, u8, 0xF) &= 0xFD;
            }
        }

        zero = 0;
        packetSource = FIELD(arg0, u32, 0);
        FIELD(packet, u8, 3) = 3;
        FIELD(packet, u32, 4) = packetSource;
        FIELD(packet, u8, 7) = 0x42;

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & highMask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & lowMask);
        FIELD(FIELD(scratch, u32 *, 0x24), u32,
              FIELD(scratch, s32, 0x100) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & highMask) |
            ((u32)packet & lowMask);

        packet = FIELD(*global, u8 *, 0x8D0);
        FIELD(*global, u8 *, 0x8D0) = packet + 0xC;
        func_80067F20(packet, zero, zero, func_80066460(zero, 1, zero, zero) & 0xFFFF, zero);

        FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & highMask) |
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & lowMask);
        packet = (u8 *)((u32)packet & lowMask);
        FIELD(FIELD(scratch, u32 *, 0x24), u32,
              FIELD(scratch, s32, 0x100) * 4) =
            (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                   FIELD(scratch, s32, 0x100) * 4) & highMask) |
            (u32)packet;

        if (*texture < 0) {
            break;
        }
        texture += 0xC;
    }

    func_80064A40();
}
