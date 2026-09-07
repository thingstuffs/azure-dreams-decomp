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

/* Advance effect positions, fade the color, and flag expiration when the timer ends. */
void func_8002744C(void *effect, void *positions, void *color) {
    s16 ticks_left;
    u8 intensity;

    ((S_8002744C_0 *)positions)->unk_00 += ((S_8002744C_1 *)effect)->unk_0C;
    ((S_8002744C_0 *)positions)->unk_04 += ((S_8002744C_1 *)effect)->unk_10;
    ((S_8002744C_0 *)positions)->unk_08 += ((S_8002744C_1 *)effect)->unk_14;

    ((S_8002744C_0 *)positions)->unk_0C += ((S_8002744C_1 *)effect)->unk_0C >> 1;
    ((S_8002744C_0 *)positions)->unk_10 += ((S_8002744C_1 *)effect)->unk_10 >> 1;
    ((S_8002744C_0 *)positions)->unk_14 += ((S_8002744C_1 *)effect)->unk_14 >> 1;

    intensity = ((S_8002744C_2 *)color)->unk_0C;
    intensity -= intensity / ((S_8002744C_1 *)effect)->unk_66;
    ((S_8002744C_2 *)color)->unk_0C = intensity;
    ((S_8002744C_2 *)color)->unk_0D = intensity;
    ((S_8002744C_2 *)color)->unk_0E = intensity;

    ticks_left = (u16)((S_8002744C_1 *)effect)->unk_66 - 1;
    ((S_8002744C_1 *)effect)->unk_66 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
