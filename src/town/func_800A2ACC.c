#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8009539C();                      /* extern */
extern M2C_UNK D_8009BC44;

typedef struct S_800A022C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800A022C_0;   /* arg1 in func_800A022C */


typedef struct S_800A022C_2 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A022C_2;   /* arg0 in func_800A022C */

void func_800A022C(S_800A022C_2 *arg0, S_800A022C_0 *arg1, Rec_D_800E3D7C *arg2) {
    arg1->unk_15 = 1;
    arg2->unk_0C.as_s32 = 0;
    arg2->unk_10.at00_s32.v = 0;
    arg2->unk_14.as_s32 = 0xFFF20000;
    func_8009539C(arg2);
    arg0->unk_50 = &D_8009BC44;
}
