#include "common.h"

typedef struct S_80171284_0 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x1F];
    union { u16 s; s16 u; } unk_24;   /* accessed as both */
    u8 pad_26[0x4];
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x20];
    u16 unk_4E;
    u16 unk_50;
} S_80171284_0;   /* arg0 in func_80171284 */

typedef struct S_80171284_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80171284_1;   /* arg1 in func_80171284 */

typedef struct S_80171284_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80171284_2;   /* arg2 in func_80171284 */



extern s32 D_800814A0;

/* Update the effect countdown and motion, fade its color, and flag expiration. */
void func_80171284(void *effect, void *transform, void *color) {
    u16 next_value;
    u16 next_total;
    s16 ticks_left;

    next_value = ((S_80171284_0 *)effect)->unk_24.s - 1;
    ((S_80171284_0 *)effect)->unk_24.s = next_value;
    if ((s16)next_value < 8) {
        ((S_80171284_0 *)effect)->unk_4E = ((S_80171284_0 *)effect)->unk_4E - 1;
    }

    if ((s16)((S_80171284_0 *)effect)->unk_4E < 2) {
        ((S_80171284_0 *)effect)->unk_4E = 2;
    }

    if ((s16)((S_80171284_0 *)effect)->unk_24.s < 10) {
        next_value = ((S_80171284_0 *)effect)->unk_2A + 1;
        next_total = ((S_80171284_0 *)effect)->unk_50 + next_value;
        ((S_80171284_0 *)effect)->unk_2A = next_value;
        ((S_80171284_0 *)effect)->unk_50 = next_total;
    } else {
        ((S_80171284_0 *)effect)->unk_50 = ((S_80171284_0 *)effect)->unk_50 + 1;
    }

    if ((s16)((S_80171284_0 *)effect)->unk_24.s < 11) {
        next_value = ((S_80171284_0 *)effect)->unk_2C + 2;
        ((S_80171284_0 *)effect)->unk_2C = next_value;
        ((S_80171284_1 *)transform)->unk_0A = ((S_80171284_1 *)transform)->unk_0A - next_value;
    }

    ticks_left = ((S_80171284_0 *)effect)->unk_24.u;
    if (ticks_left < 5) {
        ((S_80171284_2 *)color)->unk_0C = (((S_80171284_0 *)effect)->unk_02 * ticks_left) / 5;
        ((S_80171284_2 *)color)->unk_0D = (((S_80171284_0 *)effect)->unk_03 * ((S_80171284_0 *)effect)->unk_24.u) / 5;
        ((S_80171284_2 *)color)->unk_0E = (((S_80171284_0 *)effect)->unk_04 * ((S_80171284_0 *)effect)->unk_24.u) / 5;
    }

    if (((S_80171284_0 *)effect)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
