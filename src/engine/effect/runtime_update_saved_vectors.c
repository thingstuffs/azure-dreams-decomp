#include "common.h"
#include "shared/game_work.h"
#include "engine/effect.h"

/* Update the four saved vectors and return 1 if any coordinate changed, otherwise return 0. */
s32 runtime_update_saved_vectors(void)
{
    GameView *source;
    struct S_80083178State *saved;

    source = &g_game_work.view;
    saved = &saved_view_vectors;

    if (source->view_offset.parts.view_offset_x != saved->v[0].x
        || source->view_offset.parts.view_offset_y != saved->v[0].y
        || source->view_offset.parts.view_offset_z != saved->v[0].z
        || source->view_rotation_offset.parts.view_rotation_offset_x != saved->v[1].x
        || source->view_rotation_offset.parts.view_rotation_offset_y != saved->v[1].y
        || source->view_rotation_offset.parts.view_rotation_offset_z != saved->v[1].z
        || source->camera_position.parts.camera_position_x != saved->v[2].x
        || source->camera_position.parts.camera_position_y != saved->v[2].y
        || source->camera_position.parts.camera_position_z != saved->v[2].z
        || source->camera_rotation.parts.camera_rotation_x != saved->v[3].x
        || source->camera_rotation.parts.camera_rotation_y != saved->v[3].y
        || source->camera_rotation.parts.viewAngle != saved->v[3].z) {
        saved_view_vectors.v[0] = *(struct S_80083178Vector *)&source->view_offset.parts.view_offset_x;
        saved_view_vectors.v[1] = *(struct S_80083178Vector *)&source->view_rotation_offset.parts.view_rotation_offset_x;
        saved_view_vectors.v[2] = *(struct S_80083178Vector *)&source->camera_position.parts.camera_position_x;
        saved_view_vectors.v[3] = *(struct S_80083178Vector *)&source->camera_rotation.parts.camera_rotation_x;
        return 1;
    }
    return 0;
}
