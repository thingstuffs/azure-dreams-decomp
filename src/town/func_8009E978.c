#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 append_scene_list_node();                      /* extern */
void unlink_scene_list_node();                      /* extern */
extern M2C_UNK D_8009BDC0;


typedef struct S_8009C0D8_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_8009C0D8_1;   /* arg0 in initialize_moving_object */

/* Set the object flag, assign the context handler, and run object setup. */
void initialize_moving_object(S_8009C0D8_1 *context, Rec_func_80094268_arg0 *object) {
    object->unk_15 = 1;
    context->unk_50 = &D_8009BDC0;
    unlink_scene_list_node(object);
    append_scene_list_node(object);
}
