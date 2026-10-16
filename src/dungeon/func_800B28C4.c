#include "common.h"
#include "m2c_compat.h"

s32 func_800A56E0();                     /* extern */
void dungeonSpawnVariantEffectWithRandomMotion(); /* extern */

/* Spawn four directed particles and ten scattered particles at the given position. */
void dungeonSpawnDirectedAndScatteredParticles(s32 x, M2C_UNK y, M2C_UNK z) {
    s32 particles_left;

    dungeonSpawnVariantEffectWithRandomMotion(x, y, z, 1);
    dungeonSpawnVariantEffectWithRandomMotion(x, y, z, 2);
    dungeonSpawnVariantEffectWithRandomMotion(x, y, z, 3);
    dungeonSpawnVariantEffectWithRandomMotion(x, y, z, 4);
    particles_left = 0xA;
    do {
        dungeonSpawnVariantEffectWithRandomMotion(x, y, z, 0);
        particles_left -= 1;
    } while (particles_left > 0);
    func_800A56E0(0x513);
}
