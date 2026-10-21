#include "engine/util/state_defaults.h"

#include "common.h"
s32 camera_default_rotation_xy = 0xFD80;
s32 camera_default_rotation_tail = 0x0;
s32 camera_default_origin_xy = 0x0;
s32 camera_default_origin_tail = 0x400;
#include "engine/util/state_defaults.h"
#include "engine/camera.h"

void reset_camera_transition_fields(void)
{
    u8 *state = (u8 *)(&g_game_work.view);

    bzero(state + 0x9C, 8);
    *(s32 *)(state + 0x94) = camera_default_origin_xy;
    *(s32 *)(state + 0x98) = camera_default_origin_tail;
    *(s32 *)(state + 0xAC) = camera_default_rotation_xy;
    *(s32 *)(state + 0xB0) = camera_default_rotation_tail;
    bzero(state + 0xA4, 8);
    *(s32 *)(state + 0x13C) = 0;
    *(s32 *)(state + 0x180) = 0;
    *(s32 *)(state + 0xB4) = 0;
    *(s32 *)(state + 0xF8) = 0;
    bind_view_triplet_source(((u8 *)(&view_reference_entity)));
}
