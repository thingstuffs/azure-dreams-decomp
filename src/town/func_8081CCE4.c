#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80026D28;

typedef struct S_80026CE4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x5E];
    s16 unk_72;
} S_80026CE4_0;

/* Allocate a type 2 object and initialize its data pointer and value. */
void create_timed_sound(s16 value) {
    S_80026CE4_0 *object;

    object = func_8003FC64(2);
    if (object != NULL) {
        object->unk_10 = &D_80026D28;
        object->unk_72 = value;
    }
}
