#include "town/scene/object.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "town/map/object.h"
#include "town/scene.h"

extern u8 lit_mesh_renderer_address[];

void initialize_sprite_six(SpriteSixState *state, ObjectPosition *position, SpriteSixRender *render) {
    SpriteSixNodeView node;
    node.state = state;
    node.header[-1].update_callback = deactivate_object_triggered;
    register_node(node.header - 1, lit_mesh_renderer_address);
    state->angle = 0;
    render->sprite.scale_x = 0x1000;
    render->sprite.scale_y = 0x1000;
    render->sprite.offset_x = 0x1000;
    render->sprite.clut = 0;
    render->sprite.flags = 0;
    render->sprite.tpage_abr = 0;
    render->sprite.angle_x = 0;
    render->sprite.angle_y = 0;
    render->sprite.angle_z = 0;
    render->sprite.unk_00 = 0;
    render->sprite.unk_04 = 0;
    render->sprite.frame_ticks = 0;
    render->sprite.color.c.r = g_game_work.view.tint.parts.tint_r;
    render->sprite.color.c.g = g_game_work.view.tint.parts.tint_g;
    render->sprite.color.c.b = g_game_work.view.tint.parts.tint_b;
    render->record.object_id = 6;
    position->z.v = -0xA00000;
}
