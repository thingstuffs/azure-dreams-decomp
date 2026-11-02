#include "common.h"
#include "m2c_compat.h"
#include "engine/window.h"
#include "engine/node.h"
#include "town/map/state.h"

struct TownPositionXY; void write_square_position_offsets(s16, s16, s16, s16, struct TownPositionXY *);
extern M2C_UNK map_random_state_draw_address[3];
extern M2C_UNK D_800A9624[3];
extern M2C_UNK D_800A970C[3];

/* Initialize object tables, settings, and randomized state. */
void initialize_randomized_object_state(TownObjectRecord *object, ObjectPosition *random_state, SpriteFrameState *settings) {
    ((ObjectNodeHeader *)object - 1)->update_callback = D_800A9624;
    object->unk_50.as_pm = D_800A970C;
    settings->scale_x = 0x37;
    settings->scale_y = 0x37;
    settings->offset_x = 0xFF00;
    ((Fixed1616 *)&random_state->velocity_x)->w.i = scale_random_to_unsigned_halfword_limit(0xFFFF);
    ((Fixed1616 *)&random_state->velocity_y)->w.i = scale_random_to_unsigned_halfword_limit(0xFFFF);
    ((Fixed1616 *)&random_state->velocity_z)->w.i = scale_random_to_unsigned_halfword_limit(0xFFFF);
    register_node_if_unregistered(object, map_random_state_draw_address);
    write_square_position_offsets(0x10, 0x11, 0x12, 0x13, (struct TownPositionXY *)random_state);
}
