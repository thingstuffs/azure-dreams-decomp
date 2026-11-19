#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "town/menu/state.h"
#include "shared/entity.h"
#include "town/map/object/clear_object_link_and_mark_complete_g01169.h"

extern M2C_UNK D_800D0A48;

/* Initialize object state and copy its position with an offset. */
void initialize_lit_mesh_object_with_phase(DoorDisplayBody *object, ObjectPosition *position, LitMeshSprite *state) {
    s32 *value_table;
    state->frame_entry = 0;
    state->frame_index = 0;
    state->frame_ticks = 0;
    register_node(NODE_HEADER(object), &lit_mesh_renderer_address);
    position->x.v = object->origin->x.v;
    position->y.v = object->origin->y.v;
    position->z.v = object->origin->z.v;
    object->callback = &copy_negated_menu_phase;
    value_table = &D_800D0A48;
    state->mesh_index = (s32) value_table[object->part_index];
    position->x.unsigned_parts.integer = (u16) (position->x.unsigned_parts.integer + 0x28);
    position->y.unsigned_parts.integer = (u16) (position->y.unsigned_parts.integer - 8);
    state->rotation[2] = 0;
}
