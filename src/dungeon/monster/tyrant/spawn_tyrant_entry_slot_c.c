#include "common.h"

extern void * update_variant_part_brightness(s16 spawn_flags, s16 x, s16 y, s16 config_value);

/* entry; owner: dungeon/func_81071000. */
const void *const tyrant_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    update_variant_part_brightness
};
