#include "common.h"
#include "m2c_compat.h"

s16 *func_8008C0F0();                       /* extern */

typedef struct S_800A8BBC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800A8BBC_0;   /* arg4 in func_800A8BBC */

void func_800A8BBC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, S_800A8BBC_0 *arg4) {
    *func_8008C0F0((s16) (arg4->unk_02 - 0x40), (s16) (arg4->unk_06 - 0x40)) = arg0;
    *func_8008C0F0((s16) arg4->unk_02, (s16) (arg4->unk_06 - 0x40)) = arg1;
    *func_8008C0F0((s16) (arg4->unk_02 - 0x40), (s16) arg4->unk_06) = arg2;
    *func_8008C0F0((s16) arg4->unk_02, (s16) arg4->unk_06) = arg3;
}
