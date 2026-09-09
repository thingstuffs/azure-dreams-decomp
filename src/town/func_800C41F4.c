#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003AFE0();            /* extern */
M2C_UNK file_load_com();                   /* extern */
M2C_UNK SD_Call();                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK func_80066F78();                     /* extern */
extern s8 D_80080A88;
extern M2C_UNK D_80080E28;
extern M2C_UNK D_800D1D54;

/* Sets the global flag, runs the setup sequence, and processes both global data blocks. */
void func_800C1954(void) {
    D_80080A88 = 1;
    SD_Call(0x7F);
    func_800542BC();
    SD_Call(0x60C);
    func_800542BC();
    func_8003AFE0(0x13, 0xC6);
    func_80066F78(1);
    file_load_com(&D_80080E28);
    file_load_com(&D_800D1D54);
}
