#include "common.h"
#include "dungeon/monster/mandara.h"

/* Exact entry span; owner-unresolved. */
const void *const mandara_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_mandara_actor
};
