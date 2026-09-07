#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */

typedef struct S_800CA020_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA020_0;   /* arg1 in func_800CA020 */

typedef struct S_800CA020_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800CA020_1;   /* arg2 in func_800CA020 */

void func_800CA020(void *arg0, S_800CA020_0 *arg1, S_800CA020_1 *arg2) {
    arg1->unk_00 = (s32) (arg1->unk_00 + 0x40000);
    arg1->unk_04 = (s32) (arg1->unk_04 + 0x15555);
    if (arg2->unk_14 & 0x8000) {
        func_80033AA8(0x49);
        func_8008F134(arg0);
        func_800C30A4(arg0);
    }
}
