#include "common.h"
#include "m2c_compat.h"

typedef struct S_819A1118_0_pre {
    u16 unk_00;
} S_819A1118_0_pre;   /* the 0x2 bytes before arg0 in func_819A1118, addressed as arg0[-1] */

typedef struct S_819A1118_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u8 pad_40[0x14];
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    s16 unk_76;
} S_819A1118_0;   /* arg0 in func_819A1118 */

typedef struct S_819A1118_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_819A1118_1;   /* var_a0 in func_819A1118 */


extern s16 D_800261B0[];
extern s32 D_800814A0;

/* Advance effect interpolation, fade its four colors, and flag expiration. */
void func_819A1118(void *effect) {
    s32 blend_ticks;
    s32 elapsed_ticks;
    s32 color_index;
    u16 ticks_left;
    void *color_ptr;

    ticks_left = ((S_819A1118_0 *)effect)->unk_3A - 1;
    D_800261B0[0] = 1;
    blend_ticks = ((S_819A1118_0 *)effect)->unk_3E;
    ((S_819A1118_0 *)effect)->unk_3A = ticks_left;
    elapsed_ticks = ((S_819A1118_0 *)effect)->unk_3C - (s16) ticks_left;
    if (blend_ticks >= elapsed_ticks) {
        ((S_819A1118_0 *)effect)->unk_54 = (s16) (((S_819A1118_0 *)effect)->unk_60 + ((s32) (((S_819A1118_0 *)effect)->unk_6C * elapsed_ticks) / blend_ticks));
        ((S_819A1118_0 *)effect)->unk_56 = (s16) (((S_819A1118_0 *)effect)->unk_62 + ((s32) (((S_819A1118_0 *)effect)->unk_6E * (((S_819A1118_0 *)effect)->unk_3C - (s16) ((S_819A1118_0 *)effect)->unk_3A)) / (s16) ((S_819A1118_0 *)effect)->unk_3E));
        ((S_819A1118_0 *)effect)->unk_58 = (s16) (((S_819A1118_0 *)effect)->unk_64 + ((s32) (((S_819A1118_0 *)effect)->unk_70 * (((S_819A1118_0 *)effect)->unk_3C - (s16) ((S_819A1118_0 *)effect)->unk_3A)) / (s16) ((S_819A1118_0 *)effect)->unk_3E));
        ((S_819A1118_0 *)effect)->unk_5A = (s16) (((S_819A1118_0 *)effect)->unk_66 + ((s32) (((S_819A1118_0 *)effect)->unk_72 * (((S_819A1118_0 *)effect)->unk_3C - (s16) ((S_819A1118_0 *)effect)->unk_3A)) / (s16) ((S_819A1118_0 *)effect)->unk_3E));
        ((S_819A1118_0 *)effect)->unk_5C = (s16) (((S_819A1118_0 *)effect)->unk_68 + ((s32) (((S_819A1118_0 *)effect)->unk_74 * (((S_819A1118_0 *)effect)->unk_3C - (s16) ((S_819A1118_0 *)effect)->unk_3A)) / (s16) ((S_819A1118_0 *)effect)->unk_3E));
        ((S_819A1118_0 *)effect)->unk_5E = (s16) (((S_819A1118_0 *)effect)->unk_6A + ((s32) (((S_819A1118_0 *)effect)->unk_76 * (((S_819A1118_0 *)effect)->unk_3C - (s16) ((S_819A1118_0 *)effect)->unk_3A)) / (s16) ((S_819A1118_0 *)effect)->unk_3E));
    }
    color_index = 0;
    color_ptr = effect;
    do {
        ((S_819A1118_1 *)color_ptr)->unk_0C = (s8) ((s32) (((S_819A1118_1 *)color_ptr)->unk_1C * (s16) ((S_819A1118_0 *)effect)->unk_3A) / (s16) ((S_819A1118_0 *)effect)->unk_3C);
        ((S_819A1118_1 *)color_ptr)->unk_0D = (s8) ((s32) (((S_819A1118_1 *)color_ptr)->unk_1D * (s16) ((S_819A1118_0 *)effect)->unk_3A) / (s16) ((S_819A1118_0 *)effect)->unk_3C);
        color_index += 1;
        ((S_819A1118_1 *)color_ptr)->unk_0E = (s8) ((s32) (((S_819A1118_1 *)color_ptr)->unk_1E * (s16) ((S_819A1118_0 *)effect)->unk_3A) / (s16) ((S_819A1118_0 *)effect)->unk_3C);
        color_ptr += 4;
    } while (color_index < 4);
    if ((s16) ((S_819A1118_0 *)effect)->unk_3A <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_819A1118_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
