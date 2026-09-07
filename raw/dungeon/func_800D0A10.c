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
extern void func_800666E0(void *);
extern u8 D_80083160[];

void func_800D6170(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 **global = (u8 **)D_80083160;
    u8 *packet;
    s32 index;
    register s32 delta ASM_REG("$2");
    s32 i;
    u32 lowMask;
    u32 highMask;
    u16 xy[4];
    MATRIX matrix;

    FIELD(scratch, u8 *, 0x24) = *global + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    FIELD(arg2, u16, 0x14) |= 0x8000;

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

    FIELD(scratch, u16, 0x28) = FIELD(arg2, u16, 0x14);
    for (i = 0; i < 4; i++) {
        xy[i] = FIELD(arg0, u16, 0x54 + i * 2);
    }

    delta = (s16)xy[0];
    ASM_KEEP(delta);
    delta -= (s16)xy[2];
    if (delta < 0) {
        delta = -delta;
    }
    if (delta >= 0x11) {
        lowMask = 0x00FFFFFF;
        highMask = 0xFF000000;
        do {
        FIELD(scratch, u16, 0xB0) = FIELD(arg0, u16, 0x44);
        FIELD(scratch, u16, 0xB8) = FIELD(arg0, u16, 0x46);
        FIELD(scratch, u16, 0xC0) = FIELD(arg0, u16, 0x48);
        FIELD(scratch, u16, 0xC8) = FIELD(arg0, u16, 0x4A);
        FIELD(scratch, u16, 0xB2) = FIELD(arg0, u16, 0x4C);
        FIELD(scratch, u16, 0xBA) = FIELD(arg0, u16, 0x4E);
        FIELD(scratch, u16, 0xC2) = FIELD(arg0, u16, 0x50);
        FIELD(scratch, u16, 0xCA) = FIELD(arg0, u16, 0x52);
        FIELD(scratch, u16, 0xB4) = xy[2] - 0x10;
        FIELD(scratch, u16, 0xBC) = xy[3] - 0x10;
        FIELD(scratch, u16, 0xC4) = xy[2];
        FIELD(scratch, u16, 0xCC) = xy[3];
        xy[2] -= 0x10;
        xy[3] -= 0x10;

        packet = FIELD(*global, u8 *, 0x8D0);
        FIELD(*global, u8 *, 0x8D0) = packet + 0x18;
        index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0xC,
                              packet + 0x10, packet + 0x14,
                              scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
        FIELD(scratch, s32, 0x100) = index;

        if ((u32)index < 0x1E0) {
            if ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0xC) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0xE) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0x14) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0x16) + 0x20) < 0x121))) {
                FIELD(arg2, u16, 0x14) &= 0x7FFF;
                FIELD(packet, u32, 4) = FIELD(arg2, u32, 0xC);
                func_800666E0(packet);

                FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & highMask) |
                    (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                           FIELD(scratch, s32, 0x100) * 4) & lowMask);
                FIELD(FIELD(scratch, u32 *, 0x24), u32,
                      FIELD(scratch, s32, 0x100) * 4) =
                    (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                           FIELD(scratch, s32, 0x100) * 4) & highMask) |
                    ((u32)packet & lowMask);
            }
        }
            delta = (s16)xy[0];
            ASM_KEEP(delta);
            delta -= (s16)xy[2];
            if (delta < 0) {
                delta = -delta;
            }
        } while (delta >= 0x11);
    }

    if ((s16)xy[0] != (s16)xy[2]) {
        FIELD(scratch, u16, 0xB0) = FIELD(arg0, u16, 0x44);
        FIELD(scratch, u16, 0xB8) = FIELD(arg0, u16, 0x46);
        FIELD(scratch, u16, 0xC0) = FIELD(arg0, u16, 0x48);
        FIELD(scratch, u16, 0xC8) = FIELD(arg0, u16, 0x4A);
        FIELD(scratch, u16, 0xB2) = FIELD(arg0, u16, 0x4C);
        FIELD(scratch, u16, 0xBA) = FIELD(arg0, u16, 0x4E);
        FIELD(scratch, u16, 0xC2) = FIELD(arg0, u16, 0x50);
        FIELD(scratch, u16, 0xCA) = FIELD(arg0, u16, 0x52);
        FIELD(scratch, u16, 0xB4) = xy[0];
        FIELD(scratch, u16, 0xBC) = xy[1];
        FIELD(scratch, u16, 0xC4) = xy[2];
        FIELD(scratch, u16, 0xCC) = xy[3];

        packet = FIELD(*global, u8 *, 0x8D0);
        FIELD(*global, u8 *, 0x8D0) = packet + 0x18;
        index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0xC,
                              packet + 0x10, packet + 0x14,
                              scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
        FIELD(scratch, s32, 0x100) = index;

        if ((u32)index < 0x1E0) {
            if ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0xC) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0xE) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
                (((u16)(FIELD(packet, u16, 0x14) + 0x20) < 0x181) &&
                 ((u16)(FIELD(packet, u16, 0x16) + 0x20) < 0x121))) {
                FIELD(arg2, u16, 0x14) &= 0x7FFF;
                FIELD(packet, u32, 4) = FIELD(arg2, u32, 0xC);
                func_800666E0(packet);

                FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000) |
                    (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                           FIELD(scratch, s32, 0x100) * 4) & 0x00FFFFFF);
                FIELD(FIELD(scratch, u32 *, 0x24), u32,
                      FIELD(scratch, s32, 0x100) * 4) =
                    (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                           FIELD(scratch, s32, 0x100) * 4) & 0xFF000000) |
                    ((u32)packet & 0x00FFFFFF);
            }
        }
    }

    func_80064A40();
}
