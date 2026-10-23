#include "common.h"
#include "shared/game_work.h"
#include "shared/vector.h"
#include "engine/resource.h"
#include "sdk/libgte.h"

extern void advance_timed_entity_motion(GteMatrix *m);

/* Build and install the combined rotation and translation from global transform state. */
void compose_and_install_camera_transform(void)
{
    GameView *transform = (GameView *)(&g_game_work.view);
    GteTranslationVector rotated_pos;
    GteMatrix base_mat;
    GteMatrix combined_mat;
    GteMatrix offset_mat;
    GteMatrix *offset_mat_ptr;
    GteShortVector neg_offset;
    s32 gte_flags;
    offset_mat.t[2] = 0;
    offset_mat.t[1] = 0;
    offset_mat.t[0] = 0;
    base_mat.t[2] = 0;
    offset_mat_ptr = &offset_mat;
    base_mat.t[1] = 0;
    base_mat.t[0] = 0;
    RotMatrix((GteShortVector *)&transform->camera_rotation.parts.camera_rotation_x, &offset_mat);
    SetRotMatrix(offset_mat_ptr);
    SetTransMatrix(&offset_mat);
    neg_offset.vx = -transform->camera_position.parts.camera_position_x;
    neg_offset.vy = -transform->camera_position.parts.camera_position_y;
    neg_offset.vz = -transform->camera_position.parts.camera_position_z;
    RotTrans(&neg_offset, &rotated_pos, &gte_flags);
    TransMatrix(&offset_mat, &rotated_pos);
    RotMatrix((GteShortVector *)&transform->view_rotation_offset.parts.view_rotation_offset_x, &base_mat);
    SetRotMatrix(&base_mat);
    SetTransMatrix(&base_mat);
    RotTrans((GteShortVector *)&transform->view_offset.parts.view_offset_x, &rotated_pos, &gte_flags);
    TransMatrix(&base_mat, &rotated_pos);
    advance_timed_entity_motion(&base_mat);
    CompMatrix(&base_mat, &offset_mat, &combined_mat);
    SetTransMatrix(&combined_mat);
    SetRotMatrix(&combined_mat);
}
