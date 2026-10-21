#ifndef SLUS_SOUND_REVERB_H
#define SLUS_SOUND_REVERB_H

#include "slus/sound_dma_lifecycle.h"

typedef struct SoundReverbParameters {
    s32 mask;
    u16 p04;
    u16 p06;
    u16 p08;
    u16 p0A;
    u16 p0C;
    u16 p0E;
    u16 p10;
    s16 p12;
    u16 p14;
    u16 p16;
    s16 p18;
    s16 p1A;
    s16 p1C;
    u16 p1E;
    u16 p20;
    u16 p22;
    s16 p24;
    u16 p26;
    u16 p28;
    u16 p2A;
    u16 p2C;
    u16 p2E;
    u16 p30;
    u16 p32;
    u16 p34;
    u16 p36;
    s16 p38;
    s16 p3A;
    u16 p3C;
    u16 p3E;
    u16 p40;
    u16 p42;
} SoundReverbParameters;

void write_spu_reverb_parameters(SoundReverbParameters *source);

#endif
