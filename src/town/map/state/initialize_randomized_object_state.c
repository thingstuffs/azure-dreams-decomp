#include "common.h"
#include "m2c_compat.h"
#include "engine/window.h"
#include "engine/node.h"
#include "town/map/state.h"

struct S_800A8BBC_0; void write_square_position_offsets(s16, s16, s16, s16, struct S_800A8BBC_0 *);
extern M2C_UNK map_random_state_draw_address[3];
extern M2C_UNK D_800A9624[3];
extern M2C_UNK D_800A970C[3];

/* Initialize object tables, settings, and randomized state. */
void initialize_randomized_object_state(void *object, void *random_state, void *settings) {
    *(s32 **)((s8 *)object - 0x10) = D_800A9624;
    *(s32 **)((s8 *)object + 0x50) = D_800A970C;
    *(s16 *)((s8 *)settings + 0x1C) = 0x37;
    *(s16 *)((s8 *)settings + 0x1E) = 0x37;
    *(u16 *)((s8 *)settings + 0x20) = 0xFF00;
    *(s16 *)((s8 *)random_state + 0x0E) = scale_random_to_unsigned_halfword_limit(0xFFFF);
    *(s16 *)((s8 *)random_state + 0x12) = scale_random_to_unsigned_halfword_limit(0xFFFF);
    *(s16 *)((s8 *)random_state + 0x16) = scale_random_to_unsigned_halfword_limit(0xFFFF);
    register_node_if_unregistered(object, map_random_state_draw_address);
    write_square_position_offsets(0x10, 0x11, 0x12, 0x13, random_state);
}
