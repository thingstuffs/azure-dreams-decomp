#include "dungeon/item.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
extern u8 reference_tile_object[],view_reference_entity[],D_800893D8[],D_800E16E3[],D_800E1713[],dungeon_floor_object_positions[];
extern s16 select_and_initialize_entry_at_position(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value);
extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern void clear_slot_and_update_linked_state(void *);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void display_formatted_context_message(void *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void try_apply_confusion_status(void *, s32, s32);
/* Processes an actor's item and updates its object entry, effects, and item count. */
s32 apply_malicious_light_tile_item(void *actor, u8 *item, s16 action) {
    s16 entry_index;
    s32 message_handle;
    s32 saved_handle, object_addr;
    DungeonGlobalStatus *counter_base;
    void *entity;
    u8 *object_fields;
    u8 *entries;

    if (actor == ((u8 *)dungeon_actor_ring_anchor)) {
        F(actor, u8 *, 0x110) = item;
        begin_mode_selected_item_action(actor, view_reference_entity, reference_tile_object, actor);
        return 0;
    }

    entity = F(actor, void **, -0x14);
    object_addr = create_central_and_child_effects(F(entity, u8, 0x24), F(entity, u8, 0x25),
                                F(actor, s16, 0x88), -1, *item);
    if (object_addr != 0) {
        play_sound_if_enabled(0x60D);
        object_fields = (u8 *)object_addr + 0x20;
        entry_index = select_and_initialize_entry_at_position(F(entity, u8, 0x24), F(entity, u8, 0x25),
                                    F(actor, s16, 0x88), 5, object_addr);
        entries = dungeon_floor_object_positions;
        F(object_fields, s16, 0x20) = entry_index;
        F(entries + entry_index * 0x18, s32, 8) = 0;
        message_handle = get_unused_text_buffer();
        saved_handle = message_handle;

        if (action == 0xD) {
            message_handle = append_typed_formatted_value(item, message_handle);
            message_handle = expand_text_control_codes(D_800E1713, message_handle);
            message_handle = append_entity_display_text(actor, message_handle);
            message_handle = expand_text_control_codes(D_800893D8, message_handle);
            message_handle = write_status_prefix_bytes(message_handle);
            clear_byte_and_advance(message_handle);
            display_text_with_fullwidth_adjustment(saved_handle);
        }

        display_formatted_context_message(D_800E16E3);
        try_apply_confusion_status(actor, 0x100, 0x10);
        cycle_map_cell_flags(F(entity, u8, 0x24), F(entity, u8, 0x25), 0x10);
        clear_slot_and_update_linked_state(item);
        counter_base = &g_dungeon_status;
        (*(u16 *)&counter_base->activity_counts.parts.pending_action_count)--;
        return 1;
    }
    return 0;
}
