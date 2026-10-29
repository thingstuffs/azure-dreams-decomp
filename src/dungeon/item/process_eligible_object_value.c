#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "engine/item.h"
#include "dungeon/item/message.h"
#include "dungeon/item.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

typedef struct Object {
    u8 pad[3];
    u8 flags;
} Object;

extern u8 D_800E18C0[];
extern u8 D_80088CA8[];

#include "dungeon/actor/effect.h"

/* Processes an eligible object in two stages and returns the resulting value. */
u8 *process_eligible_object_value(Object *object, u8 *input_value) {
    u8 *result = input_value;

    if (!(((u32)dungeon_actor_ring_anchor->flags1C) & ACTOR_BLIND)) {
        if ((object->flags & 0x80) || get_item_category_flags(object)) {
            result = expand_text_control_codes(
                D_800E18C0,
                append_typed_formatted_value(object, write_text_byte_and_advance(10, result)));
            object->flags &= 0x7F;
            clear_selected_item_flag_400(object);
            result = expand_text_control_codes(
                D_80088CA8,
                append_typed_formatted_value(object, result));
            clear_selected_item_flag_400(object);
        }
    }

    return result;
}
