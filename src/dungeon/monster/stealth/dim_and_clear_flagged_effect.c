#include "common.h"
#include "shared/dungeon_status.h"

extern void unlink_node(void *);
extern void retire_tracked_effect_by_id(void *);
extern void spend_actor_mp(void *, s32);

#include "dungeon/monster/stealth.h"

/* Dims the effect and clears its object and owner state when flagged. */
void dim_and_clear_flagged_effect(void *effect, s32 unused, void *primitive, void *owner)
{
    u8 intensity;
    void *effect_object;

    if (*(u8 *)((u8 *)effect + 0x9B) == 0) {
        intensity = *(u8 *)((u8 *)primitive + 0xC) - 0x10;
        *(u8 *)((u8 *)primitive + 0xE) = intensity;
        *(u8 *)((u8 *)primitive + 0xD) = intensity;
        *(u8 *)((u8 *)primitive + 0xC) = intensity;
        if (*(u16 *)((u8 *)primitive + 0x14) & 0xE000) {
            effect_object = (u8 *)effect - 0x20;
            unlink_node(effect_object);
            retire_tracked_effect_by_id(effect_object);
            spend_actor_mp(owner, 0x800);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            *(u32 *)((u8 *)primitive + 0xC) = 0;
            *(u8 *)((u8 *)owner + 0x6D) = 0;
            *(u16 *)((u8 *)owner + 0x46) &= 0x7FFF;
            *(void **)((u8 *)effect + 0x8C) = stealth_behavior_entry;
        }
    }
}
