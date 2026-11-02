#include "shared/entity.h"

struct ObjectPosition;
struct SpriteFrameState;
#include "common.h"
#include "dungeon/monster/blume.h"

/* Exact jump_table span; dispatch consumer dungeon/func_80DBBFC8. */
const void *const blume_slot_g_item_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_item_visual_action + 0x130),
    ((u8 *)advance_item_visual_action + 0x128),
    ((u8 *)advance_item_visual_action + 0x120),
    ((u8 *)advance_item_visual_action + 0x138),
    ((u8 *)advance_item_visual_action + 0xE0),
    ((u8 *)advance_item_visual_action + 0xD8),
    ((u8 *)advance_item_visual_action + 0xD0)
};
