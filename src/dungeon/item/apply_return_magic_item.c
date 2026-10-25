#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct Struct_80083460 {
    u8 pad[10];
    u16 count;
} Struct_80083460;

extern s16 current_dungeon_floor;
extern u8 return_magic_begin_address[];
extern u8 D_800DF45C[];
extern u8 D_800E1375[];
extern u8 D_800E13B7[];

extern s32 test_resident_bit(s32);
#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void display_formatted_context_message(void *);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32);
extern s32 feed_actor_restore_mp(void *, u16, s32);
extern s32 create_five_point_effect(s16 tile_x, s16 tile_y, s16 pos_z, void *transform_data, s16 scale, s32 setup_word_5c, s32 setup_word_60);

/* Apply an event to the target and update the event count on completion. */
s32 apply_return_magic_item(u8 *entity, s32 event, s16 target_type, s32 target_record) {
    u8 *entity_info;

    if (target_type == 0xD) {
        return process_record_and_update_linked_state(event, target_record);
    }
    if ((void *)entity == ((u8 *)dungeon_actor_ring_anchor)) {
        *(s32 *)(entity + 0x110) = event;
        begin_mode_selected_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), 0);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        display_actor_item_status_message(entity, event);
        if (feed_actor_restore_mp(entity, entity_action_selectors[entity[0x13]] & 3, event) == 0) {
            place_actor_item(entity, event);
            return 1;
        }
        ((Struct_80083460 *)&g_dungeon_status)->count--;
    } else {
        if (*(s32 *)0x80012090 == 0 && current_dungeon_floor == 0x28 && test_resident_bit(0xA2) == 0) {
            display_formatted_context_message(D_800E1375);
            ((Struct_80083460 *)&g_dungeon_status)->count--;
            clear_slot_and_update_linked_state(event);
            return 1;
        }
        entity_info = *(u8 **)(entity - 0x14);
        if (create_five_point_effect(entity_info[0x24], entity_info[0x25],
                          *(s16 *)(entity + 0x88), D_800DF45C,
                          0x2800, 0x208020, return_magic_begin_address) == 0) {
            return 0;
        }
        display_formatted_context_message(D_800E13B7);
        ((Struct_80083460 *)&g_dungeon_status)->count++;
    }
    clear_slot_and_update_linked_state(event);
    return 1;
}
