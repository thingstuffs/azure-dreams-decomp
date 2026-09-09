#include "common.h"

typedef struct S_80174618_0 {
    u8 pad_00[0x24];
    union { u8 * s; u32 * u; } unk_24;   /* accessed as both */
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
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_80174618_0;   /* scratch in func_80174618 */

typedef struct S_80174618_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80174618_1;   /* arg1 in func_80174618 */

typedef struct S_80174618_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_80174618_2;   /* arg2 in func_80174618 */

typedef struct S_80174618_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80174618_3;   /* context in func_80174618 */

typedef struct S_80174618_4 {
    u8 pad_00[0x64];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_80174618_4;   /* arg0 in func_80174618 */

typedef struct S_80174618_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80174618_5;   /* packet in func_80174618 */

typedef struct S_80174618_6 {
    u32 unk_00;
} S_80174618_6;   /* packet2 in func_80174618 */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {
} EMPTY_ARG;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590();
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083160[];

void func_80174618(S_80174618_4 *arg0, S_80174618_1 *arg1, void *arg2, s16 arg3)
{
    u8 *packet;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet2;
    u8 *context;
    register u8 *global_page ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *packet8;
    u8 *packetC;
    u8 *call_arg0;
    u8 *arg9;
    u8 *arg10;
    u16 flags;
    u16 value;
    s32 packet_payload;
    u16 final_value;
    s32 index;
    MATRIX matrix;
    EMPTY_ARG no_arg;

    ((S_80174618_0 *)scratch)->unk_24.s = *(u8 **)D_80083160 + 0xB0;
    ((S_80174618_0 *)scratch)->unk_88 = arg1->unk_02;
    ((S_80174618_0 *)scratch)->unk_8C = arg1->unk_06;
    ((S_80174618_0 *)scratch)->unk_90 = arg1->unk_0A;
    ((S_80174618_2 *)arg2)->unk_14 |= 0x8000;

    func_800649A0();

    ((S_80174618_0 *)scratch)->unk_3C = 0x2000;
    ((S_80174618_0 *)scratch)->unk_38 = 0x2000;
    ((S_80174618_0 *)scratch)->unk_34 = 0x2000;
    ((S_80174618_0 *)scratch)->unk_A4 = ((S_80174618_2 *)arg2)->unk_16;
    ((S_80174618_0 *)scratch)->unk_A8 = ((S_80174618_2 *)arg2)->unk_1A;
    ((S_80174618_0 *)scratch)->unk_A6 = ((S_80174618_2 *)arg2)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    arg9 = scratch + 0xD0;
    arg10 = scratch + 0xD4;
    call_arg0 = scratch + 0xB0;

    value = ((S_80174618_2 *)arg2)->unk_14;
    context = *(u8 **)D_80083160;
    ((S_80174618_0 *)scratch)->unk_28 = value;
    packet = ((S_80174618_3 *)context)->unk_8D0;
    ((S_80174618_3 *)context)->unk_8D0 = packet + 0x10;

    value = arg0->unk_64;
    ((S_80174618_0 *)scratch)->unk_C0 = value;
    ((S_80174618_0 *)scratch)->unk_B0 = value;
    value = arg0->unk_6A;
    ((S_80174618_0 *)scratch)->unk_C8 = value;
    ((S_80174618_0 *)scratch)->unk_B8 = value;
    value = arg0->unk_66;
    ((S_80174618_0 *)scratch)->unk_C2 = value;
    ((S_80174618_0 *)scratch)->unk_B2 = value;
    value = arg0->unk_6C;
    ((S_80174618_0 *)scratch)->unk_CA = value;
    ((S_80174618_0 *)scratch)->unk_BA = value;
    value = arg0->unk_68;
    ((S_80174618_0 *)scratch)->unk_C4 = value;
    ((S_80174618_0 *)scratch)->unk_B4 = value;
    final_value = arg0->unk_6E;
    packet8 = packet + 8;
    packetC = packet + 0xC;
    index = func_80065590(call_arg0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet8, packetC,
                          packet8, packetC,
                          arg9, arg10,
                          (((S_80174618_0 *)scratch)->unk_CC = final_value,
                           ((S_80174618_0 *)scratch)->unk_BC = final_value,
                           no_arg));
    index = index - arg3 - 6;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80174618_0 *)scratch)->unk_100 = index;
    flags = ((S_80174618_0 *)scratch)->unk_28;
    global_page = D_80083160 - 0x3160;
    ASM_SET(global_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    packet2 = global_page + 0x3160;

    if (flags & 8) {
        u8 tail_value;
        if (flags & 4) {
            tail_value = ((S_80174618_2 *)arg2)->unk_0C.at03.v | 2;
        } else {
            tail_value = ((S_80174618_2 *)arg2)->unk_0C.at03.v & 0xFD;
        }
        ((S_80174618_2 *)arg2)->unk_0C.at03.v = tail_value;
    }

    packet_payload = ((S_80174618_2 *)arg2)->unk_0C.at00.v;
    ((S_80174618_5 *)packet)->unk_00.at03.v = 3;
    ((S_80174618_5 *)packet)->unk_04.at00.v = packet_payload;
    ((S_80174618_5 *)packet)->unk_04.at03.v = 0x40;
    flags = ((S_80174618_0 *)scratch)->unk_28;
    if (flags & 8) {
        s32 packet_type = flags & 4;
        if (packet_type) {
            packet_type = 0x42;
        } else {
            packet_type = 0x40;
        }
        ((S_80174618_5 *)packet)->unk_04.at03.v = packet_type;
    }

    {
    register u32 low_mask ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 zero;
    register u32 high_mask ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    low_mask = 0x00FFFFFF;
    zero = 0;
    ASM_KEEP(zero);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    high_mask = 0xFF000000;
    ((S_80174618_5 *)packet)->unk_00.at00.v = (((S_80174618_5 *)packet)->unk_00.at00.v & high_mask) |
                            (((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] & low_mask);
    ((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] =
        (((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] & high_mask) |
        ((u32)packet & low_mask);

    context = *(u8 **)packet2;
    packet2 = ((S_80174618_3 *)context)->unk_8D0;
    ((S_80174618_3 *)context)->unk_8D0 = packet2 + 0xC;
    func_80067F20(packet2, 0, 0, (u16)func_80066460(zero, 1, zero, zero), 0);

    ((S_80174618_6 *)packet2)->unk_00 = (((S_80174618_6 *)packet2)->unk_00 & high_mask) |
                             (((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] & low_mask);
    packet2 = (u8 *)((u32)packet2 & low_mask);
    ((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] =
        (((S_80174618_0 *)scratch)->unk_24.u[((S_80174618_0 *)scratch)->unk_100] & high_mask) |
        (u32)packet2;

    func_80064A40();
    }
}
