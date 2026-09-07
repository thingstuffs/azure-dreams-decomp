#include "common.h"

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

typedef struct S_80D65534_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_80D65534_2;   /* arg2 in func_80D65534 */



extern void func_800478B8(void *arg0);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);
extern s32 D_800814A0[3];

/* Updates effect motion, terrain collisions, visual properties, and lifetime. */
void func_80D65534(void *effect, S_80D65534_0 *position, S_80D65534_2 *visual)
{
    s16 life_left;
    s32 current_z;
    s32 life_scale;
    s32 terrain_z;
    u16 updated_value;
    u16 x;
    u16 z;

    position->unk_08.at00.v += ((S_80D65534_1 *)effect)->unk_34;
    ((S_80D65534_1 *)effect)->unk_34 += ((S_80D65534_1 *)effect)->unk_40;

    x = position->unk_00.at02.v;
    z = position->unk_08.at02.v;
    current_z = position->unk_08.at02u.v;
    terrain_z = func_800BCB04(x,
                            position->unk_04.at02.v,
                            (s16)(z - 4));
    if (terrain_z - 0x10 < current_z) {
        ((S_80D65534_1 *)effect)->unk_34 = 0;
        position->unk_08.at02u.v =
            func_800BCB04(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          (s16)(position->unk_08.at02.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
        if (((S_80D65534_1 *)effect)->unk_02 == 0) {
            ((S_80D65534_1 *)effect)->unk_02 = 1;
        }
    }

    if (((S_80D65534_1 *)effect)->unk_02 == 1) {
        position->unk_00.at00.v += ((S_80D65534_1 *)effect)->unk_2C;
        ((S_80D65534_1 *)effect)->unk_2C += ((S_80D65534_1 *)effect)->unk_38;
        if (func_800BCB04(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          position->unk_08.at02u.v) < 0x200 &&
            (s16)func_800A45D8(position->unk_00.at02.v,
                                position->unk_04.at02.v,
                                position->unk_08.at02u.v) != 0) {
            position->unk_00.at00.v -= ((S_80D65534_1 *)effect)->unk_2C;
            ((S_80D65534_1 *)effect)->unk_2C = 0;
            ((S_80D65534_1 *)effect)->unk_38 = 0;
        }

        position->unk_04.at00.v += ((S_80D65534_1 *)effect)->unk_30;
        ((S_80D65534_1 *)effect)->unk_30 += ((S_80D65534_1 *)effect)->unk_3C;
        if (func_800BCB04(position->unk_00.at02.v,
                          position->unk_04.at02.v,
                          position->unk_08.at02u.v) < 0x200 &&
            (s16)func_800A45D8(position->unk_00.at02.v,
                                position->unk_04.at02.v,
                                position->unk_08.at02u.v) != 0) {
            position->unk_04.at00.v -= ((S_80D65534_1 *)effect)->unk_30;
            ((S_80D65534_1 *)effect)->unk_30 = 0;
            ((S_80D65534_1 *)effect)->unk_3C = 0;
        }
    }

    life_scale = (((S_80D65534_1 *)effect)->unk_0C.s << 7) /
            ((S_80D65534_1 *)effect)->unk_0E;
    visual->unk_0E = life_scale;
    visual->unk_0D = life_scale;
    visual->unk_0C = life_scale;

    updated_value = ((S_80D65534_1 *)effect)->unk_18 + 1;
    ((S_80D65534_1 *)effect)->unk_18 = updated_value;
    if ((s16)updated_value == 3) {
        func_800478B8(visual);
        ((S_80D65534_1 *)effect)->unk_18 = 0;
    }

    updated_value = visual->unk_1C + 0xC8;
    visual->unk_1C = updated_value;
    if (updated_value > 0x1000) {
        visual->unk_1C = 0x1000;
    }

    updated_value = visual->unk_1E + 0xC8;
    visual->unk_1E = updated_value;
    if (updated_value > 0x1000) {
        visual->unk_1E = 0x1000;
    }

    life_left = ((S_80D65534_1 *)effect)->unk_0C.u - 1;
    ((S_80D65534_1 *)effect)->unk_0C.u = life_left;
    if ((life_left << 16) <= 0) {
        ((S_80D65534_1_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
