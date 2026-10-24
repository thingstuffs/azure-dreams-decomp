#include "common.h"

extern void run_selected_actor_action(void);

/* jump_table; owner: dungeon/func_8101F034. */
const void *const D_80158858[7] __attribute__((aligned(4))) = {
    ((u8 *)run_selected_actor_action + 0x11C),
    ((u8 *)run_selected_actor_action + 0x114),
    ((u8 *)run_selected_actor_action + 0x10C),
    ((u8 *)run_selected_actor_action + 0x124),
    ((u8 *)run_selected_actor_action + 0xCC),
    ((u8 *)run_selected_actor_action + 0xC4),
    ((u8 *)run_selected_actor_action + 0xBC)
};
