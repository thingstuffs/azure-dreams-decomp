#include "common.h"

#include "common.h"

typedef struct S_8003C128_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8003C128_0;   /* temp_v0 in func_8003C128 */


void *initialize_scene_object_in_buffer();   /* extern */
extern u8 D_80082D38[];
void func_8003C3B4();

/* Create an object, set its callback, and clear its state. */
void func_8003C128(void) {
    S_8003C128_0 *object;

    object = initialize_scene_object_in_buffer(0x15, &D_80082D38, 0x49);
    object->unk_10 = &func_8003C3B4;
    object->unk_20 = 0;
}
