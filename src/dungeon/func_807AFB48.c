#include "common.h"
#include "m2c_compat.h"

typedef struct S_807AFB48_3 {
    void * unk_00;
    void * unk_04;
} S_807AFB48_3;   /* arg0 in func_807AFB48 */

typedef struct S_807AFB48_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_4;   /* ((S_807AFB48_3 *)arg0)->unk_04 in func_807AFB48 */

typedef struct S_807AFB48_5 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFB48_5;   /* ((S_807AFB48_3 *)arg0)->unk_00 in func_807AFB48 */


typedef struct S_807AFB48_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_0;   /* arg1 in func_807AFB48 */

typedef struct S_807AFB48_1 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
} S_807AFB48_1;   /* arg0 in func_807AFB48; pointer addresses record offset 0x2 */

typedef struct S_807AFB48_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_807AFB48_2;   /* arg2 in func_807AFB48 */


extern s32 D_800814A0[3];

/* Advances position and selected color channels toward their targets and flags completion. */
void func_807AFB48(void *transition, S_807AFB48_0 *position, S_807AFB48_2 *color) {
    s16 steps_left;
    s32 color_bits;
    u8 next_level;

    position->unk_02 = (s16) ((u16) position->unk_02 + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_02 - position->unk_02) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    position->unk_06 = (s16) ((u16) position->unk_06 + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_06 - position->unk_06) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    position->unk_0A = (s16) ((u16) position->unk_0A + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_0A - position->unk_0A) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    color_bits = color->unk_0E | (color->unk_0C | color->unk_0D);
    next_level = color_bits + ((s32) (0xC0 - color_bits) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E);
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 1) {
        color->unk_0C = next_level;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 2) {
        color->unk_0E = next_level;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 4) {
        color->unk_0D = next_level;
    }
    steps_left = (u16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E - 1;
    ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E = steps_left;
    if ((steps_left << 0x10) <= 0) {
        ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_00 = (u16) (((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
