#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173FF4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80173FF4_0;   /* arg1 in func_80173FF4 */

typedef struct S_80173FF4_1 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} S_80173FF4_1;   /* arg0 in func_80173FF4; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                     /* extern */
extern s32 D_800814A0[3];

/* Advance state and decrement the record count, setting record and global flags at completion. */
void func_80173FF4(void *record_data, S_80173FF4_0 *state, M2C_UNK update_arg) {
    u16 remaining_count;

    state->unk_08 = (s32) (state->unk_08 + 0x10000);
    func_800478B8(update_arg);
    remaining_count = ((S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
