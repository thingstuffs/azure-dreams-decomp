#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                 /* extern */
extern M2C_UNK D_800A73E0;


typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A7360_1;   /* arg0 in func_800A7360 */

void func_800A7360(S_800A7360_1 *arg0, Rec_D_800E3D7C *arg1) {
    s32 temp_a1;

    arg1->unk_00.at00_s32.v = (s32) (arg1->unk_00.at00_s32.v + arg1->unk_0C.as_s32);
    arg1->unk_04.at00_s32.v = (s32) (arg1->unk_04.at00_s32.v + arg1->unk_10.at00_s32.v);
    arg1->unk_08.at00_s32.v = (s32) (arg1->unk_08.at00_s32.v + (arg1->unk_14.as_s32));
    func_80095388(arg1, (arg1->unk_14.as_s32));
    if (arg1->unk_14.as_s32 >= 0) {
        arg0->unk_50 = &D_800A73E0;
    }
}
