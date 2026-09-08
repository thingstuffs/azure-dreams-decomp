#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
s32 func_800C30E0();         /* extern */
M2C_UNK func_800CDE9C();     /* extern */
M2C_UNK func_800CDFF8();     

typedef struct S_800CDCA8_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CDCA8_1;   /* arg1 in func_800CDCA8 */

/* extern */

/* Update spin and vertical motion, then handle ground contact and remaining bounces. */
void func_800CDCA8(Rec_func_80094268_arg0 *entity, S_800CDCA8_1 *motion, M2C_UNK context) {
    u16 remaining_bounces;

    entity->unk_72.as_u16 = (u16) (entity->unk_72.as_u16 + 0x400);
    motion->unk_08.at00.v = (s32) (motion->unk_08.at00.v + motion->unk_14);
    if (func_800C2AE8(motion) < motion->unk_08.at02.v) {
        motion->unk_08.at02.v = func_800C2AE8(motion);
        remaining_bounces = entity->unk_90.as_u16 - 1;
        entity->unk_90.as_u16 = remaining_bounces;
        if ((remaining_bounces << 0x10) <= 0) {
            motion->unk_14 = 0;
            entity->unk_72.as_u16 = (u16) entity->unk_6E;
            func_800CDE9C(entity, motion, context);
            return;
        }
        if (func_800C30E0(entity, motion, context) == 0) {
            func_800CDFF8(entity, motion, context);
            return;
        }
    } else {
        func_80095388(motion);
    }
}
