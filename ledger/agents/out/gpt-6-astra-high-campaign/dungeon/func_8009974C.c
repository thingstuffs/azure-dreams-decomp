#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_800B835C();
extern M2C_UNK D_800DD80C;
extern u32 D_800E296C[];

/* Submit a fixed command and set the global activation flag. */
void func_8009EEAC(void) {
    s32 command[2];

    command[0] = 0x01000340;
    command[1] = 0x00200020;
    func_800B835C(&D_800DD80C, command, 1, 0);
    D_800E296C[0] |= 0x00800000;
}
