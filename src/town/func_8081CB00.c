#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026B00_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80026B00_0;   /* arg1 in func_80026B00 */

typedef struct S_80026B00_1 {
    u16 unk_00;
    u8 pad_02[0xE];
    u16 unk_10;
} S_80026B00_1;   /* arg0 in func_80026B00; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

/* Advance the position and flag the record and global state when its timer expires. */
void func_80026B00(void *record_data, S_80026B00_0 *motion) {
    u16 ticks_left;

    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    ticks_left = ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_10 - 1;
    ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_10 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
