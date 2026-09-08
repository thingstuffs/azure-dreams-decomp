#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
M2C_UNK func_800C4174();     /* extern */
extern M2C_UNK D_800CE8CC;


typedef struct S_800CE800_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CE800_0;   /* arg1 in func_800CE800 */


void func_800CE800(Rec_func_80094268_arg0 *arg0, S_800CE800_0 *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + arg1->unk_14);
    if (func_800C2AE8(arg1) < arg1->unk_08.at02.v) {
        arg1->unk_08.at02.v = func_800C2AE8(arg1);
        temp_v0 = arg0->unk_90.as_u16 - 1;
        arg0->unk_90.as_u16 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            arg1->unk_14 = 0;
            func_800C4174(arg0, arg1, arg2);
            return;
        }
        arg1->unk_14 = 0xFFF60000;
        arg0->unk_54 = &D_800CE8CC;
        return;
    }
    func_80095388(arg1);
}
