#include "common.h"

extern void * create_entity_and_initialize_placement(s16 entity_id, s32 tile_x, s16 tile_y, u16 initial_height);

/* entry; owner-unresolved. */
const void *const beldo_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_entity_and_initialize_placement
};
