#include "common.h"

extern void queue_linked_object_draw_packets(void);

/* entry; owner: dungeon/func_80A35000. */
const void *const ifrit_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    queue_linked_object_draw_packets
};
