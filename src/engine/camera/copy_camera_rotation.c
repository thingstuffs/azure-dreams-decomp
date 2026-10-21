#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "engine/camera.h"
#include "engine/resource.h"
#include "slus/data.h"

/* g_game_work.view declared on its own: retail forms this TU's base at 0x80083178 itself (not g_game_work + 0x18). */

/* Copies rotation angles from D_80083780 into D_80083178 (g_game_work.view's position vector) and builds matrices. */
void copy_camera_rotation(void)
{
    game_view_state_alias.camera_position.parts.camera_position_x = view_reference_entity.x.w.i;
    game_view_state_alias.camera_position.parts.camera_position_y = view_reference_entity.y.w.i;
    game_view_state_alias.camera_position.parts.camera_position_z = view_reference_entity.z.w.i;
    compose_and_install_camera_transform();
}
