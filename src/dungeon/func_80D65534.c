#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80D65534_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_80D65534_0;   /* arg1 in func_80D65534 */

typedef struct S_80D65534_1_pre {
    u16 unk_00;
} S_80D65534_1_pre;   /* the 0x2 bytes before arg0 in func_80D65534, addressed as arg0[-1] */

typedef struct S_80D65534_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x8];
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    s16 unk_0E;
    u8 pad_10[0x8];
    u16 unk_18;
    u8 pad_1A[0x12];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} S_80D65534_1;   /* arg0 in func_80D65534 */




extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0[3];

void func_80D65534(void *arg0, S_80D65534_0 *arg1, Rec_D_80082E80 *arg2)
{
    s16 count;
    s32 old_z;
    s32 scale;
    s32 terrain;
    u16 value;
    u16 x_arg;
    u16 z_arg;

    arg1->unk_08.at00.v += ((S_80D65534_1 *)arg0)->unk_34;
    ((S_80D65534_1 *)arg0)->unk_34 += ((S_80D65534_1 *)arg0)->unk_40;

    x_arg = arg1->unk_00.at02.v;
    z_arg = arg1->unk_08.at02.v;
    old_z = arg1->unk_08.at02u.v;
    terrain = func_800BCB04(x_arg,
                            arg1->unk_04.at02.v,
                            (s16)(z_arg - 4));
    if (terrain - 0x10 < old_z) {
        ((S_80D65534_1 *)arg0)->unk_34 = 0;
        arg1->unk_08.at02u.v =
            func_800BCB04(arg1->unk_00.at02.v,
                          arg1->unk_04.at02.v,
                          (s16)(arg1->unk_08.at02.v - 4)) - 0x11;
        arg1->unk_08.at00u.v = 0;
        if (((S_80D65534_1 *)arg0)->unk_02 == 0) {
            ((S_80D65534_1 *)arg0)->unk_02 = 1;
        }
    }

    if (((S_80D65534_1 *)arg0)->unk_02 == 1) {
        arg1->unk_00.at00.v += ((S_80D65534_1 *)arg0)->unk_2C;
        ((S_80D65534_1 *)arg0)->unk_2C += ((S_80D65534_1 *)arg0)->unk_38;
        if (func_800BCB04(arg1->unk_00.at02.v,
                          arg1->unk_04.at02.v,
                          arg1->unk_08.at02u.v) < 0x200 &&
            (s16)func_800A45D8(arg1->unk_00.at02.v,
                                arg1->unk_04.at02.v,
                                arg1->unk_08.at02u.v) != 0) {
            arg1->unk_00.at00.v -= ((S_80D65534_1 *)arg0)->unk_2C;
            ((S_80D65534_1 *)arg0)->unk_2C = 0;
            ((S_80D65534_1 *)arg0)->unk_38 = 0;
        }

        arg1->unk_04.at00.v += ((S_80D65534_1 *)arg0)->unk_30;
        ((S_80D65534_1 *)arg0)->unk_30 += ((S_80D65534_1 *)arg0)->unk_3C;
        if (func_800BCB04(arg1->unk_00.at02.v,
                          arg1->unk_04.at02.v,
                          arg1->unk_08.at02u.v) < 0x200 &&
            (s16)func_800A45D8(arg1->unk_00.at02.v,
                                arg1->unk_04.at02.v,
                                arg1->unk_08.at02u.v) != 0) {
            arg1->unk_04.at00.v -= ((S_80D65534_1 *)arg0)->unk_30;
            ((S_80D65534_1 *)arg0)->unk_30 = 0;
            ((S_80D65534_1 *)arg0)->unk_3C = 0;
        }
    }

    scale = (((S_80D65534_1 *)arg0)->unk_0C.s << 7) /
            ((S_80D65534_1 *)arg0)->unk_0E;
    arg2->unk_0C.at02_s8.v = scale;
    arg2->unk_0C.at01_s8.v = scale;
    arg2->unk_0C.at00_s8.v = scale;

    value = ((S_80D65534_1 *)arg0)->unk_18 + 1;
    ((S_80D65534_1 *)arg0)->unk_18 = value;
    if ((s16)value == 3) {
        func_800478B8(arg2);
        ((S_80D65534_1 *)arg0)->unk_18 = 0;
    }

    value = arg2->unk_1C.at00_u16.v + 0xC8;
    arg2->unk_1C.at00_u16.v = value;
    if (value > 0x1000) {
        arg2->unk_1C.at00_u16.v = 0x1000;
    }

    value = arg2->unk_1C.at02_u16.v + 0xC8;
    arg2->unk_1C.at02_u16.v = value;
    if (value > 0x1000) {
        arg2->unk_1C.at02_u16.v = 0x1000;
    }

    count = ((S_80D65534_1 *)arg0)->unk_0C.u - 1;
    ((S_80D65534_1 *)arg0)->unk_0C.u = count;
    if ((count << 16) <= 0) {
        ((S_80D65534_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
