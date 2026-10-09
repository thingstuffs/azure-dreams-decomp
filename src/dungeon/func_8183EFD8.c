#include "modules/dungeon_ovl_185e800.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"


/* cfail-repair: tf7-phase1-cache-v3 */

/* Brightens and accelerates an effect, spawns particles, then fades it out. */
void func_800247D8(void *effect_arg, DelayMotion *motion, DelaySpriteColor *sprite) {
    s32 color;
    s32 phase;
    s32 z_velocity;
    s32 random;
    s32 count_or_step;
    u8 bright_level;
    u8 fade_level;
    DelaySprite *particle_sprite;
    void *particle;
    DelayOwner *owner;
    DelayParticleTimers *particle_state;
    void *particle_data;

    owner = ((DelayParticle *)effect_arg)->unk_00;
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    phase = *(s16 *)((s8 *)effect_arg + 0x4C);
    ((DelayParticle *)effect_arg)->unk_48 = (u16) (((DelayParticle *)effect_arg)->unk_48 - 1);
    switch (phase) {
    case 0:
        func_800478B8(sprite);
        if ((u8) sprite->unk_0C.at00.v < 0x81U) {
            bright_level = sprite->unk_0C.at02.v + 0x20;
            sprite->unk_0C.at02.v = bright_level;
            sprite->unk_0C.at01.v = bright_level;
            sprite->unk_0C.at00.v = bright_level;
        }
        if ((s16) ((DelayParticle *)effect_arg)->unk_48 <= 0) {
            ((DelayParticle *)effect_arg)->unk_48 = 0x10U;
            ((DelayParticle *)effect_arg)->unk_4C.u = (u16) (((DelayParticle *)effect_arg)->unk_4C.u + 1);
            return;
        }
        return;
    case 1:
        z_velocity = motion->unk_14 + 0x8000;
        motion->unk_14 = z_velocity;
        motion->unk_08 = (s32) (motion->unk_08 + z_velocity);
        count_or_step = 0x14;
        if ((s16) ((DelayParticle *)effect_arg)->unk_48 <= 0) {
            particle_data = func_80024688;
            ((DelayParticle *)effect_arg)->unk_4C.s = (s16) ((u16) ((DelayParticle *)effect_arg)->unk_4C.s + 1);
            do {
                particle = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
                if (particle != NULL) {
                    ((DelayObject *)particle)->unk_10 = particle_data;
                    particle_sprite = ((DelayObject *)particle)->unk_0C;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_00 = (s32) motion->unk_00;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_04 = (s32) motion->unk_04;
                    random = func_80069EF8();
                    {
                        DelayMotionZ *particle_motion = ((DelayObject *)particle)->unk_08;
                        particle_motion->unk_08 = (s32) (motion->unk_08 + ((random & 0x1F) << 0x10));
                        random = func_80069EF8();
                    }
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_0C =
                        (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    random = func_80069EF8();
                    color = 0x800000;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_10 =
                        (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    particle_sprite->unk_1E = 0x1000;
                    particle_sprite->unk_1C = 0x1000;
                    particle_sprite->unk_10 = 0x20;
                    particle_sprite->unk_00 = D_800DECF8;
                    particle_sprite->unk_14 = (u16) (particle_sprite->unk_14 | 0xC);
                    random = (s32) ((SpriteSourceEntry *)D_800DECF8)->unk_04;
                    color |= 0x8080;
                    particle_sprite->unk_04 = 0;
                    particle_sprite->unk_05 = 0;
                    particle_sprite->unk_0C = color;
                    particle_sprite->unk_08 = random;
                    particle_state = particle + 0x20;
                    particle_state->unk_48 = (s16) (func_80069EF8() & 3);
                    particle_state->unk_4A = 0xC;
                    particle_state->unk_4C = 0;
                    ((DelayObject *)particle)->unk_20 = (void *) ((DelayParticle *)effect_arg)->unk_00;
                }
                count_or_step -= 1;
            } while (count_or_step >= 0);
            return;
        }
        return;
    case 2:
        count_or_step = 0x10;
        if (count_or_step >= (s32) sprite->unk_0C.at00.v) {
            sprite->unk_0C.at00u.v = 0;
            ((DelayStatusPrefix *)effect_arg)[-1].unk_00 = (u16) (((DelayStatusPrefix *)effect_arg)[-1].unk_00 | 0x8000);
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        fade_level = sprite->unk_0C.at02.v - 0x10;
        sprite->unk_0C.at02.v = fade_level;
        sprite->unk_0C.at01.v = fade_level;
        sprite->unk_0C.at00.v = fade_level;

        return;
    }
}
