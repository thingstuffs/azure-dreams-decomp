#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */

typedef struct S_800CA458_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA458_0;   /* arg1 in func_800CA458 */


void func_800CA458(Rec_func_80094268_arg0 *arg0, S_800CA458_0 *arg1) {
    u16 temp_v0;

    arg1->unk_00 = (s32) (arg1->unk_00 - 0x3333);
    arg1->unk_04 = (s32) (arg1->unk_04 + 0x40000);
    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80033AA8(0x49);
        func_8008F134(arg0);
        func_800C30A4(arg0);
    }
}
