#include "common.h"

extern void create_actor_grid_object(void);

/* Exact entry span; owner-unresolved. */
const void *const mandara_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_actor_grid_object
};
