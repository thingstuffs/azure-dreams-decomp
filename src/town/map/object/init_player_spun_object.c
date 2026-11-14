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
    u8 blue;

    NODE_HEADER(object)->update_callback = update_player_spun_object;
    register_node(NODE_HEADER(object), draw_linked_lit_meshes);

    object->unk_66 = 0;
    sprite->scale_x = 0x1000;
    sprite->scale_y = 0x1000;
    sprite->offset_x = 0x1000;
    sprite->clut = 0;
    sprite->flags = 0;
    sprite->tpage_abr = 0;
    sprite->angle_x = 0;
    sprite->angle_y = 0;
    sprite->angle_z = 0;
    sprite->unk_00 = 0;
    sprite->unk_04 = 0;
    sprite->frame_ticks = 0;
    sprite->color.c.r = g_game_work.view.tint.parts.tint_r;
    sprite->color.c.g = g_game_work.view.tint.parts.tint_g;
    blue = g_game_work.view.tint.parts.tint_b;
    sprite->source = (void *)0x1F;
    sprite->color.c.b = blue;
    render_data->z.v = 0xFF600000;
}
