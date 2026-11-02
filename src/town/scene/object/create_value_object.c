#include "common.h"
#include "town/scene/object.h"
#include "town/devkit/old_minigame_imports.h"

#ifndef NULL
#define NULL 0
#endif

extern u8 D_8052FEDC[];

/* Create an object and assign its data pointer and supplied value. */
void create_value_object(s16 object_value) {
    void *object;

    object = func_800373DC(2);
    if (object != NULL) {
        *(s32 *)((s8 *)object + 0x10) = (s32)D_8052FEDC;
        *(s16 *)((s8 *)object + 0x72) = object_value;
    }
}
