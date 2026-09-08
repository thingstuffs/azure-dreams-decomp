#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800C9B44_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
M2C_UNK func_800C9C94();     /* extern */
M2C_UNK func_800C9DB8();     
typedef struct S_800C9B44_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C9B44_0;   /* arg1 in func_800C9B44 */


/* extern */

/* Advance motion and handle reaching the position limit. */
void func_800C9B44(Rec_func_800C9B44_arg0 *state, S_800C9B44_0 *motion, M2C_UNK context) {
    u16 remaining_count;

    motion->unk_08.at00.v = (s32) (motion->unk_08.at00.v + motion->unk_14);
    if (func_800C2AE8(motion) < motion->unk_08.at02.v) {
        motion->unk_08.at02.v = func_800C2AE8(motion);
        remaining_count = state->unk_90 - 1;
        state->unk_90 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            motion->unk_14 = 0;
            func_800C9DB8(state, motion, context);
            return;
        }
        func_800C9C94(state, motion, context);
        return;
    }
    func_80095388(motion);
}
