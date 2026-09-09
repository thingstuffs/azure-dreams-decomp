#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80024E80_arg1.h"

M2C_UNK func_80024E80();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern s32 D_800814A0;


typedef struct S_80025094_0_pre {
    u16 unk_00;
} S_80025094_0_pre;   /* the 0x2 bytes before arg0 in func_80025094, addressed as arg0[-1] */

typedef struct S_80025094_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} S_80025094_0;   /* arg0 in func_80025094 */

typedef struct S_80025094_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025094_1;   /* temp_v1 in func_80025094 */

/* Advances the effect phase, brightness, scale, and position until its lifetime ends. */
void func_80025094(void *effect, void *transform, void *visual) {
    s32 scale;
    s16 phase;
    u8 brightness;
    void *owner;

    owner = ((S_80025094_0 *)effect)->unk_00;
    ((S_80025094_1 *)owner)->unk_14 = (u16) (((S_80025094_1 *)owner)->unk_14 + 1);
    func_800478B8(visual);
    ((S_80025094_0 *)effect)->unk_06.u = (u16) (((S_80025094_0 *)effect)->unk_06.u + 1);
    ((Rec_D_80082E80 *)visual)->unk_1A.as_u16 = (u16) (((Rec_D_80082E80 *)visual)->unk_1A.as_u16 + 0x200);
    phase = ((S_80025094_0 *)effect)->unk_04.s;

    if (phase == 1) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        goto common;
    }
    if (phase == 2) {
        goto state_2;
    }
    goto common;

state_0:
    {
        u16 radius;

        if (((S_80025094_0 *)effect)->unk_06.u & 1) {
            radius = ((S_80025094_0 *)effect)->unk_0A + 2;
        } else {
            radius = ((S_80025094_0 *)effect)->unk_0A + 1;
        }
        ((S_80025094_0 *)effect)->unk_0A = radius;
    }
    brightness = ((Rec_D_80082E80 *)visual)->unk_0C.at02_u8.v + 3;
    ((Rec_D_80082E80 *)visual)->unk_0C.at02_u8.v = brightness;
    ((Rec_D_80082E80 *)visual)->unk_0C.at01_u8.v = brightness;
    ((Rec_D_80082E80 *)visual)->unk_0C.at00_u8.v = brightness;
    scale = ((S_80025094_0 *)effect)->unk_06.s << 5;
    ((Rec_D_80082E80 *)visual)->unk_1C.at02_s16.v = scale;
    ((Rec_D_80082E80 *)visual)->unk_1C.at00_s16.v = scale;
    ((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v =
        (u16) (((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v - 2);

state_1:
    if ((s16) ((S_80025094_0 *)effect)->unk_06.u >= 0x20) {
        ((S_80025094_0 *)effect)->unk_06.u = 0U;
        ((S_80025094_0 *)effect)->unk_04.u =
            (u16) (((S_80025094_0 *)effect)->unk_04.u + 1);
        goto common;
    }
    goto common;

state_2:
    if ((s16) ((S_80025094_0 *)effect)->unk_06.u >=
            ((S_80025094_0 *)effect)->unk_08) {
        func_80024E80(effect, transform);
        (*(u16 *)((u8 *)effect + (-2))) =
            (u16) (((S_80025094_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        return;
    }

common:
    ((Rec_func_80024E80_arg1 *)transform)->unk_00.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_0E + ((s32) ((func_80064584(((S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)effect)->unk_0A) >> 8));
    ((Rec_func_80024E80_arg1 *)transform)->unk_04.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_12 + ((s32) ((func_800644B8(((S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((S_80025094_0 *)effect)->unk_0A) >> 8));
}
