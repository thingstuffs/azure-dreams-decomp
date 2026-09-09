#include "common.h"

typedef struct S_800250E8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800250E8_0;   /* arg1 in func_800250E8 */

typedef struct S_800250E8_1_pre {
    u16 unk_00;
} S_800250E8_1_pre;   /* the 0x2 bytes before arg0 in func_800250E8, addressed as arg0[-1] */

typedef struct S_800250E8_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x8];
    s16 unk_26;
} S_800250E8_1;   /* arg0 in func_800250E8 */

typedef struct S_800250E8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800250E8_2;   /* tail_arg in func_800250E8 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80069EF8(void);
extern s16 func_800BCB04(u16, u16, s16);

extern u16 D_800257CE[5];
extern s32 D_800814A0[3];

__asm__(".set D_800257CE, 0x800257CE");

/* Updates effect motion and marks it inactive when its lifetime or owner expires. */
void func_800250E8(void *effect, S_800250E8_0 *motion, void *owner)
{
    register void *owner_state ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 life_left;
    s32 y_step;
    s32 z_velocity;
    s32 z_position;
    register s32 z_velocity_copy ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 y_motion;
    s32 random_value;
    s32 x_direction;
    s32 y_direction;
    s32 x;
    s32 y;
    s16 probe_z;
    u16 counter;
    u16 *counter_ptr;

    owner_state = owner;
    ASM_KEEP_NV(owner_state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    counter_ptr = D_800257CE;
    x = motion->unk_00.at02.v;
    counter = counter_ptr[0];
    probe_z = motion->unk_08.at02.v;
    y = motion->unk_04.at02.v;
    counter++;
    probe_z -= 2;
    counter_ptr[0] = counter;
    if (motion->unk_08.at02u.v <
        func_800BCB04(x, y, probe_z)) {
        if (((S_800250E8_1 *)effect)->unk_26 == 0) {
            x_direction = func_80064584(((S_800250E8_1 *)effect)->unk_1A);
            motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v +
                (((s32)(x_direction * ((S_800250E8_1 *)effect)->unk_1C.s) >> 4) +
                 (func_80069EF8() & 0xFFFF)));

            y_direction = func_800644B8(((S_800250E8_1 *)effect)->unk_1A);
            y_step = ((y_direction * ((S_800250E8_1 *)effect)->unk_1C.s) >> 4) +
                       (func_80069EF8() & 0xFFFF);
            motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + y_step);

            random_value = func_80069EF8();
            motion->unk_08.at00.v = (s32)(motion->unk_08.at00.v +
                (0xFFFE0000 - (random_value & 0xFFF)));
        } else {
            motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v +
                func_80064584(((S_800250E8_1 *)effect)->unk_1A) *
                ((S_800250E8_1 *)effect)->unk_1C.s * 8);
            y_motion = func_800644B8(((S_800250E8_1 *)effect)->unk_1A) *
                      ((S_800250E8_1 *)effect)->unk_1C.s;
            z_velocity = motion->unk_14;
            z_velocity_copy = z_velocity;
            ASM_KEEP_NV(z_velocity_copy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            z_position = motion->unk_08.at00.v;
            motion->unk_14 = z_velocity_copy + 0x6000;
            motion->unk_08.at00.v = (s32)(z_position + z_velocity);
            motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + y_motion * 8);
        }
    }

    life_left = ((S_800250E8_1 *)effect)->unk_1C.u - 1;
    ((S_800250E8_1 *)effect)->unk_1C.s = life_left;
    if ((life_left << 16) <= 0 ||
        (((S_800250E8_2 *)owner_state)->unk_14 & 0x8000)) {
        ((S_800250E8_1_pre *)effect)[-1].unk_00 = (u16)(((S_800250E8_1_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
