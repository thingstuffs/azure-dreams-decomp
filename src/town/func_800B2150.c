/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"


typedef struct S_800AF8B0_2 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
} S_800AF8B0_2;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_00 in func_800AF8B0 */




M2C_UNK func_800B05DC(); /* extern */


void func_800AF8B0(Rec_func_800AF254_arg1 *arg0) {
    M2C_UNK var_a2;
    s32 var_a3;

    var_a3 = ((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_00))->unk_18 % 10;
    var_a2 = -0xB4;
    if ((var_a3 / 5) != 0) {
        var_a2 = 0x28;
    }
    arg0->unk_10 = 0;
    func_800B05DC(arg0->unk_18, ((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_00))->unk_18, var_a2, ((var_a3 % 5) * 0x18) - 0x80, ((s32 *)((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_00))->unk_20)[((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)arg0)->unk_00))->unk_18]);
}
