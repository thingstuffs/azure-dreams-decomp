#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80170D58_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80170D58_0;   /* arg1 in func_80170D58 */

typedef struct S_80170D58_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0xA];
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0x2A];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_80170D58_1;   /* arg0 in func_80170D58 */




extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0;

void func_80170D58(void *arg0, void *arg1, void *arg2)
{
    s32 old_z;
    u16 value;

    ((S_80170D58_0 *)arg1)->unk_00.at00.v += ((S_80170D58_1 *)arg0)->unk_54;
    ((S_80170D58_1 *)arg0)->unk_54 += ((S_80170D58_1 *)arg0)->unk_60;
    if ((func_800BCB04(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                       ((S_80170D58_0 *)arg1)->unk_08.at02.v) < 0x200) &&
        ((s16)func_800A45D8(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                            ((S_80170D58_0 *)arg1)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)arg1)->unk_00.at00.v -= ((S_80170D58_1 *)arg0)->unk_54;
        ((S_80170D58_1 *)arg0)->unk_54 = 0;
        ((S_80170D58_1 *)arg0)->unk_60 = 0;
    }

    ((S_80170D58_0 *)arg1)->unk_04.at00.v += ((S_80170D58_1 *)arg0)->unk_58;
    ((S_80170D58_1 *)arg0)->unk_58 += ((S_80170D58_1 *)arg0)->unk_64;
    if ((func_800BCB04(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                       ((S_80170D58_0 *)arg1)->unk_08.at02.v) < 0x200) &&
        ((s16)func_800A45D8(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                            ((S_80170D58_0 *)arg1)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)arg1)->unk_04.at00.v -= ((S_80170D58_1 *)arg0)->unk_58;
        ((S_80170D58_1 *)arg0)->unk_58 = 0;
        ((S_80170D58_1 *)arg0)->unk_64 = 0;
    }

    ((S_80170D58_0 *)arg1)->unk_08.at00.v += ((S_80170D58_1 *)arg0)->unk_5C;
    ((S_80170D58_1 *)arg0)->unk_5C += ((S_80170D58_1 *)arg0)->unk_68;
    old_z = ((S_80170D58_0 *)arg1)->unk_08.at02.v;
    if (func_800BCB04(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                      (s16)(((S_80170D58_0 *)arg1)->unk_08.at02u.v - 4)) - 0x10 < old_z) {
        ((S_80170D58_1 *)arg0)->unk_5C = 0;
        ((S_80170D58_0 *)arg1)->unk_08.at02.v =
            func_800BCB04(((S_80170D58_0 *)arg1)->unk_00.at02.v, ((S_80170D58_0 *)arg1)->unk_04.at02.v,
                          (s16)(((S_80170D58_0 *)arg1)->unk_08.at02u.v - 4)) - 0x11;
        ((S_80170D58_0 *)arg1)->unk_08.at00u.v = 0;
        if (((S_80170D58_1 *)arg0)->unk_1A == 0) {
            ((S_80170D58_1 *)arg0)->unk_1A = 1;
            ((S_80170D58_1 *)arg0)->unk_26.s = 0;
        }
    }

    value = ((S_80170D58_1 *)arg0)->unk_28 + 1;
    ((S_80170D58_1 *)arg0)->unk_28 = value;
    if ((value & 3) == 0) {
        func_800478B8(arg2);
    }

    value = ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v + 0x64;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = value;
    if (value > 0x1000) {
        ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = 0x1000;
    }

    value = ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v + 0x64;
    ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = value;
    if (value > 0x1000) {
        ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = 0x1000;
    }

    value = ((S_80170D58_1 *)arg0)->unk_26.u - 1;
    ((S_80170D58_1 *)arg0)->unk_26.u = value;
    if ((s16)value <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
