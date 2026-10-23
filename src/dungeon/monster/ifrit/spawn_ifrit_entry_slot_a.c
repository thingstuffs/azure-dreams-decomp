#include "common.h"

extern void queue_linked_point_packets(void);

/* entry; owner: dungeon/func_80A41000. */
const u32 ifrit_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)queue_linked_point_packets
};
