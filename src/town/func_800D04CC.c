#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
M2C_UNK func_800CE04C();     /* extern */

typedef struct S_800CDC2C_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800CDC2C_0;   /* arg0 in advance_object_and_run_follow_up */


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void advance_object_and_run_follow_up(S_800CDC2C_0 *object, EntityRec *motion, M2C_UNK context) {
    object->unk_72 = (u16) (object->unk_72 + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
