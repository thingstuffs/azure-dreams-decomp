#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C4174();
M2C_UNK func_800C7E58();



typedef struct S_800C7DB8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7DB8_1;   /* arg1 in func_800C7DB8 */

void func_800C7DB8(Rec_func_80094268_arg0 *arg0, S_800C7DB8_1 *arg1) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((s16) temp_v0 <= 0) {
        func_800C4174(arg0);
        arg1->unk_02 = (u16) arg0->unk_84.as_u16;
        arg1->unk_06 = (s16) arg0->unk_86.as_u16;
        func_800C7E58();
        return;
    }
    arg1->unk_02 = (u16) (arg1->unk_02 + ((s32) ((s16) arg0->unk_84.as_u16 - (s16) arg1->unk_02) / (s16) temp_v0));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) ((s16) arg0->unk_86.as_u16 - arg1->unk_06) / (s16) arg0->unk_6C.as_u16));
}
