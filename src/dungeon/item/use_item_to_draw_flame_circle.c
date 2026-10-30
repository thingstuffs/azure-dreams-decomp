#include "shared/entity_action_selectors.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/effect/screen.h"
#include "dungeon/actor.h"

typedef struct S_800C13C8_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C13C8_0;   /* arg0 in use_item_to_draw_flame_circle; pointer addresses record offset 0x14 */

typedef struct S_800C13C8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C13C8_1;   /* state in use_item_to_draw_flame_circle */




#include "dungeon/player/item.h" /* extern */
s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */           /* extern */
void clear_slot_and_update_linked_state(DungeonItemEntry *slot);                         /* extern */
void display_formatted_context_message(void *context);                   /* extern */
extern s32 D_800C135C(void);
extern u8 ribbon_sprite_entries[];
extern u8 D_800E1482[];

/* Handles an object operation and updates its state or triggers its effect. */
s32 use_item_to_draw_flame_circle(void *object, DungeonItemEntry *value, s16 operation, s32 context) {
    MovingTile *object_data;
    s32 result;

    if (operation == 0xD) {
        return process_record_and_update_linked_state(value, context);
    }
    if (object == dungeon_actor_ring_anchor) {
        ((PlayerRecord *)object)->pending_item_action = value;
        begin_mode_selected_item_action(object, &view_reference_entity.x.v, &reference_tile_object.frame_entry, 0);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        display_actor_item_status_message(object, value);
        if (feed_actor_restore_mp(object, entity_action_selectors[((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_27] & 3, value) == 0) {
            place_actor_item(object, value);
            return 1;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
    } else {
        object_data = ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_00;
        if (create_five_point_effect(object_data->tile_x, object_data->tile_y, ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_9C,
            &ribbon_sprite_entries, 0x5000, 0x202080, &D_800C135C) == 0) {
            result = 0;
            return result;
        }
        display_formatted_context_message(&D_800E1482);
    }
    clear_slot_and_update_linked_state(value);
    result = 1;
    return result;
}
