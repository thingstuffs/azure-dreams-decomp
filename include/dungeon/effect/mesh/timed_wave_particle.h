#ifndef DUNGEON_EFFECT_MESH_TIMED_WAVE_PARTICLE_H
#define DUNGEON_EFFECT_MESH_TIMED_WAVE_PARTICLE_H

#include "common.h"

/* Body of the node that installs update_timed. The creator stores target and
 * source at offsets 0x2C and 0x30 and clears the 0x60-byte intensity field. */
struct ProjectileSelf;

typedef struct TimedWaveParticleBody {
    s16 mode;
    s16 frame;
    u8 pad_04[0x28];
    void *target;
    struct ProjectileSelf *source;
    u8 pad_34[0x4];
    u8 levels[0x60];
    u16 unk_98;
    u16 unk_9A;
} TimedWaveParticleBody;

#endif
