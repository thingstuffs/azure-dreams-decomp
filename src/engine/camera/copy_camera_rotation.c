#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

/* g_game_work.view declared on its own: retail forms this TU's base at 0x80083178 itself (not g_game_work + 0x18). */
extern GameView D_80083178;

extern void compose_and_install_camera_transform(void);

/* Copies rotation angles from D_80083780 into D_80083178 (g_game_work.view's position vector) and builds matrices. */
void copy_camera_rotation(void)
{
    D_80083178.camera_position.parts.camera_position_x = D_80083780.x.w.i;
    D_80083178.camera_position.parts.camera_position_y = D_80083780.y.w.i;
    D_80083178.camera_position.parts.camera_position_z = D_80083780.z.w.i;
    compose_and_install_camera_transform();
}
