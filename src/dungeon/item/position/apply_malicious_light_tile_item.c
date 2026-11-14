#include "dungeon/item.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/level/floor_object_positions.h"
#include "dungeon/actor/state.h"
#include "dungeon/item/position.h"
#include "dungeon/effect/dispatch.h"
#include "dungeon/item/state.h"
#include "dungeon/player/state.h"
#include "dungeon/system.h"
extern u8 reference_tile_object[],D_800893D8[],D_800E16E3[],D_800E1713[];
#include "dungeon/player/item.h"
#include "dungeon/item/message.h"

/* Processes an actor's item and updates its object entry, effects, and item count. */
s32 apply_malicious_light_tile_item(void *actor, DungeonItemEntry *item, s16 action) {
    ActorRecord *user = actor;
    s16 entry_index;
    void *message_handle;
    s32 saved_handle;
    CentralChildEffectObject *object_addr;
    DungeonGlobalStatus *counter_base;
    SpriteFrameState *sprite;
    CentralChildEffectState *placed_effect;
    D_800E39C8_entry *entries;

    if (actor == ((u8 *)dungeon_actor_ring_anchor)) {
        ((PlayerRecord *)user)->pending_item_action = item;
        begin_mode_selected_item_action(actor, &view_reference_entity, reference_tile_object, actor);
        return 0;
    }

    sprite = NODE_HEADER(actor)->sprite;
    object_addr = create_central_and_child_effects(sprite->tile_x, sprite->tile_y,
                                user->ground_height, -1, item->unk_00);
    if (object_addr != 0) {
        play_sound_if_enabled(0x60D);
        placed_effect = NODE_BODY(object_addr);
        entry_index = place_floor_trap_at_tile(sprite->tile_x, sprite->tile_y,
                                    user->ground_height, 5, (s32)object_addr);
        entries = dungeon_floor_object_positions;
        placed_effect->item_position_index = entry_index;
        entries[entry_index].field8.s = 0;
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
        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y, 0x10);
        clear_item_slot(item);
        counter_base = &g_dungeon_status;
        (*(u16 *)&counter_base->activity_counts.parts.pending_action_count)--;
        return 1;
    }
    return 0;
}
