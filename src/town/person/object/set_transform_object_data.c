#include "common.h"
void reset_matching_transform_object(s32 object_addr);
extern s32 current_transform_object;

typedef struct S_800C2864_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    void (*unk_50)(s32);
} S_800C2864_0;   /* arg0 in set_transform_object_data */

/* Set the object's flag and data pointer unless it is the excluded object. */
void set_transform_object_data(S_800C2864_0 *object) {
    if (current_transform_object != object) {
        object->unk_14 = 1;
        object->unk_50 = &reset_matching_transform_object;
    }
}
