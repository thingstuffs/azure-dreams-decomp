#include "common.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct Entity {
    u8 pad[0x13];
    u8 unk_13;
    u32 flags;
    u8 pad2[0x110 - 0x18];
    DungeonItemEntry *unk_110;
} Entity;

extern s32 dungeon_mode_state;
extern s16 current_dungeon_floor;
extern u8 D_80089384[];
extern u8 D_800E15FE[];
extern u8 D_800E1677[];

s32 test_resident_bit(s32);
#include "dungeon/player/item.h"
void clear_slot_and_update_linked_state(struct DungeonItemEntry *);
void *get_unused_text_buffer(void);
u8 *expand_text_control_codes(u8 *src, u8 *dst);
void clear_byte_and_advance(s8 *byte_ptr);
u8 * append_typed_formatted_value(struct DungeonItemEntry *,u8 *);
u8 *append_entity_display_text(void *record, u8 *out);
void display_formatted_context_message(void *);
void display_text_with_fullwidth_adjustment(s8 *text);
void place_actor_item(Entity *, struct DungeonItemEntry *);
void display_item_status_message(Entity *, struct DungeonItemEntry *, s16);
s32 create_return_magic_effect(Entity *);

/* Handles an item's effect on an entity and updates the pending action count. */
s32 use_return_magic(Entity *entity, DungeonItemEntry *item, s16 action_type) {
    if (entity == ((Entity *)dungeon_actor_ring_anchor)) {
        entity->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }
    if (entity->flags & 0x4000) {
        if ((u32)(entity->unk_13 - 3) < 0x2B) {
            if (dungeon_mode_state == 0 && current_dungeon_floor == 0x28 && test_resident_bit(0xA2) == 0) {
                DungeonGlobalStatus *counter;
                display_formatted_context_message(D_800E15FE);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
                clear_slot_and_update_linked_state(item);
                return 1;
            }
            if (create_return_magic_effect(entity) != 0) {
                DungeonGlobalStatus *counter;
                clear_slot_and_update_linked_state(item);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
                return 1;
            }
            return 0;
        }
        {
            void *original_value;
            void *current_value;
            void *adjusted_value;

            adjusted_value = append_entity_display_text(entity, current_value = get_unused_text_buffer());
            original_value = current_value;
            current_value = adjusted_value;
            clear_byte_and_advance(expand_text_control_codes(D_80089384, append_typed_formatted_value(item, expand_text_control_codes(D_800E1677, current_value))));
            display_text_with_fullwidth_adjustment(original_value);
            place_actor_item(entity, item);
        }
        return 1;
    }
    if ((u32)(entity->unk_13 - 3) < 0x2B) {
        if (create_return_magic_effect(entity) != 0) {
            DungeonGlobalStatus *counter = &g_dungeon_status;
            (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
            return 1;
        }
        return 0;
    }
    display_item_status_message(entity, item, action_type);
    {
        DungeonGlobalStatus *counter = &g_dungeon_status;
        (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
    }
    return 1;
}
