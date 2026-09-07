#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033CD8();                   /* extern */
M2C_UNK func_8008F074();  /* extern */
M2C_UNK func_800C2CB0(); /* extern */
M2C_UNK func_800C337C();    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800D5028;


void func_800C3438(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80033CD8(arg0, &D_80045340);
    arg0->unk_8C = 0x40;
    arg0->unk_8E = 0x40;
    func_800C2CB0(arg0, arg2, **arg0->unk_7C.as_pps32, 0);
    func_8008F074(arg0, arg1, &D_800D5028);
    func_800C337C(arg0, arg1, arg2);
}
