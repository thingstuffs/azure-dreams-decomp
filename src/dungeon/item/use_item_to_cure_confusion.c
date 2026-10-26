#include "shared/actor_property_flags.h"
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

typedef struct {
    s8 type;
    s8 value;
} Slot;
typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

void clear_slots_of_type(SlotOwner *owner, s8 match_type);             /* extern */
#include "dungeon/player/item.h"
void clear_slot_and_update_linked_state();                         /* extern */
void *get_unused_text_buffer(void);                          /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
void place_actor_item();                 /* extern */
void display_item_status_message();            /* extern */
s32 feed_actor_restore_mp();            /* extern */
void create_timed_paired_particle_emitter();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern u8 confusion_cure_text[];


typedef struct S_800BD5C4_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD5C4_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_cure_confusion, addressed as arg0[-1] */


/* Applies an entity update and handles its follow-up effects and state count. */
s32 use_item_to_cure_confusion(void *entity, s32 update_value, s16 mode) {
    u16 *type_flags;
    void *call_arg;
    void *context_arg;
    void *saved_context;
    s32 type_index;
    void *effect_result;

    if (entity == dungeon_actor_ring_anchor) {
        ((EntityRec *)entity)->unk_110 = update_value;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, update_value, mode);
        call_arg = entity;
        type_index = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        type_flags = (u16 *)&entity_action_selectors;
        if (feed_actor_restore_mp(call_arg, (type_flags[type_index] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, update_value);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(((S_800BD5C4_0_pre *)entity)[-1].unk_00, 0xC02020, entity);
    if ((((EntityRec *)entity)->flags14 & ACTOR_PARTY_MEMBER) && !(((EntityRec *)entity)->flags1C & ACTOR_CONFUSED)) {
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
