#include "common.h"
#include "m2c_compat.h"

typedef struct S_800220A8_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_800220A8_0;   /* arg0 in func_800220A8 */

typedef struct S_800220A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800220A8_1;   /* arg1 in func_800220A8 */

typedef struct S_800220A8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800220A8_2;   /* ((S_800220A8_0 *)arg0)->unk_04 in func_800220A8 */


M2C_UNK func_800644B8();
extern M2C_UNK D_800814A0;

/* Update motion through approach, oscillation, and withdrawal, flagging completion. */
void func_800220A8(void *motion_state, void *motion) {
    s16 state;
    s32 phase_two;

    phase_two = 2;
    if (((S_800220A8_2 *)(((S_800220A8_0 *)motion_state)->unk_04))->unk_18 == phase_two) {
        ((S_800220A8_0 *)motion_state)->unk_00 = 3;
    }
    state = ((S_800220A8_0 *)motion_state)->unk_00;
    if (state != phase_two) {
        if (state < 3) {
            if (state != 0) {
                if (state == 1) {
                    goto accelerate;
                }
                return;
            }
            goto approach;
        }
        if (state != 3) {
            if (state != 0xF0) {
                return;
            }
            goto oscillate;
        }
        goto withdraw;
    }
    goto decelerate;

approach:
    if ((((S_800220A8_1 *)motion)->unk_08 += 0x100000) < (s32)0xFF900000) {
        return;
    }
    ((S_800220A8_0 *)motion_state)->unk_02 = 0;
    ((S_800220A8_1 *)motion)->unk_14 = -0x40000;
    goto start_acceleration;

accelerate:
{
    s32 velocity;
    register s32 next_velocity ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 position;

    velocity = ((S_800220A8_1 *)motion)->unk_14;
    next_velocity = velocity;
    ASM_KEEP_NV(next_velocity);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    position = ((S_800220A8_1 *)motion)->unk_08;
    position += velocity;
    next_velocity += 0x4000;
    ((S_800220A8_1 *)motion)->unk_08 = position;
    ((S_800220A8_1 *)motion)->unk_14 = next_velocity;
    if (next_velocity != 0x40000) {
        return;
    }
    ((S_800220A8_0 *)motion_state)->unk_00 = phase_two;
    return;
}

decelerate:
{
    register s32 position_or_velocity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 velocity_step;

    position_or_velocity = ((S_800220A8_1 *)motion)->unk_08;
    velocity_step = ((S_800220A8_1 *)motion)->unk_14;
    position_or_velocity += velocity_step;
    ((S_800220A8_1 *)motion)->unk_08 = position_or_velocity;
    position_or_velocity = velocity_step;
    velocity_step = -0x8000;
    position_or_velocity += velocity_step;
    ((S_800220A8_1 *)motion)->unk_14 = position_or_velocity;
    if (position_or_velocity != -0x40000) {
        return;
    }
}

start_acceleration:
    ((S_800220A8_0 *)motion_state)->unk_00 = 1;
    return;

oscillate:
{
    u16 phase;
    s32 position;
    s32 base_position;

    phase = (((S_800220A8_0 *)motion_state)->unk_02 + 1) & 0x7F;
    ((S_800220A8_0 *)motion_state)->unk_02 = phase;
    position = func_800644B8(phase << 6, phase_two, motion_state);
    position <<= 7;
    base_position = (s32)0xFF900000;
    position += base_position;
    ((S_800220A8_1 *)motion)->unk_08 = position;
    return;
}

withdraw:
{
    register s32 position_or_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 exit_check ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    position_or_flags = ((S_800220A8_1 *)motion)->unk_08;
    exit_check = (s32)0xFFF00000;
    position_or_flags += exit_check;
    exit_check = (s32)0xFE000000;
    exit_check = exit_check < position_or_flags;
    ((S_800220A8_1 *)motion)->unk_08 = position_or_flags;
    if (exit_check != 0) {
        return;
    }
    (*(u16 *)((u8 *)motion_state + -2)) |= 0x8000;
    position_or_flags = D_800814A0;
    position_or_flags |= 0x8000;
    D_800814A0 = position_or_flags;
    return;
}
}
