#include "dungeon/actor/status.h"
#include "shared/monster_ids.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/system.h"
#include "engine/menu.h"
#include "dungeon/player/item.h"
#include "dungeon/player/state.h"
#include "dungeon/item/message.h"

typedef struct S_800C08A4_0 {
    void * unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    u8 pad_2C[0x34];
    u8 unk_60;
    u8 unk_61;
    u8 pad_62[0x1];
    u8 unk_63;
    u8 pad_64[0xC4];
    u8 * unk_128;
} S_800C08A4_0;   /* Pointer addresses record offset 0x18. */

typedef struct S_800C08A4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C08A4_1;

typedef struct S_800C08A4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C08A4_2;   /* counter_base in apply_monster_equipment_item */



void * copy_fullwidth_vowel_bytes(void *dst, void *character);
 /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
void * append_value_seven_suffix(u8 *dst);
s32 display_text_with_fullwidth_adjustment(s8 *text); /* extern */
struct DungeonItemEntry;
void place_actor_item(void *object_context, struct DungeonItemEntry *target); /* extern */
s32 generate_random_value(void);
s32 place_item_at_valid_floor_position(); /* extern */
extern u8 D_80089378[];
extern u8 D_8008937C[];
extern u8 D_800E13DA[15];
extern u8 D_800E13E9[18];

/* Applies an entity action to a target and updates the pending count. */
s32 apply_monster_equipment_item(u8 *entity, DungeonItemEntry *target, s16 action, void *context) {
    void *entity_value;
    void *event_value;
    void *external_entity_value;
    void *external_event_value;
    u8 *compare_ptr;
    void *script;
    S_800C08A4_1 *position;

    if (action == 0xD) {
        if ((((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_2B != MONSTER_TROLL) || ((generate_random_value() & 1) != 0)) {
            return process_record_and_update_linked_state(target, context);
        }
    }
    compare_ptr = ((u8 *)dungeon_actor_ring_anchor);
    if (entity == compare_ptr) {
        ((PlayerRecord *)entity)->pending_item_action = target;
        begin_mode_selected_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }
    compare_ptr = (u8 *) 0x9FFFFFFF;
    if ((u32) entity <= (u32) compare_ptr) {
        if (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_2B != MONSTER_TROLL) {
            void *body = entity;
            ActorRecord *actor = body;

            display_actor_item_status_message(entity, target);
            if (feed_actor_restore_mp(actor, (entity_action_selectors[actor->species] >> 4) & 3, 0) == 0) {
                place_actor_item(entity, target);
                return 1;
            }
            clear_slot_and_update_linked_state(target);
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
            return 1;

        }
        position = ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_00;
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 & 0xDF);
        place_item_at_valid_floor_position((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A,
            lookup_item_category_mapped_value(((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_61,
            ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_60), entity + 0x48);
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_60 = (u8) target->unk_00;
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 | 0x20);
        script = get_unused_text_buffer();
        entity_value = append_entity_display_text(entity, script);
        event_value = expand_text_control_codes(D_800E13DA, entity_value);
        {
            void *node_offset;
            void *result;

            external_entity_value = append_value_seven_suffix(event_value);
            result = expand_text_control_codes(D_80089378, external_entity_value);
            node_offset = external_entity_value - 2;
            external_entity_value = result;
            result = append_typed_formatted_value(target, external_entity_value);
            {

                entity_value = external_entity_value;
                external_entity_value = result;
                copy_fullwidth_vowel_bytes(node_offset, entity_value);
            }
            clear_byte_and_advance(expand_text_control_codes(D_8008937C, external_entity_value));
        }
        display_text_with_fullwidth_adjustment(script);
        clear_slot_and_update_linked_state(target);
    } else {
        script = get_unused_text_buffer();
        external_entity_value = append_entity_display_text(entity, script);
        external_event_value = expand_text_control_codes(D_800E13E9, external_entity_value);
        {
            void *node_offset;
            void *result;

            external_entity_value = append_value_seven_suffix(external_event_value);
            result = expand_text_control_codes(D_80089378, external_entity_value);
            node_offset = external_entity_value - 2;
            external_entity_value = result;
            result = append_typed_formatted_value(target, external_entity_value);
            {

                entity_value = external_entity_value;
                external_entity_value = result;
                copy_fullwidth_vowel_bytes(node_offset, entity_value);
            }
            clear_byte_and_advance(expand_text_control_codes(D_8008937C, external_entity_value));
        }
        display_text_with_fullwidth_adjustment(script);
    }
    {
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    }
    return 1;
}
