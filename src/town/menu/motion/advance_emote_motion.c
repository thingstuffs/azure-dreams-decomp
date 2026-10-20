#include "common.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14();                 /* extern */
void advance_position_and_handle_ground_contact(void *entity, void *motion, s32 context);


typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A7360_1;   /* arg0 in advance_emote_motion */

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void advance_emote_motion(S_800A7360_1 *object, EntityRec *motion) {
    motion->x.v = (s32) (motion->x.v + motion->unk_0C);
    motion->y.v = (s32) (motion->y.v + motion->unk_10);
    motion->z.v = (s32) (motion->z.v + (motion->flags14));
    add_hex_20000_s_signed_offset_hex_14(motion, (motion->flags14));
    if (motion->flags14 >= 0) {
        object->unk_50 = &advance_position_and_handle_ground_contact;
    }
}
