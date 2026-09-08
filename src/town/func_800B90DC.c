#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"


typedef struct S_800B683C_2 {
    u8 pad_00[0x5C];
    void ** unk_5C;
} S_800B683C_2;   /* ((Rec_func_800B683C_arg0 *)arg0)->unk_98 in func_800B683C */




M2C_UNK func_800B6580();


void func_800B683C(void *arg0) {
    s32 *temp_v0;
    s32 var_a1;

    var_a1 = 0x14;
    do {
        temp_v0 = *(s32 **)((var_a1 * 4) + ((Rec_func_800B683C_arg0 *)arg0)->unk_98);
        var_a1 += 1;
        *temp_v0 = 0;
    } while (var_a1 < 0x16);
    *((S_800B683C_2 *)(((Rec_func_800B683C_arg0 *)arg0)->unk_98))->unk_5C = arg0 + 0x18;
    func_800B6580(*((S_800B683C_2 *)(((Rec_func_800B683C_arg0 *)arg0)->unk_98))->unk_5C, 0);
}
