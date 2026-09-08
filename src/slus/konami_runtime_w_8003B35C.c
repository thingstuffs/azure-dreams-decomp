#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003AE28(); /* extern */
M2C_UNK func_8003AF58();        /* extern */
M2C_UNK func_80041284();                   /* extern */
M2C_UNK func_800418B4();                            /* extern */
M2C_UNK func_8004B834();                            /* extern */
extern M2C_UNK D_8006AE94;
extern M2C_UNK D_800717D0;
extern M2C_UNK D_80080ED0;
extern M2C_UNK D_80080ED8;

/* Append the runtime entry, copy two VRAM strips, and run the associated updates. */
void func_8003B35C(void) {
    func_8003AF58(&D_800717D0, &D_8006AE94);
    func_8003AE28(0, 0x1F2, 0x10, 1, 0x90, 0x1F2);
    func_8003AE28(0x80, 0x1F2, 0x10, 1, 0, 0x1F2);
    func_80041284(&D_80080ED0);
    func_80041284(&D_80080ED8);
    func_8004B834();
    func_800418B4();
}
