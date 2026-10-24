#include "common.h"

extern void update_movement_destination_selection_recovery_animation_entity(void);

/* jump_table; owner: dungeon/func_80EA6C28. */
const void *const D_801588F0[6] __attribute__((aligned(4))) = {
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x90),
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x130),
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x1C0),
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x24C),
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x2BC),
    ((u8 *)update_movement_destination_selection_recovery_animation_entity + 0x39C)
};
