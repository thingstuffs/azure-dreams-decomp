#include "town/player/initialize_record_and_select_active_data.h"
#include "town/player/carry_item.h"
#include "shared/object_node.h"
#include "town/player.h"
#include "town/player/item.h"
#include "town/event/state.h"

extern s32 scene_object_payload_alias;


typedef struct CarryRecord {
    u8 pad_00[0x2C];
    u8 *linked_object;
} CarryRecord;

typedef struct CarryLinkedObject {
    u8 pad_00[0x14];
    u8 type;
    u8 pad_15[0x38];
    u8 state;
    u8 pad_4E[2];
    s32 *handler;
} CarryLinkedObject;

/* plt_carry_item_del_ext: Updates the carried object and detaches it when its type or state matches. */
void plt_carry_item_del_ext(void) {
    CarryRecord *base;
    ObjectNodeHeader *input_values;
    struct ObjectPosition *position;
    struct SpriteFrameState *sprite;
    u8 *saved_object;
    void *context;

    base = (CarryRecord *)&scene_object_payload_alias;
    context = base;
    input_values = NODE_HEADER(base);
    position = input_values->position;
    sprite = input_values->sprite;
    saved_object = base->linked_object;

    if (get_linked_carry_item_data(context, position, sprite) != 0) {
        CarryLinkedObject *linked_object;

        initialize_record_and_select_active_data(base, position, sprite);
        do {
            linked_object = (CarryLinkedObject *)base->linked_object;
        } while (0);
        if (linked_object != 0 && (linked_object->type == 4 || linked_object->state == 0xD)) {
            ((CarryLinkedObject *)saved_object)->handler = unlink_and_remove_scene_object;
            base->linked_object = 0;
        }
    }
}
