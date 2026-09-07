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

void func_80BC1264(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    ((S_80BC1264_0 *)arg1)->unk_00.at00.v = (s32) (((S_80BC1264_0 *)arg1)->unk_00.at00.v + ((S_80BC1264_1 *)arg0)->unk_40);
    ((S_80BC1264_0 *)arg1)->unk_04.at00.v = (s32) (((S_80BC1264_0 *)arg1)->unk_04.at00.v + ((S_80BC1264_1 *)arg0)->unk_44);
    ((S_80BC1264_0 *)arg1)->unk_08 = (s32) (((S_80BC1264_0 *)arg1)->unk_08 + ((S_80BC1264_1 *)arg0)->unk_48);
    ((S_80BC1264_1 *)arg0)->unk_40 = (s32) (((S_80BC1264_1 *)arg0)->unk_40 + ((S_80BC1264_1 *)arg0)->unk_4C);
    ((S_80BC1264_1 *)arg0)->unk_44 = (s32) (((S_80BC1264_1 *)arg0)->unk_44 + ((S_80BC1264_1 *)arg0)->unk_50);
    ((S_80BC1264_1 *)arg0)->unk_48 = (s32) (((S_80BC1264_1 *)arg0)->unk_48 + ((S_80BC1264_1 *)arg0)->unk_54);
    var_v0 = abs(((S_80BC1264_1 *)arg0)->unk_36 - ((S_80BC1264_0 *)arg1)->unk_00.at02.v);
    if (var_v0 < 0x10) {
        var_v0_2 = abs(((S_80BC1264_1 *)arg0)->unk_38 - ((S_80BC1264_0 *)arg1)->unk_04.at02.v);
        if (var_v0_2 < 0x10) {
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80BC1264_1_pre *)arg0)[-1].unk_00 | 0x8000);
            (*(s32 *)((u8 *)D_80080000 + 0x14A0)) = (s32) (((S_80BC1264_2 *)D_80080000)->unk_14A0 | 0x8000);
        }
    }
    var_a0 = ((S_80BC1264_1 *)arg0)->unk_00 * ((S_80BC1264_1 *)arg0)->unk_32;
    if (var_a0 < 0) {
        var_a0 += 0xFF;
    }
    ((S_80BC1264_1 *)arg0)->unk_04.at00.v = (s8) (var_a0 >> 8);
    var_a1 = ((S_80BC1264_1 *)arg0)->unk_01 * ((S_80BC1264_1 *)arg0)->unk_32;
    if (var_a1 < 0) {
        var_a1 += 0xFF;
    }
    ((S_80BC1264_1 *)arg0)->unk_04.at01.v = (s8) (var_a1 >> 8);
    var_v1 = ((S_80BC1264_1 *)arg0)->unk_02 * ((S_80BC1264_1 *)arg0)->unk_32;
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    ((S_80BC1264_1 *)arg0)->unk_04.at02.v = (s8) (var_v1 >> 8);
    temp_v0 = (u16) ((S_80BC1264_1 *)arg0)->unk_32 - 8;
    ((S_80BC1264_1 *)arg0)->unk_32 = temp_v0;
    ((S_80BC1264_1 *)arg0)->unk_08 = (s32) ((S_80BC1264_1 *)arg0)->unk_04.at00u.v;
    if ((temp_v0 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80BC1264_1_pre *)arg0)[-1].unk_00 | 0x8000);
        (*(s32 *)((u8 *)D_80080000 + 0x14A0)) = (s32) (((S_80BC1264_2 *)D_80080000)->unk_14A0 | 0x8000);
    }
}
