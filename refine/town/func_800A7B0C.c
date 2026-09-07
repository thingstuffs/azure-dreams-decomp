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

/* Interpolate three state components toward their targets and advance the transition when complete. */
void func_800A526C(S_800A526C_1 *transition)
{
    u8 *state_base;
    s32 ticks_left;
    u16 target_component;

    state_base = D_80083160;
    ((S_800A526C_0 *)state_base)->unk_AC.s =
        ((S_800A526C_0 *)state_base)->unk_AC.u +
        ((transition->unk_00.s - ((S_800A526C_0 *)state_base)->unk_AC.s) /
         transition->unk_18);
    ((S_800A526C_0 *)state_base)->unk_AE.s =
        ((S_800A526C_0 *)state_base)->unk_AE.u +
        ((transition->unk_02.s - ((S_800A526C_0 *)state_base)->unk_AE.s) /
         transition->unk_18);
    ((S_800A526C_0 *)state_base)->unk_B0.s =
        ((S_800A526C_0 *)state_base)->unk_B0.u +
        ((transition->unk_04.s - ((S_800A526C_0 *)state_base)->unk_B0.s) /
         transition->unk_18);

    ticks_left = transition->unk_18 - 1;
    transition->unk_18 = ticks_left;
    if (ticks_left <= 0) {
        target_component = transition->unk_00.u;
        transition->unk_10 = target_component;
        ((S_800A526C_0 *)state_base)->unk_AC.u = target_component;

        target_component = transition->unk_02.u;
        transition->unk_12 = target_component;
        ((S_800A526C_0 *)state_base)->unk_AE.u = target_component;

        target_component = transition->unk_04.u;
        transition->unk_14 = target_component;
        ((S_800A526C_0 *)state_base)->unk_B0.u = target_component;

        transition->unk_20 = D_800A51CC;
    }
}
