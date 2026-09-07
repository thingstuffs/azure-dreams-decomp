#include "common.h"

typedef struct S_8002744C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002744C_0;   /* arg1 in func_8002744C */

typedef struct S_8002744C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x4E];
    s16 unk_66;
} S_8002744C_1;   /* arg0 in func_8002744C */

typedef struct S_8002744C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_8002744C_2;   /* arg2 in func_8002744C */



extern s32 D_800814A0;

void func_8002744C(void *arg0, void *arg1, void *arg2) {
    s16 timer;
    u8 intensity;

    ((S_8002744C_0 *)arg1)->unk_00 += ((S_8002744C_1 *)arg0)->unk_0C;
    ((S_8002744C_0 *)arg1)->unk_04 += ((S_8002744C_1 *)arg0)->unk_10;
    ((S_8002744C_0 *)arg1)->unk_08 += ((S_8002744C_1 *)arg0)->unk_14;

    ((S_8002744C_0 *)arg1)->unk_0C += ((S_8002744C_1 *)arg0)->unk_0C >> 1;
    ((S_8002744C_0 *)arg1)->unk_10 += ((S_8002744C_1 *)arg0)->unk_10 >> 1;
    ((S_8002744C_0 *)arg1)->unk_14 += ((S_8002744C_1 *)arg0)->unk_14 >> 1;

    intensity = ((S_8002744C_2 *)arg2)->unk_0C;
    intensity -= intensity / ((S_8002744C_1 *)arg0)->unk_66;
    ((S_8002744C_2 *)arg2)->unk_0C = intensity;
    ((S_8002744C_2 *)arg2)->unk_0D = intensity;
    ((S_8002744C_2 *)arg2)->unk_0E = intensity;

    timer = (u16)((S_8002744C_1 *)arg0)->unk_66 - 1;
    ((S_8002744C_1 *)arg0)->unk_66 = timer;
    if ((timer << 16) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
