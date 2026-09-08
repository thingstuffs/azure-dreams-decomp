#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"



M2C_UNK func_80016098();                            /* extern */
M2C_UNK func_80016510();                    /* extern */
M2C_UNK func_800168B4();   /* extern */
extern Rec_D_80016000 *D_80016000;
extern s16 D_800160B0;
extern s16 D_800160B2;
extern s32 D_80016E40;
extern M2C_UNK D_80016E48;
extern M2C_UNK D_80016F88;
extern M2C_UNK D_80016FC8;
extern M2C_UNK D_8001700C;

/* Initialize shared state and attach its data pointers. */
void func_80016C34(void) {
    func_80016510(D_800160B0, D_800160B2);
    func_80016098();
    func_800168B4(D_80016E40, &D_80016E48, &D_80016F88);
    D_80016000->unk_34 = &D_80016FC8;
    D_80016000->unk_28 = &D_80016E48;
    D_80016000->unk_2C = &D_8001700C;
}
