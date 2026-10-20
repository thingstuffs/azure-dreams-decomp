#include "common.h"
void reset_matching_transform_object(s32 object_addr);
extern s32 D_800FE4A0;

typedef struct S_800C2864_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x3B];
    s32 * unk_50;
} S_800C2864_0;   /* arg0 in set_transform_object_data */

/* Set the object's flag and data pointer unless it is the excluded object. */
void set_transform_object_data(S_800C2864_0 *object) {
    if (D_800FE4A0 != object) {
        object->unk_14 = 1;
        object->unk_50 = &reset_matching_transform_object;
    }
}
