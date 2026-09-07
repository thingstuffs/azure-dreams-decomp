#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B7D74(); /* extern */

/* Spawn four directed particles and ten scattered particles at the given position. */
void func_800B8024(s32 x, M2C_UNK y, M2C_UNK z) {
    s32 particles_left;

    func_800B7D74(x, y, z, 1);
    func_800B7D74(x, y, z, 2);
    func_800B7D74(x, y, z, 3);
    func_800B7D74(x, y, z, 4);
    particles_left = 0xA;
    do {
        func_800B7D74(x, y, z, 0);
        particles_left -= 1;
    } while (particles_left > 0);
    func_800A56E0(0x513);
}
