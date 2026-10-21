#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "engine/window.h"

typedef struct S_80035614_0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    u8 pad_4D[0x1B];
    s32 * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
} S_80035614_0;   /* arg0 in init_window_object */
extern u8 attached_window_object_storage[];
extern u8 attached_window_node_storage[];

/* Initialize the object, clear its state byte, and set its next handler. */
void init_window_object(S_80035614_0 *object) {
    initialize_attached_message_window_node(&attached_window_node_storage, &attached_window_object_storage, object, 0, object->unk_74);
    object->unk_4C = 0;
    object->unk_68 = &scroll_window_x;
}
