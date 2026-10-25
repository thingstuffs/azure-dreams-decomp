#include "shared/object_node.h"
#include "town/minigame.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026CE4_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x5E];
    s16 unk_72;
} S_80026CE4_0;

/* Allocate a type 2 object and initialize its data pointer and value. */
void create_timed_sound(s16 value) {
    S_80026CE4_0 *object;

    object = allocate_flagged_object_node(2);
    if (object != NULL) {
        object->unk_10 = tick_timed_sound;
        object->unk_72 = value;
    }
}
