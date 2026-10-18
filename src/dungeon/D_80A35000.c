#include "common.h"

extern void queue_linked_object_draw_packets(void);

/* entry; owner: dungeon/func_80A35000. */
const u32 D_80158800[1] __attribute__((aligned(4))) = {
    (u32)queue_linked_object_draw_packets
};
