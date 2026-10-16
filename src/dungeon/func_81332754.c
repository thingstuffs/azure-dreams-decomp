#include "common.h"
#include "shared/object_flags.h"


extern s32 rand(void);
extern void func_800A56E0(s32);
extern void dungeonCreateShortLivedChildParticle(void *, s32, s32, s32, s32, s32, s32);
extern void dungeonCreateShortLivedColoredParticle(void *, s32, s32, s32, s32, s32, s32);
extern void dungeonCreateBallisticLandingParticle(void *, s32, s32, s32, s32, s32, s32);
extern void dungeonCreateJitteredLandingSpark(void *);
extern void dungeonScatterLandingSparksOnGrid(void *);
extern void dungeonCreateShortLivedRedSpark(void *, s32, s32, s32, s32, s32, s32);

/* Advances a timed particle effect, emitting particles and sounds until completion. */
void dungeonUpdateStagedParticleEmitter(void *effect_data)
{
    u8 *effect = effect_data;
    s32 particle_index;
    s32 state;


    state = *(s16 *)(effect + 0x12);
    switch (state) {
    case 0:
        *(u16 *)(effect + 0x12) += 1;
        *(s32 *)(effect + 0x64) = (s32)0xFFE80000;

    case 1:
    {
        u16 frame;
        s32 next_frame;
        s32 within_duration;

        for (particle_index = 0; particle_index < 3; particle_index++) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateShortLivedChildParticle(effect - 0x20, 0, 0x2040F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }

        for (particle_index = 0; particle_index < 5; particle_index++) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateShortLivedColoredParticle(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }

        for (particle_index = 0; particle_index < 4; particle_index++) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateShortLivedRedSpark(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }

        *(s32 *)(effect + 0x64) += 0xA000;
        {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateBallisticLandingParticle(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          ~((~(rand() & 0xF)) & 0x3F),
                          *(s32 *)(effect + 0x64));
        }

        if ((*(u16 *)(effect + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        frame = *(u16 *)(effect + 0x18);
        next_frame = frame + 1;
        within_duration = (s16)frame < 0x14;
        *(u16 *)(effect + 0x18) = next_frame;
        if (within_duration) {
            return;
        }
        *(u16 *)(effect + 0x18) = 0;
        *(u16 *)(effect + 0x12) += 1;
        return;
    }

    case 2:
    {
        u16 frame;
        s32 next_frame;
        s32 within_duration;

        for (particle_index = 0; particle_index < 2; particle_index++) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateShortLivedColoredParticle(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }
        for (particle_index = 0; particle_index < 2; particle_index++) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateShortLivedRedSpark(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }
        *(s32 *)(effect + 0x64) += 0x2000;
        if ((u16)(*(u16 *)(effect + 0x18) - 0xF) < 0xB) {
            dungeonScatterLandingSparksOnGrid(effect - 0x20);
        }
        if (*(s16 *)(effect + 0x18) == 0xF ||
            *(s16 *)(effect + 0x18) == 0x14 ||
            *(s16 *)(effect + 0x18) == 0x19) {
            dungeonCreateJitteredLandingSpark(effect - 0x20);
        }
        if (*(s16 *)(effect + 0x18) < 0x1F &&
            (*(u16 *)(effect + 0x18) & 1) == 0) {
            s32 jitter_x;
            s32 jitter_y;
            jitter_x = (s16)((rand() & 0xF) - 8);
            jitter_y = (s16)((rand() & 0xF) - 8);
            dungeonCreateBallisticLandingParticle(effect - 0x20, 0, 0x2020F0, jitter_x, jitter_y,
                          (rand() & 0xF) | -0x40,
                          *(s32 *)(effect + 0x64));
        }
        if ((*(u16 *)(effect + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        frame = *(u16 *)(effect + 0x18);
        next_frame = frame + 1;
        within_duration = (s16)frame < 0x28;
        *(u16 *)(effect + 0x18) = next_frame;
        if (within_duration) {
            return;
        }
        *(u16 *)(effect + 0x18) = 0;
        *(u16 *)(effect + 0x12) += 1;
        return;
    }

    case 3:
    case 4:
    {
        u16 frame;
        s32 next_frame;
        s32 within_duration;

        frame = *(u16 *)(effect + 0x18);
        next_frame = frame + 1;
        within_duration = (s16)frame < 0xA;
        *(u16 *)(effect + 0x18) = next_frame;
        if (!within_duration) {
            *(u16 *)(effect - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }

        return;
    default:
        return;
    }
}
