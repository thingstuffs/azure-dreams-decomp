#include "common.h"

extern void queue_linked_render_packets(void);

/* entry; owner: dungeon/func_80A2F000. */
const void *const ifrit_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    queue_linked_render_packets
};
