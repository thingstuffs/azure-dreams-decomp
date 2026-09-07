#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D4CB0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4CB0_0;   /* arg1 in func_800D4CB0 */

typedef struct S_800D4CB0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800D4CB0_1;   /* arg2 in func_800D4CB0 */

typedef struct S_800D4CB0_2_pre {
    u16 unk_00;
} S_800D4CB0_2_pre;   /* the 0x2 bytes before arg0 in func_800D4CB0, addressed as arg0[-1] */

typedef struct S_800D4CB0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xF];
    s16 unk_1E;
    s16 unk_20;
} S_800D4CB0_2;   /* arg0 in func_800D4CB0 */


extern M2C_UNK D_800814A0;

/* Advance and damp motion, fade the effect color, and flag expiration. */
void func_800D4CB0(void *effect, void *motion, void *color) {
    s16 ticks_left;

    ((S_800D4CB0_0 *)motion)->unk_00 += ((S_800D4CB0_0 *)motion)->unk_0C;
    ((S_800D4CB0_0 *)motion)->unk_04 += ((S_800D4CB0_0 *)motion)->unk_10;
    ((S_800D4CB0_0 *)motion)->unk_08 += ((S_800D4CB0_0 *)motion)->unk_14;
    ((S_800D4CB0_0 *)motion)->unk_0C /= 2;
    ((S_800D4CB0_0 *)motion)->unk_10 /= 2;
    ((S_800D4CB0_0 *)motion)->unk_14 /= 2;
    ((S_800D4CB0_1 *)color)->unk_0C = (s8) ((s32) (((S_800D4CB0_2 *)effect)->unk_0C * ((S_800D4CB0_2 *)effect)->unk_1E) / (s16) ((S_800D4CB0_2 *)effect)->unk_20);
    ((S_800D4CB0_1 *)color)->unk_0D = (s8) ((s32) (((S_800D4CB0_2 *)effect)->unk_0D * ((S_800D4CB0_2 *)effect)->unk_1E) / (s16) ((S_800D4CB0_2 *)effect)->unk_20);
    ((S_800D4CB0_1 *)color)->unk_0E = (s8) ((s32) (((S_800D4CB0_2 *)effect)->unk_0E * ((S_800D4CB0_2 *)effect)->unk_1E) / (s16) ((S_800D4CB0_2 *)effect)->unk_20);
    ticks_left = (u16) ((S_800D4CB0_2 *)effect)->unk_1E - 1;
    ((S_800D4CB0_2 *)effect)->unk_1E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800D4CB0_2_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
