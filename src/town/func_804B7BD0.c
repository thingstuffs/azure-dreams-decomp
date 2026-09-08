#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001611C();                /* extern */
M2C_UNK func_80017EB0();                /* extern */
M2C_UNK func_800188CC();                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;

/* Conditionally processes 0x50C, then forwards the inputs to both shared routines. */
void func_804B7BD0(s32 forwardedValue, M2C_UNK forwardedData) {
    if (func_8001894C(0x50C) != 0) {
        if (func_8001894C(D_80018AEA) == 0) {
            func_800188CC(0x50C);
        }
    }
    func_8001611C(forwardedValue, forwardedData);
    func_80017EB0(forwardedValue, forwardedData);
}
