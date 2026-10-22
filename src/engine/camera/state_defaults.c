#include "engine/util/state_defaults.h"

#include "common.h"
s32 camera_default_rotation_xy = 0xFD80;
s32 camera_default_rotation_tail = 0x0;
s32 camera_default_origin_xy = 0x0;
s32 camera_default_origin_tail = 0x400;
#include "engine/util/state_defaults.h"
#include "engine/camera.h"

/* Clears camera transition fields, restores the default origin and rotation, and binds the view reference. */
void reset_camera_transition_fields(void)
{
    GameView *state = &g_game_work.view;

    bzero(&state->view_rotation_offset, 8);
    state->view_offset.words[0] = camera_default_origin_xy;
    state->view_offset.words[1] = camera_default_origin_tail;
    state->camera_rotation.words[0] = camera_default_rotation_xy;
    state->camera_rotation.words[1] = camera_default_rotation_tail;
    bzero(&state->camera_position, 8);
    state->slot[2].callback = 0;
    state->slot[3].callback = 0;
    state->slot[0].callback = 0;
    state->slot[1].callback = 0;
    bind_view_triplet_source(((u8 *)(&view_reference_entity)));
}
