#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */

typedef struct S_800C56A8_0 {
    s32 unk_00;
    s32 unk_04;
} S_800C56A8_0;   /* arg1 in func_800C56A8 */

typedef struct S_800C56A8_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C56A8_1;   /* arg0 in func_800C56A8 */

void func_800C56A8(S_800C56A8_1 *arg0, S_800C56A8_0 *arg1) {
    u16 temp_v0;

    arg1->unk_00 = (s32) (arg1->unk_00 + 0xFFFEAAAB);
    arg1->unk_04 = (s32) (arg1->unk_04 + 0x40000);
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80033AA8(0x54);
        func_8008F134(arg0);
        func_800C30A4(arg0);
    }
}
