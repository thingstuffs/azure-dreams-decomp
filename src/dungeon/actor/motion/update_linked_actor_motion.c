#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"

extern void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);

/* Follows the linked position until the countdown expires, then resets and marks completion. */
s32 update_linked_actor_motion(void *state, ObjectPosition *transform, SpriteFrameState *config, void *object) {
    s16 ticks_left;
    void *linked_transform;

    if (config->flags & 0x8000) {
        *(s16 *)((u8 *)state + 0x96) = 0;
    }
    if (*(s16 *)((u8 *)state + 0x96) != 0) {
        linked_transform = *(void **)((u8 *)*(void **)((u8 *)object + 0x60) - 0x18);
        transform->velocity_x = *(s32 *)((u8 *)linked_transform + 0xC);
        transform->velocity_y = *(s32 *)((u8 *)linked_transform + 0x10);
    }
    ticks_left = *(u16 *)((u8 *)state + 0x96) - 1;
    *(s16 *)((u8 *)state + 0x96) = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        return 0;
    }
    transform->velocity_z = 0;
    transform->velocity_y = 0;
    transform->velocity_x = 0;
    set_record_integer_tile_center(transform, config->tile_x, config->tile_y);
    *(u16 *)((u8 *)state + 0x98) &= 0xFFF7;
    *(s32 *)((u8 *)object + 0x1C) |= 0x40000000;
    g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
    return 1;
}
