#include "common.h"
#include "m2c_compat.h"

void *initialize_scene_object_in_buffer();   /* extern */
extern M2C_UNK D_800A24FC;
extern M2C_UNK D_80100BF0;

typedef struct S_800A24C4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800A24C4_0;

/* Create an object, install its handler, and clear its state. */
void create_and_reset_resource_object(void) {
    S_800A24C4_0 *object;

    object = initialize_scene_object_in_buffer(0x136, &D_80100BF0, 0x49);
    object->unk_10 = &D_800A24FC;
    object->unk_2C = 0;
}
