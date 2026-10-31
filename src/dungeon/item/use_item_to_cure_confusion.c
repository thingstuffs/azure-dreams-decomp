#include "dungeon/item.h"
#include "shared/actor_property_flags.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"


void clear_slots_of_type(ActorRecord *owner, s8 match_type);             /* extern */
#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"

void *get_unused_text_buffer(void);                          /* extern */
s32 display_text_with_fullwidth_adjustment(s8 *text);                         /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern u8 confusion_cure_text[];



/* Applies an entity update and handles its follow-up effects and state count. */
s32 use_item_to_cure_confusion(ActorRecord *entity, DungeonItemEntry *update_value, s16 mode) {
    u16 *type_flags;
    void *call_arg;
    void *context_arg;
    void *saved_context;
    s32 type_index;
    void *effect_result;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = update_value;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, update_value, mode);
        call_arg = entity;
        type_index = (*((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        type_flags = (u16 *)&entity_action_selectors;
        if (feed_actor_restore_mp(call_arg, (type_flags[type_index] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, update_value);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(((ObjectNodeHeader *)entity - 1)->position, 0xC02020, entity);
    if ((entity->flags14 & ACTOR_PARTY_MEMBER) && !(entity->flags1C & ACTOR_CONFUSED)) {
        effect_result = get_unused_text_buffer();
        call_arg = &confusion_cure_text;
        context_arg = effect_result;
        saved_context = context_arg;
        effect_result = expand_text_control_codes(call_arg, context_arg);
        clear_byte_and_advance(effect_result);
        display_text_with_fullwidth_adjustment(saved_context);
    }
    clear_slots_of_type(entity, STATUS_CONFUSION);
    clear_slot_and_update_linked_state(update_value);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
