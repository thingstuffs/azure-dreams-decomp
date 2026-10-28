#include "town/player/carry_item.h"
#include "shared/object_node.h"

extern void initialize_record_and_select_active_data(void *record, s32 setup_value, s32 init_value);

extern s32 scene_object_payload_alias;
extern s32 D_8009C340;

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
    u8 *base;
    ObjectNodeHeader *input_values;
    s32 first_value;
    s32 second_value;
    u8 *saved_object;
    void *context;

    base = (u8 *)&scene_object_payload_alias;
    context = base;
    input_values = base - 0x20;
    first_value = (s32)input_values->position;
    second_value = (s32)input_values->sprite;
    saved_object = ((CarryRecord *)base)->linked_object;

    if (get_linked_carry_item_data(context, first_value, second_value) != 0) {
        CarryLinkedObject *linked_object;

        initialize_record_and_select_active_data(base, first_value, second_value);
        do {
            linked_object = (CarryLinkedObject *)((CarryRecord *)base)->linked_object;
        } while (0);
        if (linked_object != 0 && (linked_object->type == 4 || linked_object->state == 0xD)) {
            ((CarryLinkedObject *)saved_object)->handler = &D_8009C340;
            ((CarryRecord *)base)->linked_object = 0;
        }
    }
}
