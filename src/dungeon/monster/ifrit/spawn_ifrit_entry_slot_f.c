#include "common.h"

extern void queue_projected_point_primitives_2(void);

/* entry; owner: dungeon/func_80A23000. */
const u32 ifrit_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)queue_projected_point_primitives_2
};
