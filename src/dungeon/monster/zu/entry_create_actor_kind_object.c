#include "common.h"

extern void create_actor_kind_object(void);

/* entry; owner: dungeon/func_80FAB000. */
const u32 zu_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)create_actor_kind_object
};
