#include "common.h"

extern void create_entity_and_initialize_placement(void);

/* entry; owner-unresolved. */
const void *const beldo_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_entity_and_initialize_placement
};
