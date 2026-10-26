#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern void unlink_node(void *);
extern void retire_tracked_effect_by_id(void *);
extern void spend_actor_mp(void *, s32);

#include "dungeon/monster/stealth.h"

/* Dims the effect and clears its object and owner state when flagged. */
void dim_and_clear_flagged_effect(ActorRecord *effect, ObjectPosition *unused, SpriteFrameState *primitive, ActorRecord *owner) {
    u8 intensity;
    void *effect_object;

    if (effect->action_phase == 0) {
        intensity = *(u8 *)((u8 *)primitive + 0xC) - 0x10;
        *(u8 *)((u8 *)primitive + 0xE) = intensity;
        *(u8 *)((u8 *)primitive + 0xD) = intensity;
        *(u8 *)((u8 *)primitive + 0xC) = intensity;
        if (primitive->flags & 0xE000) {
            effect_object = (u8 *)effect - 0x20;
            unlink_node(effect_object);
            retire_tracked_effect_by_id(effect_object);
            spend_actor_mp(owner, 0x800);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            primitive->color.word = 0;
            owner->pending_turn_updates = 0;
            owner->action_flags &= 0x7FFF;
            *(void **)((u8 *)effect + 0x8C) = stealth_behavior_entry;
        }
    }
}
