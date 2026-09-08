#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB4C();          /* extern */
M2C_UNK func_8009D3B0();                            /* extern */
extern M2C_UNK D_800E50A8;

/* Process the 0x200-byte global buffer and run the follow-up routine. */
void func_8009D380(void) {
    func_8003DB4C(&D_800E50A8, 0x200);
    func_8009D3B0();
}
