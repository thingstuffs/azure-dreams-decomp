#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "slus/data.h"

typedef struct S_8003C128_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8003C128_0;   /* temp_v0 in func_8003C128 */

/* Create an object, set its callback, and clear its state. */
void create_marked_callback_node(void) {
    S_8003C128_0 *object;

    object = initialize_scene_object_in_buffer(0x15, &callback_node_storage, 0x49);
    object->unk_10 = &run_node_callback_and_set_marker;
    object->unk_20 = 0;
}
