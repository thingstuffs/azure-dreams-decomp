#include "common.h"

typedef struct S_800A526C_0 {
    u8 pad_00[0xAC];
    union { s16 s; u16 u; } unk_AC;   /* accessed as both */
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_800A526C_0;   /* base in func_800A526C */

typedef struct S_800A526C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0xA];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
} S_800A526C_1;   /* arg0 in func_800A526C */



extern u8 D_80083160[0xB2];
extern u8 D_800A51CC[16];

void func_800A526C(S_800A526C_1 *arg0)
{
    u8 *base;
    s32 timer;
    u16 component;

    base = D_80083160;
    ((S_800A526C_0 *)base)->unk_AC.s =
        ((S_800A526C_0 *)base)->unk_AC.u +
        ((arg0->unk_00.s - ((S_800A526C_0 *)base)->unk_AC.s) /
         arg0->unk_18);
    ((S_800A526C_0 *)base)->unk_AE.s =
        ((S_800A526C_0 *)base)->unk_AE.u +
        ((arg0->unk_02.s - ((S_800A526C_0 *)base)->unk_AE.s) /
         arg0->unk_18);
    ((S_800A526C_0 *)base)->unk_B0.s =
        ((S_800A526C_0 *)base)->unk_B0.u +
        ((arg0->unk_04.s - ((S_800A526C_0 *)base)->unk_B0.s) /
         arg0->unk_18);

    timer = arg0->unk_18 - 1;
    arg0->unk_18 = timer;
    if (timer <= 0) {
        component = arg0->unk_00.u;
        arg0->unk_10 = component;
        ((S_800A526C_0 *)base)->unk_AC.u = component;

        component = arg0->unk_02.u;
        arg0->unk_12 = component;
        ((S_800A526C_0 *)base)->unk_AE.u = component;

        component = arg0->unk_04.u;
        arg0->unk_14 = component;
        ((S_800A526C_0 *)base)->unk_B0.u = component;

        arg0->unk_20 = D_800A51CC;
    }
}
