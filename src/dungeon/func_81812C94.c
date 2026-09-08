#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027AD0_arg0.h"

M2C_UNK func_80027AD0();            /* extern */
M2C_UNK func_80027B44();               /* extern */
M2C_UNK func_80027B6C();               /* extern */
M2C_UNK func_80027BBC();                    /* extern */
M2C_UNK func_8004CB2C();                      /* extern */


void func_80027C94(void *arg0) {
    func_80027B44(((Rec_func_80027AD0_arg0 *)arg0)->unk_88, ((Rec_func_80027AD0_arg0 *)arg0)->unk_00, ((Rec_func_80027AD0_arg0 *)arg0)->unk_04);
    func_80027AD0(arg0, ((Rec_func_80027AD0_arg0 *)arg0)->unk_00, ((Rec_func_80027AD0_arg0 *)arg0)->unk_04);
    func_80027B6C(((Rec_func_80027AD0_arg0 *)arg0)->unk_88, ((Rec_func_80027AD0_arg0 *)arg0)->unk_00, ((Rec_func_80027AD0_arg0 *)arg0)->unk_04);
    func_80027BBC(((Rec_func_80027AD0_arg0 *)arg0)->unk_88, ((Rec_func_80027AD0_arg0 *)arg0)->unk_40);
    func_8004CB2C(arg0 + 0x2C);
}
