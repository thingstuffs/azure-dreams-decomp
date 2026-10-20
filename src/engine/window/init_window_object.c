#include "common.h"

#include "common.h"

typedef struct S_80035614_0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    u8 pad_4D[0x1B];
    s32 * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
} S_80035614_0;   /* arg0 in init_window_object */
void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner); /* extern */
extern u8 attached_window_object_storage[];
extern u8 attached_window_node_storage[];
void scroll_window_x();

/* Initialize the object, clear its state byte, and set its next handler. */
void init_window_object(S_80035614_0 *object) {
    initialize_attached_message_window_node(&attached_window_node_storage, &attached_window_object_storage, object, 0, object->unk_74);
    object->unk_4C = 0;
    object->unk_68 = &scroll_window_x;
}
