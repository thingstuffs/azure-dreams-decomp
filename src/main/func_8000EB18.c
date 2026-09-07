#include "common.h"
#include "m2c_compat.h"

M2C_UNK strcat();              /* extern */
M2C_UNK strcpy();                    /* extern */
extern u8 D_80027F18;
extern M2C_UNK D_80027F20;
extern M2C_UNK D_80027F30;
extern s32 D_800287CC;

void func_80021B18(s32 arg0, s32 arg1) {
    s32 *var_v0;

    var_v0 = &D_80027F18;
    if (D_800287CC != 0) {
        var_v0 = &D_80027F18 + 4;
    }
    strcpy(arg0, *var_v0);
    strcat(arg0, &D_80027F20);
    strcat(arg0, ((s32 *) &D_80027F30)[arg1]);
}
