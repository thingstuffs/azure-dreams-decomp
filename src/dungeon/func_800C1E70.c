#include "common.h"
#include "shared/game_work.h"

extern s16 sample_terrain_surface_height(u16, u16, s16);
extern u8 D_800DF63C[];
extern u8 D_800E3D20[];
extern u16 D_800E58F8[];

/* Update target tracking and smoothly approach its position and transition value. */
void update_target_tracking_and_transition(void *tracker) {
    GameView *state = &g_game_work.view;
    s16 frames_left;
    s16 next_frames;
    s16 target_height;
    u16 *target_pos;
    void *tracked_object;

    tracked_object = *(void **)((char *)tracker + 0x34);
    if ((tracked_object != 0) && (*(u16 *)((char *)tracked_object + 0x1E) & 0x8000)) {
        u16 *saved_pos = D_800E58F8;
        *(void **)((char *)tracker + 0x34) = 0;
        saved_pos[1] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
        saved_pos[3] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
        saved_pos[5] = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
        *(void **)((char *)tracker + 0xC) = saved_pos;
    }
    frames_left = *(s16 *)((char *)tracker + 0x24);
    if (frames_left > 0) {
        state->view_offset.parts.view_offset_z = (u16)state->view_offset.parts.view_offset_z +
            (*(s16 *)((char *)tracker + 0x26) - state->view_offset.parts.view_offset_z) / frames_left;
    } else {
        D_800E3D20[0] = 0;
    }
    next_frames = *(s16 *)((char *)tracker + 0x24) - 1;
    *(s16 *)((char *)tracker + 0x24) = next_frames;
    if (next_frames < -0x80) {
        *(s16 *)((char *)tracker + 0x24) = -0x80;
    }
    *(u16 *)((char *)tracker + 4) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 2);
    *(u16 *)((char *)tracker + 6) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 6);
    target_pos = *(u16 **)((char *)tracker + 0xC);
    target_height = sample_terrain_surface_height(target_pos[1], target_pos[3], (s16)(target_pos[5] - 0x20));
    *(s16 *)((char *)tracker + 8) = target_height;
    if (target_height >= 0x201) {
        *(s16 *)((char *)tracker + 8) = *(u16 *)((char *)*(void **)((char *)tracker + 0xC) + 0xA);
    }
    state->camera_position.parts.camera_position_x = (u16)state->camera_position.parts.camera_position_x + ((s32)((s16)*(u16 *)((char *)tracker + 4) - state->camera_position.parts.camera_position_x) >> 2);
    state->camera_position.parts.camera_position_y = (u16)state->camera_position.parts.camera_position_y + ((s32)((s16)*(u16 *)((char *)tracker + 6) - state->camera_position.parts.camera_position_y) >> 2);
    if (D_800DF63C[0] != 0) {
        state->camera_position.parts.camera_position_z = (u16)state->camera_position.parts.camera_position_z + ((s32)(*(s16 *)((char *)tracker + 8) - state->camera_position.parts.camera_position_z) >> 2);
    }
    D_800DF63C[0] = (s8)(state->camera_position.parts.camera_position_z != *(s16 *)((char *)tracker + 8));
    state->view_offset.parts.view_offset_x = (s32)(((u16)state->view_offset.parts.view_offset_x) << 0x10) >> 0x12;
    state->view_offset.parts.view_offset_y = (s32)(((u16)state->view_offset.parts.view_offset_y) << 0x10) >> 0x12;
}
