#include "dungeon/item.h"
#include "shared/actor_property_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"

#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "engine/entity.h"

extern u8 D_800E0EE1[38];


typedef struct S_800BDA44_0_pre {
    ObjectPosition *unk_00;
    u8 pad_04[0x14];
} S_800BDA44_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_restore_attack, addressed as arg0[-1] */


/* Apply the item effect to the target and consume the item on completion. */
s32 use_item_to_restore_attack(ActorRecord *target, DungeonItemEntry *item, s16 use_type) {
    if (target == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_deferred_item_action(target, &view_reference_entity.x.v, &reference_tile_object.frame_entry, target);
        return 0;
    }
    if ((u32) target <= 0x9FFFFFFFU) {
        display_item_status_message(target, item, use_type);
        if (feed_actor_restore_mp(target, (entity_action_selectors[(*((u8 *)&((EntityRec *)target)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(((S_800BDA44_0_pre *)target)[-1].unk_00, 0x2020C0, target);
    target->current_attack = (u8) target->base_attack;
    apply_entity_effects(target);
    if (target->flags14 & ACTOR_PARTY_MEMBER) {
        adjust_source_value_and_finalize(target, D_800E0EE1);
    }
    clear_slot_and_update_linked_state(item);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
