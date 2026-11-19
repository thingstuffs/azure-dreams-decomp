#include "common.h"
#include "slus.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/map/object.h"

/* Initializes object data, transform, color, and rendering defaults. */
void init_player_spun_object(TownObjectRecord *object, ObjectPosition *render_data, SpriteFrameState *sprite) {
    LitMeshSprite *mesh = (LitMeshSprite *)sprite;
    u8 blue;

    NODE_HEADER(object)->update_callback = update_player_spun_object;
    register_node(NODE_HEADER(object), draw_linked_lit_meshes);

    object->unk_66 = 0;
    mesh->scale[0] = 0x1000;
    mesh->scale[1] = 0x1000;
    mesh->scale[2] = 0x1000;
    mesh->clut = 0;
    mesh->flags = 0;
    mesh->tpage_abr = 0;
    mesh->rotation[0] = 0;
    mesh->rotation[1] = 0;
    mesh->rotation[2] = 0;
    mesh->frame_entry = 0;
    mesh->frame_index = 0;
    mesh->frame_ticks = 0;
    mesh->color.c.r = g_game_work.view.tint.parts.tint_r;
    mesh->color.c.g = g_game_work.view.tint.parts.tint_g;
    blue = g_game_work.view.tint.parts.tint_b;
    mesh->mesh_index = 0x1F;
    mesh->color.c.b = blue;
    render_data->z.v = 0xFF600000;
}
