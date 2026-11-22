#include "town/scene/object.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "town/map/object.h"
#include "town/map/object/clear_object_link_and_mark_complete_g01169.h"
#include "town/scene.h"

void init_lit_mesh_sprite(TownObjectRecord *state, ObjectPosition *position, LitMeshSprite *mesh) {
    SpriteSixNodeView node;
    node.state = state;
    node.header[-1].update_callback = update_player_spun_object;
    register_node(node.header - 1, lit_mesh_renderer_address);
    state->unk_66 = 0;
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
    mesh->color.c.b = g_game_work.view.tint.parts.tint_b;
    mesh->mesh_index = 6;
    position->z.v = -0xA00000;
}
