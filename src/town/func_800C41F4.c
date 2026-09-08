#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003AFE0();            /* extern */
M2C_UNK func_80041284();                   /* extern */
M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK func_80066F78();                     /* extern */
extern s8 D_80080A88;
extern M2C_UNK D_80080E28;
extern M2C_UNK D_800D1D54;

/* Sets the global flag, runs the setup sequence, and processes both global data blocks. */
void func_800C1954(void) {
    D_80080A88 = 1;
    func_80053DA8(0x7F);
    func_800542BC();
    func_80053DA8(0x60C);
    func_800542BC();
    func_8003AFE0(0x13, 0xC6);
    func_80066F78(1);
    func_80041284(&D_80080E28);
    func_80041284(&D_800D1D54);
}
