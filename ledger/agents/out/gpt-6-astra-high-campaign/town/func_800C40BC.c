#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003AFE0();            /* extern */
M2C_UNK func_80041284();                   /* extern */
extern s8 D_80080A88;
extern M2C_UNK D_80080E28;

/* town_movie3_call: Clear the shared flag and invoke the movie setup routines. */
void func_800C181C(void) {
    D_80080A88 = 0;
    func_8003AFE0(0x14, 0x304);
    func_80041284(&D_80080E28);
}
