#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_80099CE0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80099CE0_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_80099CE0 */




M2C_UNK func_80094984();                 /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80099790;


void func_80099CE0(Rec_func_80094268_arg0 *arg0) {
    func_80094984(((S_80099CE0_2 *)(((Rec_func_80094268_arg0 *)arg0)->unk_44))->unk_08, arg0);
    *((arg0->unk_40 * 8) + &D_80082660) = 0;
    arg0->unk_04.as_pm = &D_80099790;
    arg0->unk_0A.as_s16 = 0x20;
}
