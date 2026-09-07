#include "common.h"
#include "m2c_compat.h"

extern void *D_80088880[];
extern u16 D_80083168[];

/* Converts directional input to an angle, optionally stepping from the current angle, and updates flags. */
s32 func_8009074C(s16 direction_offset, u16 *flags, u16 *angle) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    s32 current_angle;
    register s16 result_angle ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 direction_mask;
    register s32 direction_or_angle ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 direction_result;
    s32 angle_distance;
    register s32 shifted_angle ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u16 current_bits;
    u16 angle_bits;
    u16 updated_flags;
    u16 normalized;
    u32 input_state;
    u32 input_direction;

    input_state = D_80083168[0];
    result_angle = -1;
    direction_mask = input_state & 0xF000;
    if (input_state & 0x10) {
        goto block_2;
    }
    *flags &= 0xFFF;
block_2:
    input_direction = input_state >> 0xC;
    if ((u32) (input_direction - 1) >= 0xCU) {
        goto block_17;
    }
    (void)jt_keep; goto *D_80088880[(u32)((input_direction) - 1)];
jt_c2:
    if (*flags & direction_mask) {
        goto block_19;
    }
    {
        register s32 offset_angle ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 relative_angle;
        offset_angle = ((s32) (direction_offset << 0x10) >> 7);
        relative_angle = 0 - offset_angle;
        result_angle = relative_angle;
        goto block_19;
    }
jt_c6:
    {
        register s32 relative_direction ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 relative_angle;
        register s32 direction_or_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        direction_or_flags = (s16)direction_offset;
        relative_direction = 1 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c1;
    }
jt_c4:
    if (*flags & direction_mask) {
        goto block_19;
    }
    {
        direction_or_angle = (s16)direction_offset;
        direction_result = 2;
        goto entry_v0_minus_v1;
    }
jt_c12:
    {
        register s32 relative_direction ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 relative_angle;
        register s32 direction_or_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        direction_or_flags = (s16)direction_offset;
        relative_direction = 3 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c3;
    }
jt_c8:
    if (*flags & direction_mask) {
        goto block_19;
    }
    {
        direction_or_angle = (s16)direction_offset;
        direction_result = 4;
        goto entry_v0_minus_v1;
    }
jt_c9:
    {
        register s32 relative_direction ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register s32 direction_or_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 relative_angle;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 5 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c5;
    }
jt_c1:
    if (*flags & direction_mask) {
        goto block_19;
    }
    direction_or_angle = (s16)direction_offset;
    direction_result = 6;
entry_v0_minus_v1:
    direction_result = direction_result - direction_or_angle;
    result_angle = direction_result << 9;
    goto block_19;
jt_c3:
    {
        register s32 direction_or_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 relative_direction ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 relative_angle;
        direction_or_flags = (s16)direction_offset;
        relative_direction = 7 - direction_or_flags;
        relative_angle = relative_direction << 9;
        direction_or_flags = (*flags & 0xFFF) | direction_mask;
        result_angle = relative_angle;
        updated_flags = direction_or_flags;
        goto block_18_c7;
    }
jt_c5:
jt_c7:
jt_c10:
jt_c11:
block_17:
    updated_flags = *flags & 0xFFF;
block_18_c1:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c3:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c5:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
block_18_c7:
block_18:
    *flags = updated_flags;
block_19:
    *flags &= 0xFBFF;
    if (angle == NULL) {
        goto block_34;
    }
    if (result_angle == -1) {
        goto block_34;
    }
    angle_bits = *angle;
    normalized = angle_bits & 0x800;
    if (!normalized) {
        normalized = angle_bits & 0x7FF;
    } else {
        normalized = angle_bits | 0xF800;
    }
block_23:
    *angle = normalized;
    normalized = result_angle & 0x800;
    if (!normalized) {
        normalized = (u16) result_angle & 0x7FF;
    } else {
        normalized = (u16) result_angle | 0xF800;
    }
block_25:
    result_angle = normalized;
    current_angle = (s16) *angle;
    current_bits = *angle;
    angle_distance = current_angle - result_angle;
    if (angle_distance >= 0) {
        goto block_27;
    }
    angle_distance = 0 - angle_distance;
block_27:
    ASM_KEEP(result_angle);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (angle_distance < 0x801) {
        goto block_28;
    }
    {
        u16 wrap_hi;
        register u16 wrap_lo ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        wrap_hi = current_bits & 0xF000;
        ASM_KEEP(wrap_hi);   /* MATCH pin: keeps a statement from moving across a call/branch */
        wrap_lo = result_angle & 0xFFF;
        ASM_KEEP(wrap_lo);   /* MATCH pin: load-bearing for the whole function shape */
        result_angle = wrap_hi | wrap_lo;
    }
    shifted_angle = result_angle << 0x10;
    goto block_29;
block_28:
    shifted_angle = result_angle << 0x10;
block_29:
    direction_or_angle = shifted_angle >> 0x10;
    direction_result = current_angle < direction_or_angle;
    if (!direction_result) {
        goto block_31;
    }
    updated_flags = *flags;
    result_angle = current_bits + 0x200;
    goto block_33;
block_31:
    direction_result = direction_or_angle < current_angle;
    if (!direction_result) {
        goto block_34;
    }
    updated_flags = *flags;
    result_angle = current_bits - 0x200;
block_33:
    updated_flags |= 0x400;
    *flags = updated_flags;
block_34:
    return result_angle & 0xFFF;
}
