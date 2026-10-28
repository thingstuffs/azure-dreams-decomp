#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/camera.h"

/* Set position and rotation targets, adjusting rotation components across the 12-bit wrap. */
void set_camera_targets(void *target_position, void *target_rotation, u16 transition_param)
{
    GameView *state = &g_game_work.view;
    u16 angle_bits;
    s16 target_angle;
    s16 current_angle;
    s32 angle_delta;
    s32 within_half_turn;
    if (target_position != 0) {
        initialize_three_component_interpolation(&state->slot[0].unk_04, target_position, transition_param, &state->camera_position.parts.camera_position_x);
    }
    if (target_rotation != 0) {
        s32 current_angle_wide_m;
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 0));
        if (angle_bits & 0x800) {
            target_angle = angle_bits | 0xF800;
        }
        else {
            target_angle = angle_bits & 0x7FF;
        }
        *((s16 *) (((u8 *) target_rotation) + 0)) = target_angle;
        angle_bits = *((u16 *) (&state->camera_rotation.parts.camera_rotation_x));
        if (angle_bits & 0x800) {
            current_angle = angle_bits | 0xF800;
        }
        else {
            current_angle = angle_bits & 0x7FF;
        }
        state->camera_rotation.parts.camera_rotation_x = current_angle;
        {
            current_angle_wide_m = (u32)current_angle << 16;
            current_angle_wide_m >>= 16;
            angle_delta = (*((s16 *) (((u8 *) target_rotation) + 0))) - current_angle_wide_m;
        }
        if (angle_delta < 0) {
            within_half_turn = (-angle_delta < 0x801);
        } else {
            within_half_turn = (angle_delta < 0x801);
        }
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 0));
        if (!within_half_turn) {
            *((s16 *) (((u8 *) target_rotation) + 0)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
        }
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 2));
        if (angle_bits & 0x800) {
            target_angle = angle_bits | 0xF800;
        }
        else {
            target_angle = angle_bits & 0x7FF;
        }
        *((s16 *) (((u8 *) target_rotation) + 2)) = target_angle;
        angle_bits = *((u16 *) (&state->camera_rotation.parts.camera_rotation_y));
        if (angle_bits & 0x800) {
            current_angle = angle_bits | 0xF800;
        }
        else {
            current_angle = angle_bits & 0x7FF;
        }
        state->camera_rotation.parts.camera_rotation_y = current_angle;
        {
            current_angle_wide_m = (u32)current_angle << 16;
            current_angle_wide_m >>= 16;
            angle_delta = (*((s16 *) (((u8 *) target_rotation) + 2))) - current_angle_wide_m;
        }
        if (angle_delta < 0) {
            within_half_turn = (-angle_delta < 0x801);
        } else {
            within_half_turn = (angle_delta < 0x801);
        }
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 2));
        if (!within_half_turn) {
            *((s16 *) (((u8 *) target_rotation) + 2)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
        }
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 4));
        if (angle_bits & 0x800) {
            target_angle = angle_bits | 0xF800;
        }
        else {
            target_angle = angle_bits & 0x7FF;
        }
        *((s16 *) (((u8 *) target_rotation) + 4)) = target_angle;
        angle_bits = *((u16 *) (&state->camera_rotation.parts.viewAngle));
        if (angle_bits & 0x800) {
            current_angle = angle_bits | 0xF800;
        }
        else {
            current_angle = angle_bits & 0x7FF;
        }
        state->camera_rotation.parts.viewAngle = current_angle;
        {
            current_angle_wide_m = (u32)current_angle << 16;
            current_angle_wide_m >>= 16;
            angle_delta = (*((s16 *) (((u8 *) target_rotation) + 4))) - current_angle_wide_m;
        }
        if (angle_delta < 0) {
            within_half_turn = (-angle_delta < 0x801);
        } else {
            within_half_turn = (angle_delta < 0x801);
        }
        angle_bits = *((u16 *) (((u8 *) target_rotation) + 4));
        if (!within_half_turn) {
            *((s16 *) (((u8 *) target_rotation) + 4)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
        }
        initialize_three_component_interpolation(&state->slot[2].unk_04, target_rotation, transition_param, &state->camera_rotation.parts.camera_rotation_x);
    }
}
