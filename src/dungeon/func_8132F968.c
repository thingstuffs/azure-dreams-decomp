#include "common.h"

typedef struct S_80166968_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    u8 pad_B6[0x2];
    s16 unk_B8;
    s16 unk_BA;
    s16 unk_BC;
    u8 pad_BE[0x2];
    s16 unk_C0;
    s16 unk_C2;
    s16 unk_C4;
    u8 pad_C6[0x2];
    s16 unk_C8;
    s16 unk_CA;
    s16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_80166968_0;   /* scratch in func_80166968 */

typedef struct S_80166968_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80166968_1;   /* arg1 in func_80166968 */

typedef struct S_80166968_2 {
    u8 pad_00[0x8];
    s8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_80166968_2;   /* arg2 in func_80166968 */

typedef struct S_80166968_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80166968_3;   /* *global in func_80166968 */

typedef struct S_80166968_4 {
    u32 unk_00;
    u8 pad_04[0x70];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_80166968_4;   /* arg0 in func_80166968 */

typedef struct S_80166968_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80166968_5;   /* packet in func_80166968 */



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

void func_80166968(S_80166968_4 *arg0, S_80166968_1 *arg1, u8 *arg2, s32 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *preloaded = D_80083160;
    u32 tailValue;
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

    ((S_80166968_0 *)scratch)->unk_24.p = preloaded + 0xB0;
    lowMask = 0x00FFFFFF;
    ((S_80166968_0 *)scratch)->unk_88 = arg1->unk_02;
    ((S_80166968_0 *)scratch)->unk_8C = arg1->unk_06;
    heldArg3 = arg3;
    ((S_80166968_0 *)scratch)->unk_90 = arg1->unk_0A;
    ((S_80166968_2 *)arg2)->unk_14 |= 0x8000;
    global = &D_80083160;
    func_800649A0();

    ((S_80166968_0 *)scratch)->unk_3C = 0x2000;
    ((S_80166968_0 *)scratch)->unk_38 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_34 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_A4 = ((S_80166968_2 *)arg2)->unk_16;
    ((S_80166968_0 *)scratch)->unk_A8 = ((S_80166968_2 *)arg2)->unk_1A;
    ((S_80166968_0 *)scratch)->unk_A6 = ((S_80166968_2 *)arg2)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = ((S_80166968_2 *)arg2)->unk_08;
    highMask = 0xFF000000;
    ((S_80166968_0 *)scratch)->unk_28 = ((S_80166968_2 *)arg2)->unk_14;

    for (;;) {
        packet = ((S_80166968_3 *)(*global))->unk_8D0;
        ((S_80166968_3 *)(*global))->unk_8D0 = packet + 0x10;

        coord0 = scratch + 0xB0;
        average0 = (arg0->unk_74 + arg0->unk_7A) / 2;
        ((S_80166968_0 *)scratch)->unk_C0 = average0;
        ((S_80166968_0 *)scratch)->unk_B0 = average0;
        coord1 = scratch + 0xB8;
        average1 = (arg0->unk_80 + arg0->unk_86) / 2;
        ((S_80166968_0 *)scratch)->unk_C8 = average1;
        ((S_80166968_0 *)scratch)->unk_B8 = average1;
        coord2 = scratch + 0xC0;
        average2 = (arg0->unk_76 + arg0->unk_7C) / 2;
        ((S_80166968_0 *)scratch)->unk_C2 = average2;
        ((S_80166968_0 *)scratch)->unk_B2 = average2;
        coord3 = scratch + 0xC8;
        average3 = (arg0->unk_82 + arg0->unk_88) / 2;
        ((S_80166968_0 *)scratch)->unk_CA = average3;
        ((S_80166968_0 *)scratch)->unk_BA = average3;
        average4 = (arg0->unk_78 + arg0->unk_7E) / 2;
        ((S_80166968_0 *)scratch)->unk_C4 = average4;
        ((S_80166968_0 *)scratch)->unk_B4 = average4;
        average5 = (arg0->unk_84 + arg0->unk_8A) / 2;
        ((S_80166968_0 *)scratch)->unk_CC = average5;
        ((S_80166968_0 *)scratch)->unk_BC = average5;

        index = func_80065590(coord0, coord1, coord2, coord3,
                              packet + 8, packet + 0xC,
                              packet + 8, packet + 0xC,
                              scratch + 0xD0, scratch + 0xD4) - (s16)heldArg3 - 6;
        ((S_80166968_0 *)scratch)->unk_100 = index;

        flags = ((S_80166968_0 *)scratch)->unk_28;
        if (flags & 8) {
            if (flags & 4) {
                tailValue = ((S_80166968_2 *)arg2)->unk_0F | 2;
                ASM_TAILSLOT_PIN(tailValue);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                func_80166BD8();
            } else {
                ((S_80166968_2 *)arg2)->unk_0F &= 0xFD;
            }
        }

        zero = 0;
        packetSource = arg0->unk_00;
        ((S_80166968_5 *)packet)->unk_00.at03.v = 3;
        ((S_80166968_5 *)packet)->unk_04.at00.v = packetSource;
        ((S_80166968_5 *)packet)->unk_04.at03.v = 0x42;

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & highMask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & lowMask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & highMask) |
            ((u32)packet & lowMask);

        packet = ((S_80166968_3 *)(*global))->unk_8D0;
        ((S_80166968_3 *)(*global))->unk_8D0 = packet + 0xC;
        func_80067F20(packet, zero, zero, func_80066460(zero, 1, zero, zero) & 0xFFFF, zero);

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & highMask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & lowMask);
        packet = (u8 *)((u32)packet & lowMask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & highMask) |
            (u32)packet;

        if (*texture < 0) {
            break;
        }
        texture += 0xC;
    }

    func_80064A40();
}
