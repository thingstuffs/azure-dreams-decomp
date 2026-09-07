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
extern void func_8006671C(void *);
extern u8 D_80083160[];

void func_80024BF4(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 index;
    u16 flags;
    u8 texFlags;
    MATRIX matrix;

    FIELD(scratch, u8 *, 0x24) = *(u8 **)D_80083160 + 0xB0;
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

    texture = FIELD(arg2, u8 *, 8);
    FIELD(scratch, u16, 0x28) = FIELD(arg2, u16, 0x14);
    packet = FIELD(*(u8 **)D_80083160, u8 *, 0x8D0);
    FIELD(*(u8 **)D_80083160, u8 *, 0x8D0) = packet + 0x34;

    FIELD(scratch, u16, 0xB0) = FIELD(arg0, u16, 0x4A);
    FIELD(scratch, u16, 0xB8) = FIELD(arg0, u16, 0x50);
    FIELD(scratch, u16, 0xC0) = FIELD(arg0, u16, 0x56);
    FIELD(scratch, u16, 0xC8) = FIELD(arg0, u16, 0x5C);
    FIELD(scratch, u16, 0xB2) = FIELD(arg0, u16, 0x4C);
    FIELD(scratch, u16, 0xBA) = FIELD(arg0, u16, 0x52);
    FIELD(scratch, u16, 0xC2) = FIELD(arg0, u16, 0x58);
    FIELD(scratch, u16, 0xCA) = FIELD(arg0, u16, 0x5E);
    FIELD(scratch, u16, 0xB4) = FIELD(arg0, u16, 0x4E);
    FIELD(scratch, u16, 0xBC) = FIELD(arg0, u16, 0x54);
    FIELD(scratch, u16, 0xC4) = FIELD(arg0, u16, 0x5A);
    FIELD(scratch, u16, 0xCC) = FIELD(arg0, u16, 0x60);

    index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x14,
                          packet + 0x20, packet + 0x2C,
                          scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
    FIELD(scratch, s32, 0x100) = index;

    if ((u32)index < 0x1E0) {
        if ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x14) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x16) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x2C) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x2E) + 0x20) < 0x121))) {
            FIELD(arg2, u16, 0x14) &= 0x7FFF;
            FIELD(packet, u16, 0xE) = FIELD(arg0, u16, 0x3C);
            FIELD(packet, u16, 0x1A) = FIELD(arg0, u16, 0x40);
            FIELD(packet, u8, 0xC) = FIELD(arg0, u8, 0x3A);
            FIELD(packet, u8, 0x18) = FIELD(arg0, u8, 0x3E);
            FIELD(packet, u8, 0x24) = FIELD(arg0, u8, 0x44);
            FIELD(packet, u8, 0x30) = FIELD(arg0, u8, 0x46);
            FIELD(packet, u8, 0xD) = FIELD(arg0, u8, 0x3B);
            FIELD(packet, u8, 0x19) = FIELD(arg0, u8, 0x3F);
            FIELD(packet, u8, 0x25) = FIELD(arg0, u8, 0x45);
            FIELD(packet, u8, 0x31) = FIELD(arg0, u8, 0x47);
            FIELD(packet, u32, 4) = FIELD(arg0, u32, 0xC);
            FIELD(packet, u32, 0x10) = FIELD(arg0, u32, 0x10);
            FIELD(packet, u32, 0x1C) = FIELD(arg0, u32, 0x14);
            FIELD(packet, u32, 0x28) = FIELD(arg0, u32, 0x18);

            func_8006671C(packet);

            texFlags = texture[1];
            FIELD(arg2, u8, 0xF) = texFlags;
            flags = FIELD(scratch, u16, 0x28);
            if (flags & 8) {
                FIELD(arg2, u8, 0xF) = (flags & 4) ?
                    (texFlags | 2) : (texFlags & 0xFD);
            }

            FIELD(packet, u8, 7) |= FIELD(arg2, u8, 0xF);
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

    func_80064A40();
}
