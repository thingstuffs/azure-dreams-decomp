#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/effect/motion.h"

s32 play_sound_if_enabled();                     /* extern */

/* Spawn four directed particles and ten scattered particles at the given position. */
void spawn_directed_and_scattered_particles(s32 x, s32 y, s32 z) {
    s32 particles_left;

    spawn_variant_effect_with_random_motion(x, y, z, 1);
    spawn_variant_effect_with_random_motion(x, y, z, 2);
    spawn_variant_effect_with_random_motion(x, y, z, 3);
    spawn_variant_effect_with_random_motion(x, y, z, 4);
    particles_left = 0xA;
    do {
        spawn_variant_effect_with_random_motion(x, y, z, 0);
        particles_left -= 1;
    } while (particles_left > 0);
    play_sound_if_enabled(0x513);
}
