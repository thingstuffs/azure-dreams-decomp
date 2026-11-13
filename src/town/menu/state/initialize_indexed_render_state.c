#include "shared/game_work.h"

#include "town/menu/state.h"
#include "town/menu/target_adjustment.h"
#include "engine/object.h"
#include "sdk/libgte.h"
#include "engine/node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"


extern s16 D_800D0A10[];
extern s32 D_800D0A1C[];
extern u16 D_800D0A34[];
extern u8 D_800F148C[];
/* Initializes object and render state from indexed parameter tables. */
void initialize_indexed_render_state(void *object, ObjectPosition *unused, SpriteFrameState *render_state)
{
    s16 *angle_entry;
    s32 *property_entry;
    s32 *property_table;
    u16 *state_entry;
    u16 *state_table;
    u8 *angle_table;
    u16 initial_state;
    s32 variant_offset;
    s32 halfword_offset;
    variant_offset = *((s16 *) (((s8 *) object) + 0x20));
    render_state->unk_00 = 0;
    render_state->unk_04 = 0;
    render_state->frame_ticks = 0;
    render_state->source = D_800F148C;
    register_node(NODE_HEADER(object), runtime_render_linked_textured_sprites);
    angle_table = (u8 *) D_800D0A10;
    render_state->tpage_abr = 0x20;
    render_state->flags |= 0x1C;
    halfword_offset = variant_offset * 2;
    angle_entry = (s16 *) (angle_table + halfword_offset);
    *((s32 *) (((s8 *) object) + 0x24)) = rsin(*angle_entry);
    variant_offset *= 4;
    *((s32 *) (((s8 *) object) + 0x28)) = 0;
    *((s32 *) (((s8 *) object) + 0x2C)) = rcos(*angle_entry);
    property_table = D_800D0A1C;
    property_entry = (s32 *) (((u8 *) property_table) + variant_offset);
    *((s32 *) (((s8 *) object) + 0x3C)) = *property_entry;
    state_table = D_800D0A34;
    state_entry = (u16 *) (((u8 *) state_table) + halfword_offset);
    initial_state = *state_entry;
    *((u8 **) (((s8 *) object) + 0)) = decrement_sprite_angle_y;
    *((u16 *) (((s8 *) object) + 0x22)) = initial_state;
}
