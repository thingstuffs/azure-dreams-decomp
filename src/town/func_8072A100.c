#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016100_1 {
    u8 pad_00[0x330];
    s32 (*unk_330)(M2C_UNK);
    s32 (*unk_334)(M2C_UNK);
} S_80016100_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80016100 */




M2C_UNK func_80017684();                         /* extern */
M2C_UNK func_800176FC();                         /* extern */
s32 func_8001777C();                         /* extern */
s32 func_80017918();                                /* extern */
extern Rec_D_80016000 *D_80016000;
extern s16 D_80017A6C;
extern s16 D_80017A74;


void func_80016100(void) {
    s16 *var_s0;
    s16 *var_s1;
    s32 temp_s3;
    s32 var_s2;

    temp_s3 = ((S_80016100_1 *)(D_80016000->unk_20))->unk_330(0);
    var_s2 = 0;
    var_s0 = &D_80017A6C;
    var_s1 = &D_80017A74;
loop_1:
    if (temp_s3 == *var_s1) {
        func_80017684(*var_s0++);
    } else {
        func_800176FC(*var_s0++);
    }
    var_s1 += 1;
    var_s2 += 1;
    if (var_s2 >= 4) {
        if (((S_80016100_1 *)(D_80016000->unk_20))->unk_334(0) != 5) {
            func_80017684(0xBE0);
        } else {
            func_800176FC(0xBE0);
        }
        if ((func_80017918() < 5) || ((func_80017918() >= 5) && (func_8001777C(0x1460) != 0))) {
            func_80017684(0xBE1);
        } else {
            func_800176FC(0xBE1);
        }
        return;
    }
    goto loop_1;
}
