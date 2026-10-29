#include "common.h"
#include "m2c_compat.h"
#include "town/person/object.h"

extern void D_800C2864();
extern void *current_transform_object;

typedef struct S_800C283C_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    void (*unk_50)();
} S_800C283C_0;   /* v1 in reset_matching_transform_object */

/* Reset the current object's state and data pointer when its address matches. */
void reset_matching_transform_object(s32 object_addr) {
    S_800C283C_0 *current_object = current_transform_object;
    if (current_object == (void *)object_addr) {
        current_object->unk_14 = 0;
        current_object->unk_50 = &D_800C2864;
    }
}
