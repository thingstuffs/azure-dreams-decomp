#include "common.h"

extern void update_creature_animation_dispatch_dungeon_action(void);

/* jump_table; owner: dungeon/func_81017858. */
const u32 garuda_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x494),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x494),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x494),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x4C0),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x440),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x440),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x440),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x408),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x3AC),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x4C0),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x4C0),
    (u32)((u8 *)update_creature_animation_dispatch_dungeon_action + 0x484)
};
