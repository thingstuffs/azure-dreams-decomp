#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u8 D_80083160[];

void func_8195FD40(s32 arg0, void *arg1, void *arg2, s16 arg3)
{
    s32 sp28[8];
    u8 *scratch = (u8 *)0x1F800000;
    u8 **global = (u8 **)D_80083160;
    s32 *temp_v1;
    s32 temp_a0;
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 acc1;
    s32 acc2;
    s8 temp_v0_3;
    s8 temp_v0_5;
    u32 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_4;
    u8 *packet;
    u8 *texture;

    (void)arg0;
    FIELD(scratch, u32, 0x20) = *global + 0xB0;
    FIELD(scratch, s32, 0xE4) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0xE8) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0xEC) = FIELD(arg1, s16, 0xA);
    packet = FIELD(*global, u8 *, 0x8D0);
    texture = FIELD(arg2, u8 *, 8);
    func_800649A0();

    FIELD(scratch, u32, 0x30) = FIELD(arg2, u16, 0x1C) * 2;
    FIELD(scratch, u32, 0x34) = FIELD(arg2, u16, 0x1E) * 2;
    FIELD(scratch, u32, 0x38) = 0x2000;
    FIELD(scratch, u16, 0x100) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0x104) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0x102) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(&sp28);
    func_80064840(&sp28, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    FIELD(scratch, u32, 0x78) = 0x20;
    FIELD(scratch, u32, 0x88) = 0x200000;
    FIELD(scratch, u32, 0x80) = 0x200000;
    FIELD(scratch, u32, 0x70) = 0;
    FIELD(scratch, u16, 0x8C) = 0;
    FIELD(scratch, u16, 0x84) = 0;
    FIELD(scratch, u16, 0x7C) = 0;
    FIELD(scratch, u16, 0x74) = 0;
    temp_v0 = func_80065590(scratch + 0x70, scratch + 0x78,
                            scratch + 0x80, scratch + 0x88,
                            packet + 8, packet + 0x10,
                            packet + 0x18, packet + 0x20,
                            scratch + 0x90, scratch + 0x94) - arg3;
    FIELD(scratch, u32, 0xC0) = temp_v0;

    if (temp_v0 < 0x1E0U) {
        f0 = 0;
        if ((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181U) {
            f0 = (u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121U;
        }
        f1 = 0;
        if ((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181U) {
            f1 = (u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121U;
        }
        f2 = 0;
        acc1 = f0 | f1;
        if ((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181U) {
            f2 = (u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121U;
        }
        f3 = 0;
        acc2 = acc1 | f2;
        if ((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181U) {
            f3 = (u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121U;
        }

        if ((acc2 | f3) != 0) {
            temp_v0_2 = FIELD(texture, u8, 8);
            FIELD(packet, u8, 0x1C) = temp_v0_2;
            FIELD(packet, u8, 0xC) = temp_v0_2;
            temp_v0_3 = FIELD(texture, u8, 8) + FIELD(texture, u8, 0xA);
            FIELD(packet, s8, 0x24) = temp_v0_3;
            FIELD(packet, s8, 0x14) = temp_v0_3;
            temp_v0_4 = FIELD(texture, u8, 9);
            FIELD(packet, u8, 0x15) = temp_v0_4;
            FIELD(packet, u8, 0xD) = temp_v0_4;
            temp_v0_5 = FIELD(texture, u8, 9) + FIELD(texture, u8, 0xB);
            FIELD(packet, s8, 0x25) = temp_v0_5;
            FIELD(packet, s8, 0x1D) = temp_v0_5;
            FIELD(packet, u16, 0x16) = FIELD(texture, u16, 4);
            FIELD(packet, s32, 4) = FIELD(arg2, s32, 0xC);
            FIELD(packet, s8, 3) = 9;
            FIELD(packet, s8, 7) = 0x2C;
            if (FIELD(arg2, u16, 0x14) & 4) {
                FIELD(packet, s8, 7) = 0x2E;
            }
            temp_a0 = (s32)packet & 0xFFFFFF;
            FIELD(packet, s32, 0) = (FIELD(packet, s32, 0) & 0xFF000000) |
                (FIELD((u8 *)((FIELD(scratch, u32, 0xC0) * 4) +
                              FIELD(scratch, u32, 0x20)), u32, 0) & 0xFFFFFF);
            temp_v1 = (s32 *)((FIELD(scratch, u32, 0xC0) * 4) +
                              FIELD(scratch, u32, 0x20));
            packet += 0x28;
            *temp_v1 = (*temp_v1 & 0xFF000000) | temp_a0;
        }
    }
    func_80064A40();
    FIELD(*global, u8 *, 0x8D0) = packet;
}
