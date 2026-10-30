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
#include "engine/town.h"


#include "dungeon/player/item.h"
#include "dungeon/system.h"
#include "dungeon/player/state.h"
#include "dungeon/item/message.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s32 generate_random_value(void);

extern u8 D_800893E0[];
extern u8 D_800E18A4[];


typedef struct S_800C4490_0_pre {
    ObjectPosition *unk_00;
    u8 pad_04[0x14];
} S_800C4490_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_heal_small_random_amount, addressed as arg0[-1] */


/* Applies a capped random stat gain to the target and displays its effect message. */
s32 use_item_to_heal_small_random_amount(void *target, DungeonItemEntry *source, s16 effect_mode) {
    s16 stat_gap;
    s16 feed_result;
    s32 stat_gain;
    void *effect_text;
    void *message_context;

    if (target == ((s32)dungeon_actor_ring_anchor)) {
        ((PlayerRecord *)target)->pending_item_action = source;
        begin_deferred_item_action(target, &view_reference_entity.x.v, &reference_tile_object.frame_entry, target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_item_status_message(target, source, effect_mode);
        feed_result = feed_actor_restore_mp(target,
                          (*(u16 *)(((u8 *)entity_action_selectors) +
                                    (*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3)) * 2) >> 6) & 3,
                          source);
        if (feed_result == 0) {
            place_actor_item(target, source);
            return 1;
        }
    }

    stat_gain = (generate_random_value() & 3) + 7;
    if (stat_gain >= 0x100) {
        stat_gain = 0xFF;
    }

    stat_gap = ((EntityRec *)target)->unk_29 - ((EntityRec *)target)->unk_28;
    if (stat_gap < stat_gain) {
        stat_gain = stat_gap;
    }
    ((EntityRec *)target)->unk_64 = stat_gain;

    if (((EntityRec *)target)->flags14 & ACTOR_PARTY_MEMBER) {
        effect_text = get_unused_text_buffer();
        {
            void *message_target;
            void *context_arg;

            message_target = target;
            context_arg = effect_text;
            message_context = context_arg;
            effect_text = append_entity_display_text(message_target, context_arg);
        }
        clear_byte_and_advance(expand_text_control_codes(
            D_800893E0,
            format_unsigned_double_byte_decimal(((EntityRec *)target)->unk_64,
                          expand_text_control_codes(D_800E18A4, effect_text))));
        display_text_with_fullwidth_adjustment(message_context);
    }

    create_timed_paired_particle_emitter(((S_800C4490_0_pre *)target)[-1].unk_00, 0x20E020, target);
    clear_slot_and_update_linked_state(source);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
