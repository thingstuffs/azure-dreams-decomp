#include "common.h"

extern void update_variant_part_brightness(void);

/* entry; owner: dungeon/func_81071000. */
const u32 tyrant_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)update_variant_part_brightness
};
