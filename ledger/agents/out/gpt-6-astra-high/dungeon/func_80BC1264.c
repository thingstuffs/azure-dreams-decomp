#include "common.h"
#include "m2c_compat.h"

typedef struct S_80BC1264_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80BC1264_0;   /* arg1 in func_80BC1264 */

typedef struct S_80BC1264_1_pre {
    u16 unk_00;
} S_80BC1264_1_pre;   /* the 0x2 bytes before arg0 in func_80BC1264, addressed as arg0[-1] */

typedef struct S_80BC1264_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x6];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80BC1264_1;   /* arg0 in func_80BC1264 */

typedef struct S_80BC1264_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80BC1264_2;   /* D_80080000 in func_80BC1264 */


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern s32 D_800814A0[3];
extern u8 D_80080000[];

/* Advance the effect motion, fade its color, and flag it near its target or when faded out. */
void func_80BC1264(void *effect, void *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 x_distance;
    s32 y_distance;
    s32 scaled_blue;

    ((S_80BC1264_0 *)position)->unk_00.at00.v = (s32) (((S_80BC1264_0 *)position)->unk_00.at00.v + ((S_80BC1264_1 *)effect)->unk_40);
    ((S_80BC1264_0 *)position)->unk_04.at00.v = (s32) (((S_80BC1264_0 *)position)->unk_04.at00.v + ((S_80BC1264_1 *)effect)->unk_44);
    ((S_80BC1264_0 *)position)->unk_08 = (s32) (((S_80BC1264_0 *)position)->unk_08 + ((S_80BC1264_1 *)effect)->unk_48);
    ((S_80BC1264_1 *)effect)->unk_40 = (s32) (((S_80BC1264_1 *)effect)->unk_40 + ((S_80BC1264_1 *)effect)->unk_4C);
    ((S_80BC1264_1 *)effect)->unk_44 = (s32) (((S_80BC1264_1 *)effect)->unk_44 + ((S_80BC1264_1 *)effect)->unk_50);
    ((S_80BC1264_1 *)effect)->unk_48 = (s32) (((S_80BC1264_1 *)effect)->unk_48 + ((S_80BC1264_1 *)effect)->unk_54);
    x_distance = abs(((S_80BC1264_1 *)effect)->unk_36 - ((S_80BC1264_0 *)position)->unk_00.at02.v);
    if (x_distance < 0x10) {
        y_distance = abs(((S_80BC1264_1 *)effect)->unk_38 - ((S_80BC1264_0 *)position)->unk_04.at02.v);
        if (y_distance < 0x10) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80BC1264_1_pre *)effect)[-1].unk_00 | 0x8000);
            (*(s32 *)((u8 *)D_80080000 + 0x14A0)) = (s32) (((S_80BC1264_2 *)D_80080000)->unk_14A0 | 0x8000);
        }
    }
    scaled_red = ((S_80BC1264_1 *)effect)->unk_00 * ((S_80BC1264_1 *)effect)->unk_32;
    if (scaled_red < 0) {
        scaled_red += 0xFF;
    }
    ((S_80BC1264_1 *)effect)->unk_04.at00.v = (s8) (scaled_red >> 8);
    scaled_green = ((S_80BC1264_1 *)effect)->unk_01 * ((S_80BC1264_1 *)effect)->unk_32;
    if (scaled_green < 0) {
        scaled_green += 0xFF;
    }
    ((S_80BC1264_1 *)effect)->unk_04.at01.v = (s8) (scaled_green >> 8);
    scaled_blue = ((S_80BC1264_1 *)effect)->unk_02 * ((S_80BC1264_1 *)effect)->unk_32;
    if (scaled_blue < 0) {
        scaled_blue += 0xFF;
    }
    ((S_80BC1264_1 *)effect)->unk_04.at02.v = (s8) (scaled_blue >> 8);
    fade_level = (u16) ((S_80BC1264_1 *)effect)->unk_32 - 8;
    ((S_80BC1264_1 *)effect)->unk_32 = fade_level;
    ((S_80BC1264_1 *)effect)->unk_08 = (s32) ((S_80BC1264_1 *)effect)->unk_04.at00u.v;
    if ((fade_level << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_80BC1264_1_pre *)effect)[-1].unk_00 | 0x8000);
        (*(s32 *)((u8 *)D_80080000 + 0x14A0)) = (s32) (((S_80BC1264_2 *)D_80080000)->unk_14A0 | 0x8000);
    }
}
