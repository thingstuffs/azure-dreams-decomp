#include "shared/actor_status_flags.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "dungeon/level.h"
#include "dungeon/item/position.h"
#include "dungeon/item/state.h"
#include "dungeon/player/state.h"
#include "dungeon/system.h"
#include "engine/entity.h"

#include "dungeon/player/item.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
extern void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 flags);
extern s32 select_and_initialize_entry_at_position(s16 x, s16 y, s16 z, s32 type_id, s32 entry_value);
extern s32 create_central_and_child_effects(u8 x, u8 y, s16 value, s32 mode, s32 object_data_value);

extern u8 D_800893D4[];
extern u8 D_800E1684[];
extern u8 D_800E169A[];
extern u8 dungeon_floor_object_positions[];


   /* the 0x14 bytes before arg0 in apply_holy_beam_tile_item, addressed as arg0[-1] */

   /* entity in apply_holy_beam_tile_item */

typedef struct S_800C2CDC_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800C2CDC_2;   /* object_fields in apply_holy_beam_tile_item */

typedef struct S_800C2CDC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C2CDC_3;   /* entries + (index * 24) in apply_holy_beam_tile_item */

/* Creates an object at the entity position, updates its state, and decrements the global count. */
s32 apply_holy_beam_tile_item(ActorRecord *body, DungeonItemEntry *object_data, s16 action_type) {
    MovingTile *entity;
    s32 object_fields;
    u8 *entries;
    s32 object;
    void *handle;
    s16 entry_index;

    if (body == *(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) {
        ((PlayerRecord *)body)->pending_item_action = object_data;
        begin_mode_selected_item_action(body, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), body);
        return 0;
    }

    entity = ((SpriteLinkPrefixView *)body)[-1].sprite;
    object = create_central_and_child_effects(entity->tile_x,
                           entity->tile_y,
                           body->ground_height, 7, object_data->unk_00);
    if (object == 0) {
        return 0;
    }

    play_sound_if_enabled(0x816);
    object_fields = object + 0x20;
    entry_index = select_and_initialize_entry_at_position(entity->tile_x,
                          entity->tile_y,
                          body->ground_height, 6, object);
    entries = dungeon_floor_object_positions;
    ((S_800C2CDC_2 *)object_fields)->unk_20 = entry_index;
    ((S_800C2CDC_3 *)(entries + (entry_index * 24)))->unk_08 = 0;

    handle = get_unused_text_buffer();
    object = write_text_byte_and_advance(8, handle);

    if (action_type == 13) {
        object = write_status_prefix_bytes(expand_text_control_codes(D_800893D4,
                    append_entity_display_text(body, expand_text_control_codes(D_800E1684,
                        append_typed_formatted_value(object_data, object)))));

        if (!(body->flags1C & ACTOR_PLAYER_SIDE) &&
            body->species < 0x31) {
            update_map_cell_flags_with_item_limit(entity->tile_x,
                          entity->tile_y, 0x3000);
            body->flags1C |= ACTOR_PLAYER_SIDE;
            cycle_map_cell_flags(entity->tile_x,
                          entity->tile_y, 0x300);
        }

        clear_byte_and_advance(object);
        display_text_with_fullwidth_adjustment(handle);
    }

    handle = get_unused_text_buffer();
    clear_byte_and_advance(expand_text_control_codes(D_800E169A, handle));
    display_text_with_fullwidth_adjustment(handle);

    if ((s16)get_entity_effect_value(body, STATUS_CONFUSION) != 0) {
        clear_slots_of_type(body, STATUS_CONFUSION);
    }

    cycle_map_cell_flags(entity->tile_x, entity->tile_y, 2);
    clear_slot_and_update_linked_state(object_data);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
