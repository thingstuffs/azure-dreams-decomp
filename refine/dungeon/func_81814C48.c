#include "common.h"

typedef struct S_81814C48_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81814C48_0;   /* arg1 in func_81814C48 */

typedef struct S_81814C48_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_81814C48_1;   /* arg0 in func_81814C48 */

typedef struct S_81814C48_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81814C48_2;   /* arg2 in func_81814C48 */



extern s32 rand();
extern s16 func_800BCB04();
extern s16 D_80025338;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;

/* Updates a position with randomized motion, reduces speed, and flags completion. */
void func_81814C48(void *state, void *position, void *linked_state)
{
    s16 speed;
    s32 x_step;
    s32 y_step;
    s32 coord_value;
    s32 z_random;
    s32 x;
    s32 y;
    s32 z;
    register s32 z_step ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */

    z = (*(u16 *)((u8 *)position + 0xA));
    x = ((S_81814C48_0 *)position)->unk_00.at02.v;
    y = ((S_81814C48_0 *)position)->unk_04.at02.v;
    D_80025338 = 1;
    if ((s16)((S_81814C48_0 *)position)->unk_08.at02.v <
        func_800BCB04(x, y, (s16)(z + 2))) {
        x_step = ((*(s16 *)(&D_8006CCD8 + (((S_81814C48_1 *)state)->unk_14 * 2)) *
                    ((S_81814C48_1 *)state)->unk_32) << 9) +
                  (rand() & 0xFFFF);
        coord_value = ((S_81814C48_0 *)position)->unk_00.at00.v + x_step;
        ((S_81814C48_0 *)position)->unk_00.at00.v = coord_value;
        y_step = ((*(s16 *)(&D_8006CCE8 + (((S_81814C48_1 *)state)->unk_14 * 2)) *
                      ((S_81814C48_1 *)state)->unk_32) << 9) +
                    (rand(x_step) & 0xFFFF);
        coord_value = ((S_81814C48_0 *)position)->unk_04.at00.v + y_step;
        ((S_81814C48_0 *)position)->unk_04.at00.v = coord_value;
        z_random = rand(y_step);
        z_step = 0xFFFE0000;
        coord_value = ((S_81814C48_0 *)position)->unk_08.at00.v + z_step;
        coord_value -= z_random & 0xFFF;
        ((S_81814C48_0 *)position)->unk_08.at00.v = coord_value;
    }
    speed = (u16)((S_81814C48_1 *)state)->unk_32 - 8;
    ((S_81814C48_1 *)state)->unk_32 = speed;
    if (((speed << 16) <= 0) || (((S_81814C48_2 *)linked_state)->unk_14 & 0x8000)) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Guarded a0/a1/a2 call-argument pins fence D_80025338 without
   growing the retail 0x20 s1/s0/s2 frame. Byte table bases with s16 loads
   plus explicit accumulator RMWs place each lw before mflo. A tail a0
   constant pin and direct D_800814A0 scalar RMW remove the two cascades. */
