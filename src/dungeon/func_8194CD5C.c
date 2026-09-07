#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

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

void func_8002455C(void *arg0, void *arg1, void *arg2) {
    InputVector sp10;
    OutputVector sp18;
    s32 temp_lo;
    u16 temp_v0_2;
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = ((S_8002455C_0 *)arg0)->unk_00;
    ((S_8002455C_1 *)temp_v1)->unk_1A = (u16) (((S_8002455C_1 *)temp_v1)->unk_1A + 1);
    ((S_8002455C_0 *)arg0)->unk_2E = (u16) (((S_8002455C_0 *)arg0)->unk_2E + 0x100);
    ((S_8002455C_2 *)arg1)->unk_00.at00.v = (s32) ((S_8002455C_2 *)arg1)->unk_0C;
    ((S_8002455C_2 *)arg1)->unk_04.at00.v = (s32) ((S_8002455C_2 *)arg1)->unk_10;
    ((S_8002455C_2 *)arg1)->unk_08.at00.v = (s32) ((S_8002455C_2 *)arg1)->unk_14;
    sp10.x = (s16) ((s32) ((func_800644B8((s16) ((S_8002455C_0 *)arg0)->unk_2E) >> 4) * ((S_8002455C_0 *)arg0)->unk_2C) >> 8);
    temp_lo = (func_80064584((s16) ((S_8002455C_0 *)arg0)->unk_2E) >> 4) * ((S_8002455C_0 *)arg0)->unk_2C;
    sp10.z = 0;
    sp10.y = (s16) (temp_lo >> 8);
    func_800649A0();
    func_80064B30(arg0 + 4, &sp10, &sp18);
    func_80064A40();
    ((S_8002455C_2 *)arg1)->unk_00.at02.v = (u16) (((S_8002455C_2 *)arg1)->unk_00.at02.v + sp18.x);
    ((S_8002455C_2 *)arg1)->unk_04.at02.v = (u16) (((S_8002455C_2 *)arg1)->unk_04.at02.v + sp18.y);
    ((S_8002455C_2 *)arg1)->unk_08.at02.v = (u16) (((S_8002455C_2 *)arg1)->unk_08.at02.v + sp18.z);
    if (((S_8002455C_0 *)arg0)->unk_30 != 0) {
        ((S_8002455C_0 *)arg0)->unk_30 = 0U;
    }
    temp_v0 = ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v - 8;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at02_u8.v = temp_v0;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at01_u8.v = temp_v0;
    ((Rec_D_80082E80 *)arg2)->unk_0C.at00_u8.v = temp_v0;
    if (!(temp_v0 & 0xFF) || (temp_v0_2 = ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v - 0x100, ((Rec_D_80082E80 *)arg2)->unk_1C.at02_u16.v = temp_v0_2, ((Rec_D_80082E80 *)arg2)->unk_1C.at00_u16.v = temp_v0_2, ((Rec_D_80082E80 *)arg2)->unk_1A.as_u16 = (u16) ((S_8002455C_0 *)arg0)->unk_2E, func_800478B8(arg2), ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) != 0))) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8002455C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Two six-byte vector aggregates force stack slots sp+0x10..0x14 and sp+0x18..0x1C,
   restoring the 0x30 frame and the s0/s1/s2-only save set.
   cdk -G0 plus a direct scalar D_800814A0 RMW removes the extra address addiu and closes the residue. */
