#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017BA0();                    /* extern */
extern s32 D_80018E44;
extern s32 D_80018E48;

/* Pass the two global values to func_80017BA0. */
void func_804B78EC(void) {
    func_80017BA0(D_80018E44, D_80018E48);
}
