#include "common.h"

extern void start_selected_actor_action(void);

/* jump_table; owner: dungeon/func_8100D034. */
const void *const garuda_slot_f_action_cases[7] __attribute__((aligned(4))) = {
    ((u8 *)start_selected_actor_action + 0x11C),
    ((u8 *)start_selected_actor_action + 0x114),
    ((u8 *)start_selected_actor_action + 0x10C),
    ((u8 *)start_selected_actor_action + 0x124),
    ((u8 *)start_selected_actor_action + 0xCC),
    ((u8 *)start_selected_actor_action + 0xC4),
    ((u8 *)start_selected_actor_action + 0xBC)
};
