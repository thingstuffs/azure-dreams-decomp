#include "common.h"
#include "dungeon/monster/weadog.h"

/* entry; owner-unresolved. */
const void *const weadog_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_weadog_actor
};
