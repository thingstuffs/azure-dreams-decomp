#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
s32 func_800C30E0();         /* extern */
M2C_UNK func_800CDF00();     /* extern */
M2C_UNK func_800CDF94();     
typedef struct S_800CDADC_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CDADC_0;   /* arg1 in func_800CDADC */


/* extern */

/* Advance motion, clamp at its limit, and handle the remaining steps. */
void func_800CDADC(Rec_func_80094268_arg0 *entity, S_800CDADC_0 *motion, M2C_UNK context) {
    u16 steps_left;

    motion->unk_08.at00.v = (s32) (motion->unk_08.at00.v + motion->unk_14);
    if (func_800C2AE8(motion) < motion->unk_08.at02.v) {
        motion->unk_08.at02.v = func_800C2AE8(motion);
        steps_left = entity->unk_90.as_u16 - 1;
        entity->unk_90.as_u16 = steps_left;
        if ((steps_left << 0x10) <= 0) {
            motion->unk_14 = 0;
            func_800CDF94(entity, motion, context);
            return;
        }
        if (func_800C30E0(entity, motion, context) == 0) {
            func_800CDF00(entity, motion, context);
            return;
        }
    } else {
        func_80095388(motion);
    }
}
