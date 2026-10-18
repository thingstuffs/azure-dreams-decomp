#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

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




void begin_mode_selected_item_action(); /* extern */
s32 process_record_and_update_linked_state(s32, s32);           /* extern */
void clear_slot_and_update_linked_state();                         /* extern */
void display_formatted_context_message();                   /* extern */
void apply_item_effect_at_entity_position();                 /* extern */
void display_actor_item_status_message();            /* extern */
s32 apply_actor_food_preference();                /* extern */
s32 create_five_point_effect(); /* extern */
extern M2C_UNK D_800C135C;
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_800E1482;

/* Handles an object operation and updates its state or triggers its effect. */
s32 use_item_to_draw_flame_circle(void *object, s32 value, s16 operation, s32 context) {
    MovingTile *object_data;
    s32 result;

    if (operation == 0xD) {
        return process_record_and_update_linked_state(value, context);
    }
    if (object == D_800E3D7C) {
        ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_124 = value;
        begin_mode_selected_item_action(object, &D_80083780.x.v, &D_80082E80.unk_000, 0);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        display_actor_item_status_message(object, value, operation);
        if (apply_actor_food_preference(object, D_800DDE84[((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_27] & 3, value) == 0) {
            apply_item_effect_at_entity_position(object, value);
            return 1;
        }

        g_dungeon_status.unk_0A--;
    } else {
        object_data = ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_00;
        if (create_five_point_effect(object_data->unk_24, object_data->unk_25, ((S_800C13C8_0 *)((u8 *)object - 0x14))->unk_9C,
            &D_800DEAE0, 0x5000, 0x202080, &D_800C135C) == 0) {
            result = 0;
            return result;
        }
        display_formatted_context_message(&D_800E1482);
    }
    clear_slot_and_update_linked_state(value);
    result = 1;
    return result;
}
