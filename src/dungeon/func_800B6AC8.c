#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern void dungeonUpdateWrappedTextureScroll(void *scrollState);

typedef struct S_800BC228_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800BC228_0;

/* Create an object with dungeonUpdateWrappedTextureScroll as its data pointer and store the supplied value. */
void dungeonCreateWrappedTextureScroll(s16 value) {
    S_800BC228_0 *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = dungeonUpdateWrappedTextureScroll;
        object->unk_2C = value;
    }
}
