#include "common.h"

extern void * create_actor_kind_object(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input);

/* entry; owner: dungeon/func_80FAB000. */
const void *const zu_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    create_actor_kind_object
};
