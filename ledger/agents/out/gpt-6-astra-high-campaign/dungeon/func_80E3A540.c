#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173D40_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173D40_0;   /* arg0 in func_80173D40 */

typedef struct S_80173D40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173D40_1;   /* arg2 in func_80173D40 */


/* Resets state to code 0x19 and updates the associated record flags. */
void func_80173D40(S_80173D40_0 *state, M2C_UNK unused, S_80173D40_1 *flag_record, Rec_D_800E3D7C *record) {
    state->unk_9A = 0x19;
    state->unk_9B = 0;
    state->unk_8C = 0;
    flag_record->unk_14 = (u16) (flag_record->unk_14 & 0xF7FF);
    state->unk_96 = 0;
    record->unk_1C.as_s32 = (s32) (record->unk_1C.as_s32 | 0x10000000);
}
