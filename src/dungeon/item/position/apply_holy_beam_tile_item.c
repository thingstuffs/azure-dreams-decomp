#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"


extern s32 get_entity_effect_value(void *actor, s32 value);
extern void clear_slots_of_type(void *actor, s32 value);
#include "dungeon/player/item.h"
extern void clear_slot_and_update_linked_state(void *object_data);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void *write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_typed_formatted_value(void *object_data, s32 value);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern s32 write_status_prefix_bytes(s32 value);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 flags);
extern void play_sound_if_enabled(s32 value);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s16 select_and_initialize_entry_at_position(u8 x, u8 y, s16 value, s32 mode, s32 object);
extern s32 create_central_and_child_effects(u8 x, u8 y, s16 value, s32 mode, s32 object_data_value);

extern u8 D_800893D4[];
extern u8 D_800E1684[];
extern u8 D_800E169A[];
extern u8 dungeon_floor_object_positions[];


   /* the 0x14 bytes before arg0 in apply_holy_beam_tile_item, addressed as arg0[-1] */

typedef struct S_800C2CDC_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x86];
    u8 * unk_110;
} S_800C2CDC_0;   /* arg0 in apply_holy_beam_tile_item */

   /* entity in apply_holy_beam_tile_item */

typedef struct S_800C2CDC_2 {
    u8 pad_00[0x20];
    s16 unk_20;
} S_800C2CDC_2;   /* object_fields in apply_holy_beam_tile_item */

typedef struct S_800C2CDC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C2CDC_3;   /* entries + (index * 24) in apply_holy_beam_tile_item */

typedef struct S_800C2CDC_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C2CDC_4;   /* counter_base in apply_holy_beam_tile_item */

/* Creates an object at the entity position, updates its state, and decrements the global count. */
s32 apply_holy_beam_tile_item(void *actor, u8 *object_data, s16 action_type) {
    MovingTile *entity;
    s32 object_fields;
    u8 *entries;
    s32 object;
    void *handle;
    s16 entry_index;

    if (actor == *(u8 **)((u8 *)(&dungeon_actor_ring_anchor))) {
        ((S_800C2CDC_0 *)actor)->unk_110 = object_data;
        begin_mode_selected_item_action(actor, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), actor);
        return 0;
    }

    entity = ((SpriteLinkPrefixView *)actor)[-1].sprite;
    object = create_central_and_child_effects(entity->tile_x,
                           entity->tile_y,
                           ((S_800C2CDC_0 *)actor)->unk_88, 7, *object_data);
    if (object == 0) {
        return 0;
    }

    play_sound_if_enabled(0x816);
    object_fields = object + 0x20;
    entry_index = select_and_initialize_entry_at_position(entity->tile_x,
                          entity->tile_y,
                          ((S_800C2CDC_0 *)actor)->unk_88, 6, object);
    entries = dungeon_floor_object_positions;
    ((S_800C2CDC_2 *)object_fields)->unk_20 = entry_index;
    ((S_800C2CDC_3 *)(entries + (entry_index * 24)))->unk_08 = 0;

    handle = get_unused_text_buffer();
    object = write_text_byte_and_advance(8, handle);

    if (action_type == 13) {
        object = write_status_prefix_bytes(expand_text_control_codes(D_800893D4,
                    append_entity_display_text(actor, expand_text_control_codes(D_800E1684,
                        append_typed_formatted_value(object_data, object)))));

        if (!(((S_800C2CDC_0 *)actor)->unk_1C & ACTOR_PLAYER_SIDE) &&
            ((S_800C2CDC_0 *)actor)->unk_13 < 0x31) {
            update_map_cell_flags_with_item_limit(entity->tile_x,
                          entity->tile_y, 0x3000);
            ((S_800C2CDC_0 *)actor)->unk_1C |= ACTOR_PLAYER_SIDE;
            cycle_map_cell_flags(entity->tile_x,
                          entity->tile_y, 0x300);
        }

        clear_byte_and_advance(object);
        display_text_with_fullwidth_adjustment(handle);
    }

    handle = get_unused_text_buffer();
    clear_byte_and_advance(expand_text_control_codes(D_800E169A, handle));
    display_text_with_fullwidth_adjustment(handle);

    if ((s16)get_entity_effect_value(actor, STATUS_CONFUSION) != 0) {
        clear_slots_of_type(actor, STATUS_CONFUSION);
    }

    cycle_map_cell_flags(entity->tile_x, entity->tile_y, 2);
    clear_slot_and_update_linked_state(object_data);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}
