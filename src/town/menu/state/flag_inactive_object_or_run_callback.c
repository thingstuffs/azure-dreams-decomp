#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "town/menu/state.h"

/* Flags inactive objects; otherwise copies shared bytes and invokes the callback. */
void flag_inactive_object_or_run_callback(DoorDisplayBody *object, ObjectPosition *position, LitMeshSprite *mesh) {
    u8 *active_flag;

    active_flag = object->active_flag;
    if (active_flag != 0) {
        if (*active_flag == 0) {
            NODE_HEADER(object)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }

    mesh->color.c.r = g_game_work.view.tint.parts.tint_r;
    mesh->color.c.g = g_game_work.view.tint.parts.tint_g;
    mesh->color.c.b = g_game_work.view.tint.parts.tint_b;
    object->callback(object, position, mesh);
}
