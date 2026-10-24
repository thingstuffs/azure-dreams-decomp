#include "common.h"

extern void build_projected_tile_packets(void);

/* entry; owner: dungeon/func_80A1D000. */
const void *const ifrit_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    build_projected_tile_packets
};
