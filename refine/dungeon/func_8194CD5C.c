#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002455C_0_pre {
    u16 unk_00;
} S_8002455C_0_pre;   /* the 0x2 bytes before arg0 in func_8002455C, addressed as arg0[-1] */

typedef struct S_8002455C_0 {
    void * unk_00;
    u8 pad_04[0x28];
    s16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
} S_8002455C_0;   /* arg0 in func_8002455C */

typedef struct S_8002455C_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8002455C_1;   /* temp_v1 in func_8002455C */

typedef struct S_8002455C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002455C_2;   /* arg1 in func_8002455C */

typedef struct S_8002455C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8002455C_3;   /* arg2 in func_8002455C */


M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_800649A0();                            /* extern */
M2C_UNK func_80064A40();                            /* extern */
M2C_UNK func_80064B30();        /* extern */
extern M2C_UNK D_800814A0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} InputVector;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} OutputVector;

/* Updates a rotating effect, fades and shrinks its sprite, and flags completion. */
void func_8002455C(void *effect, void *position, void *sprite) {
    InputVector local_offset;
    OutputVector rotated_offset;
    s32 y_product;
    u16 scale;
    u8 brightness;
    void *counter_state;

    counter_state = ((S_8002455C_0 *)effect)->unk_00;
    ((S_8002455C_1 *)counter_state)->unk_1A = (u16) (((S_8002455C_1 *)counter_state)->unk_1A + 1);
    ((S_8002455C_0 *)effect)->unk_2E = (u16) (((S_8002455C_0 *)effect)->unk_2E + 0x100);
    ((S_8002455C_2 *)position)->unk_00.at00.v = (s32) ((S_8002455C_2 *)position)->unk_0C;
    ((S_8002455C_2 *)position)->unk_04.at00.v = (s32) ((S_8002455C_2 *)position)->unk_10;
    ((S_8002455C_2 *)position)->unk_08.at00.v = (s32) ((S_8002455C_2 *)position)->unk_14;
    local_offset.x = (s16) ((s32) ((func_800644B8((s16) ((S_8002455C_0 *)effect)->unk_2E) >> 4) * ((S_8002455C_0 *)effect)->unk_2C) >> 8);
    y_product = (func_80064584((s16) ((S_8002455C_0 *)effect)->unk_2E) >> 4) * ((S_8002455C_0 *)effect)->unk_2C;
    local_offset.z = 0;
    local_offset.y = (s16) (y_product >> 8);
    func_800649A0();
    func_80064B30(effect + 4, &local_offset, &rotated_offset);
    func_80064A40();
    ((S_8002455C_2 *)position)->unk_00.at02.v = (u16) (((S_8002455C_2 *)position)->unk_00.at02.v + rotated_offset.x);
    ((S_8002455C_2 *)position)->unk_04.at02.v = (u16) (((S_8002455C_2 *)position)->unk_04.at02.v + rotated_offset.y);
    ((S_8002455C_2 *)position)->unk_08.at02.v = (u16) (((S_8002455C_2 *)position)->unk_08.at02.v + rotated_offset.z);
    if (((S_8002455C_0 *)effect)->unk_30 != 0) {
        ((S_8002455C_0 *)effect)->unk_30 = 0U;
    }
    brightness = ((S_8002455C_3 *)sprite)->unk_0E - 8;
    ((S_8002455C_3 *)sprite)->unk_0E = brightness;
    ((S_8002455C_3 *)sprite)->unk_0D = brightness;
    ((S_8002455C_3 *)sprite)->unk_0C = brightness;
    if (!(brightness & 0xFF) || (scale = ((S_8002455C_3 *)sprite)->unk_1E - 0x100, ((S_8002455C_3 *)sprite)->unk_1E = scale, ((S_8002455C_3 *)sprite)->unk_1C = scale, ((S_8002455C_3 *)sprite)->unk_1A = (u16) ((S_8002455C_0 *)effect)->unk_2E, func_800478B8(sprite), ((((S_8002455C_3 *)sprite)->unk_14 & 0x6000) != 0))) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_8002455C_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Two six-byte vector aggregates force stack slots sp+0x10..0x14 and sp+0x18..0x1C,
   restoring the 0x30 frame and the s0/s1/s2-only save set.
   cdk -G0 plus a direct scalar D_800814A0 RMW removes the extra address addiu and closes the residue. */
