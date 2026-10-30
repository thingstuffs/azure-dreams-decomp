#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"

extern void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);

/* Follows the linked position until the countdown expires, then resets and marks completion. */
s32 update_linked_actor_motion(void *state, void *transform, void *config, void *object) {
    s16 ticks_left;
    void *linked_transform;

    if (((SpriteFrameState *)config)->flags & 0x8000) {
        *(s16 *)((u8 *)state + 0x96) = 0;
    }
    if (*(s16 *)((u8 *)state + 0x96) != 0) {
        linked_transform = *(void **)((u8 *)*(void **)((u8 *)object + 0x60) - 0x18);
        *(s32 *)((u8 *)transform + 0xC) = *(s32 *)((u8 *)linked_transform + 0xC);
        *(s32 *)((u8 *)transform + 0x10) = *(s32 *)((u8 *)linked_transform + 0x10);
    }
    ticks_left = *(u16 *)((u8 *)state + 0x96) - 1;
    *(s16 *)((u8 *)state + 0x96) = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        return 0;
    }
    *(s32 *)((u8 *)transform + 0x14) = 0;
    *(s32 *)((u8 *)transform + 0x10) = 0;
    *(s32 *)((u8 *)transform + 0xC) = 0;
    set_record_integer_tile_center(transform, *((u8 *)config + 0x24), *((u8 *)config + 0x25));
    *(u16 *)((u8 *)state + 0x98) &= 0xFFF7;
    *(s32 *)((u8 *)object + 0x1C) |= 0x40000000;
    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    return 1;
}
