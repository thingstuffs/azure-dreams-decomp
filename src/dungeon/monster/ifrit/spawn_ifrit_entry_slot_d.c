#include "common.h"

extern void queue_linked_render_packets(void);

/* entry; owner: dungeon/func_80A2F000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)queue_linked_render_packets
};
