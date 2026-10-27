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
#include "m2c_compat.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/state.h"


extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);             /* extern */
#include "dungeon/player/item.h"
void *get_unused_text_buffer(void);                          /* extern */
s32 display_text_with_fullwidth_adjustment(s8 *text);                         /* extern */
void create_timed_paired_particle_emitter();            /* extern */
extern s32 g_dungeon_status[3];
extern u8 poison_cure_text[25];


typedef struct S_800BD45C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD45C_0_pre;   /* the 0x18 bytes before arg0 in use_item_to_cure_poison, addressed as arg0[-1] */


typedef struct S_800BD45C_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BD45C_1;   /* counter in use_item_to_cure_poison */

/* Applies an item's effect to an entity and consumes the processed item. */
s32 use_item_to_cure_poison(void *entity, DungeonItemEntry *item, s16 action) {
    u16 *type_flags;
    s32 *item_counts;

    if (entity == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)entity)->pending_item_action = item;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        void *call_entity;
        u8 type_id;

        display_item_status_message(entity, item, action);
        call_entity = entity;
        type_id = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        if (feed_actor_restore_mp(call_entity, (entity_action_selectors[type_id] >> 6) & 3, 0) == 0) {
            place_actor_item(entity, item);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(((S_800BD45C_0_pre *)entity)[-1].unk_00, 0x802080, entity);
    if ((((EntityRec *)entity)->flags14 & ACTOR_PARTY_MEMBER) && !(((EntityRec *)entity)->flags1C & ACTOR_POISONED)) {
        void *message_text;
        void *message_pos;
        void *message_start;
        void *message_end;

        message_end = get_unused_text_buffer();
        message_text = &poison_cure_text;
        message_pos = message_end;
        message_start = message_pos;
        message_end = expand_text_control_codes(message_text, message_pos);
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }
    clear_slots_of_type(entity, STATUS_POISON);
    clear_slot_and_update_linked_state(item);
    item_counts = g_dungeon_status;
    ((S_800BD45C_1 *)item_counts)->unk_0A = (u16) (((S_800BD45C_1 *)item_counts)->unk_0A - 1);
    return 1;
}
