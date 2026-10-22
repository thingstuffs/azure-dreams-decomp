
struct ObjectPosition;
struct SpriteFrameState;
#include "common.h"

extern void advance_item_visual_action(void *controller, struct ObjectPosition *motion,struct SpriteFrameState *actor, void *object);

/* Exact jump_table span; dispatch consumer dungeon/func_80DBBFC8. */
const u32 D_80170838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_item_visual_action + 0x130),
    (u32)((u8 *)advance_item_visual_action + 0x128),
    (u32)((u8 *)advance_item_visual_action + 0x120),
    (u32)((u8 *)advance_item_visual_action + 0x138),
    (u32)((u8 *)advance_item_visual_action + 0xE0),
    (u32)((u8 *)advance_item_visual_action + 0xD8),
    (u32)((u8 *)advance_item_visual_action + 0xD0)
};
