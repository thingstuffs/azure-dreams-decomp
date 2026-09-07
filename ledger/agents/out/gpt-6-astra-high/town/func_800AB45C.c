#include "common.h"
#include "m2c_compat.h"

s16 *func_8008C0F0();                       /* extern */

typedef struct S_800A8BBC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800A8BBC_0;   /* arg4 in func_800A8BBC */

/* Writes four values to a square spaced 0x40 units apart ending at the given position. */
void func_800A8BBC(s16 top_left, s16 top_right, s16 bottom_left, s16 bottom_right, S_800A8BBC_0 *pos) {
    *func_8008C0F0((s16) (pos->unk_02 - 0x40), (s16) (pos->unk_06 - 0x40)) = top_left;
    *func_8008C0F0((s16) pos->unk_02, (s16) (pos->unk_06 - 0x40)) = top_right;
    *func_8008C0F0((s16) (pos->unk_02 - 0x40), (s16) pos->unk_06) = bottom_left;
    *func_8008C0F0((s16) pos->unk_02, (s16) pos->unk_06) = bottom_right;
}
