#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8009A1A4_2 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8009A1A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_8009A1A4 */




M2C_UNK func_80094984();                 /* extern */
extern M2C_UNK D_80099B70;


void func_8009A1A4(Rec_func_80094268_arg0 *arg0) {
    func_80094984(((S_8009A1A4_2 *)(((Rec_func_80094268_arg0 *)arg0)->unk_44))->unk_20, arg0);
    arg0->unk_04.as_pm = &D_80099B70;
}
