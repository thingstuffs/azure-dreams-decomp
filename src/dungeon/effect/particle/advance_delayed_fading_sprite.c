#include "shared/audio_commands.h"
/* Targeted effect movement, delayed sprite fading, and accelerating particle emission. */
#include "modules/dungeon_ovl_185e800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_185e800_entry)(DelayedTargetEffect *, ObjectPosition *) = run_delayed_sprite_projectile;

/* Move the effect toward its target, emit particles, and apply the delayed target effect. */
void run_delayed_sprite_projectile(DelayedTargetEffect *self, ObjectPosition *motion)
{
    u8 *owner;
    u8 *owner_record;
    u8 *owner_object;
    ObjectNodeHeader *particle;
    DelayParticle *particle_data;
    SpriteFrameState *child_data;
    u8 *animation;
    u8 *particle_texture;
    s16 state;
    s16 timer;
    s32 random_sample;
    u32 state_index;
    s32 particles_left;
    s32 spawn_coord;
    u32 color;
    s16 origin_offset[3];

    owner = self->owner;
    owner_object = owner - 32;
    state = self->state.s;
    owner_record = F(owner, u8 *, -20);
    if (state != 0 && state < 5) {
        particles_left = 16;
        particle_texture = secondary_sprite;
        do {
            particle = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
            if (particle != 0) {
                particle_data = (DelayParticle *)((u8 *)particle + 32);
                child_data = *(u8 * *)&particle->sprite;
                particle->update_callback = advance_delayed_fading_sprite;

                F(F(particle, u8 *, 8), u32, 0) = (u32)motion->x.v +
                    (((rand() & 0x1ff) - 255) << 13);
                F(F(particle, u8 *, 8), u32, 4) = (u32)motion->y.v +
                    (((rand() & 0x1ff) - 255) << 13);
                color = 0xf00000;
                F(F(particle, u8 *, 8), u32, 8) = (u32)motion->z.v +
                    (((rand() & 0x1ff) - 255) << 11);

                F(child_data, u16, 20) |= 0xc;
                F(child_data, u16, 30) = 0x1000;
                F(child_data, u16, 28) = 0x1000;
                F(child_data, u16, 16) = 0x60;
                F(child_data, void *, 0) = particle_texture;
                child_data->source = F(particle_texture, u32, 4);
                color |= 0x8080;
                child_data->unk_04 = 0;
                child_data->frame_ticks = 0;
                F(child_data, u32, 12) = color;
                particle_data->unk_00 = self;
                particle_data->unk_48 = rand() & 3;
                particle_data->fade_step.u = 24;
                particle_data->unk_4C.u = 0;
            }
            particles_left--;
        } while (particles_left >= 0);
    }

    state = self->state.s;
    state_index = state;
    switch (state_index) {
    case 0:
        animation = self->animation;
        if ((F(animation, u16, 0) & 0x80) == 0)
            return;
        if ((F(owner, u8 *, 96) = scan_actor_along_heading( owner, F(owner_record, u8, 36), F(owner_record, u8, 37),
            F(owner, s16, 42), (s16)get_definition_entry_byte_13(8))) == 0) {
            F(owner, u8, 114) = F(owner_record, u8, 36);
            F(owner, u8, 115) = F(owner_record, u8, 37);
        } else {
            child_data = F(F(owner, u8 *, 96), u8 *, -20);
            F(owner, u8, 114) = child_data->tile_x;
            F(owner, u8, 115) = child_data->tile_y;
        }
        if (resolve_record_orientation_or_fallback(F(F(owner_object, u8 *, 12), u8 *, 8),
                          F(owner_object, u8 *, 12), origin_offset, 0) == 0) {
            origin_offset[2] = 0;
            origin_offset[1] = 0;
            origin_offset[0] = 0;
        }
        motion->x.w.i = F(F(owner_object, u8 *, 8), u16, 2) + origin_offset[0];
        motion->y.w.i = F(F(owner_object, u8 *, 8), u16, 6) + origin_offset[1];
        motion->z.w.i = F(F(owner_object, u8 *, 8), u16, 10) + origin_offset[2];
        self->timer.u = 8;
        {
            s32 target_x = F(owner, s8, 114) * 64;
            s32 origin_x = (u16)motion->x.w.i - 32;
            F(motion, u16, 14) = target_x - origin_x;
        }
        motion->velocity_x /= self->timer.s;
        {
            s32 target_y = F(owner, s8, 115) * 64;
            s32 origin_y = (u16)motion->y.w.i - 32;
            F(motion, u16, 18) = target_y - origin_y;
        }
        motion->velocity_y /= self->timer.s;
        F(motion, s16, 22) = sample_terrain_surface_height(
            (u16)motion->x.w.i, (u16)motion->y.w.i,
            (s16)(F(F(owner_object, u8 *, 8), u16, 10) - 48)) -
            ((u16)motion->z.w.i + 176);
        motion->velocity_z /= self->timer.s;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        state = self->state.s + 1;
        self->state.s = state;
        return;

    case 1:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        timer = self->timer.u - 1;
        self->timer.u = timer;
        if (timer > 0)
            return;
        self->timer.u = 12;
        state = self->state.s + 1;
        self->state.s = state;
        return;

    case 2:
        timer = self->timer.u - 1;
        self->timer.u = timer;
        if (timer > 0)
            return;
        if (F(owner, s32, 96) == 0) {
            self->timer.u = 8;
            self->state.u = 5;
            return;
        }
        state = self->state.s + 1;
        self->timer.u = 20;
        self->state.s = state;
        return;

    case 3:
        timer = self->timer.s;
        if (timer % 3 == 0) {
            particle = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
            if (particle != 0) {
                particle->update_callback = brighten_accelerate_and_fade_effect;
                register_node(particle, project_sprite_chain);
                child_data = *(u8 * *)&particle->sprite;

                spawn_coord = rand();
                random_sample = rand();
                spawn_coord &= 0x1ff;
                spawn_coord += random_sample & 0x1ff;
                spawn_coord -= 510;
                spawn_coord <<= 13;
                spawn_coord >>= 1;
                spawn_coord += (u32)motion->x.v;
                F(F(particle, u8 *, 8), u32, 0) = spawn_coord;

                spawn_coord = rand();
                random_sample = rand();
                spawn_coord &= 0x1ff;
                spawn_coord += random_sample & 0x1ff;
                spawn_coord -= 510;
                spawn_coord <<= 13;
                spawn_coord >>= 1;
                spawn_coord += (u32)motion->y.v;
                F(F(particle, u8 *, 8), u32, 4) = spawn_coord;

                F(F(particle, u8 *, 8), u32, 8) = (u32)motion->z.v + 0x100000;
                F(F(particle, u8 *, 8), u32, 20) = 0x40000;

                F(child_data, u16, 30) = 0xa00;
                F(child_data, u16, 28) = 0xa00;
                F(child_data, u16, 16) = 0x20;
                F(child_data, void *, 0) = landing_sprite_entries;
                F(child_data, u16, 20) |= 0xe;
                child_data->source = F(landing_sprite_entries, u32, 4);
                particle_data = (DelayParticle *)((u8 *)particle + 32);
                child_data->unk_04 = 0;
                child_data->frame_ticks = 0;
                F(child_data, u32, 12) = 0;
                particle_data->unk_00 = self;
                particle_data->unk_48 = 8;
                particle_data->unk_4C.u = 0;
            }
        }
        timer = self->timer.u - 1;
        self->timer.u = timer;
        if (timer > 0)
            return;
        state = self->state.s + 1;
        self->timer.u = 13;
        self->state.s = state;
        return;

    case 4:
        timer = self->timer.u - 1;
        self->timer.u = timer;
        if (timer > 0)
            return;
        if (F(owner, s32, 96) != 0) {
            apply_attack_power_and_element_effects(F(owner, void *, 96), 10, self->variant, 2,
                          F(owner, s16, 42), owner, 2);
        }
        self->timer.u = 16;
        state = self->state.s + 1;
        self->state.s = state;
        return;

    case 5:
        timer = self->timer.u - 1;
        self->timer.u = timer;
        if ((self->child_activity.s & 0x8000) != 0) {
            self->child_activity.u &= 0x7fff;
            return;
        }
        if (timer > 0)
            return;
        g_dungeon_status.active_actor = 0;
        F(self, u16, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    }
}
#include "modules/dungeon_ovl_185e800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

/* Waits for the effect delay, then moves and fades the sprite until it expires. */
void advance_delayed_fading_sprite(DelayParticle *effect, DelayPosition *motion, SpriteFrameState *sprite) {
    DelayOwner *owner;
    s16 phase;
    u16 delay;
    u8 shade;
    DelayPosition *position = motion;

    owner = effect->unk_00;
    owner->unk_52 |= 0x8000;
    phase = effect->unk_4C.s;
    switch (phase) {
    case 0:
        delay = effect->unk_48 - 1;
        effect->unk_48 = delay;
        if ((delay << 0x10) <= 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            effect->unk_4C.u += 1;
        }
        break;

    case 1:
        position->f0 += position->fC;
        position->f4 += position->f10;
        advance_sprite_animation_and_textures(sprite);

        if (sprite->flags & 0x6000) {
            sprite->unk_04 = 0;
            sprite->frame_ticks = 0;
        }

        if ((s32)sprite->color.c.r <= effect->fade_step.s) {
            sprite->color.word = 0;
            *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }

        shade = sprite->color.c.g - effect->fade_step.bytes.low;
        sprite->color.c.g = shade;
        sprite->color.c.r = shade;
        sprite->color.c.b -= effect->fade_step.bytes.low * 2;
        break;
    }
}
#include "modules/dungeon_ovl_185e800.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Brightens and accelerates an effect, spawns particles, then fades it out. */
void brighten_accelerate_and_fade_effect(void *effect_arg, DelayMotion *motion, DelaySpriteColor *sprite) {
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
        advance_sprite_animation_and_textures(sprite);
        if ((u8) sprite->color.at00.v < 0x81U) {
            bright_level = sprite->color.at02.v + 0x20;
            sprite->color.at02.v = bright_level;
            sprite->color.at01.v = bright_level;
            sprite->color.at00.v = bright_level;
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
            particle_data = advance_delayed_fading_sprite;
            ((DelayParticle *)effect_arg)->unk_4C.s = (s16) ((u16) ((DelayParticle *)effect_arg)->unk_4C.s + 1);
            do {
                particle = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
                if (particle != NULL) {
                    ((DelayObject *)particle)->unk_10 = particle_data;
                    particle_sprite = ((DelayObject *)particle)->unk_0C;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_00 = (s32) motion->unk_00;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_04 = (s32) motion->unk_04;
                    random = rand();
                    {
                        DelayMotionZ *particle_motion = ((DelayObject *)particle)->unk_08;
                        particle_motion->unk_08 = (s32) (motion->unk_08 + ((random & 0x1F) << 0x10));
                        random = rand();
                    }
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_0C =
                        (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    random = rand();
                    color = 0x800000;
                    ((DelayVelocity *)(((DelayObject *)particle)->unk_08))->unk_10 =
                        (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    particle_sprite->unk_1E = 0x1000;
                    particle_sprite->unk_1C = 0x1000;
                    particle_sprite->unk_10 = 0x20;
                    particle_sprite->unk_00 = fading_sprite_entries;
                    particle_sprite->unk_14 = (u16) (particle_sprite->unk_14 | 0xC);
                    random = (s32) ((SpriteSourceEntry *)fading_sprite_entries)->source;
                    color |= 0x8080;
                    particle_sprite->unk_04 = 0;
                    particle_sprite->unk_05 = 0;
                    particle_sprite->unk_0C = color;
                    particle_sprite->unk_08 = random;
                    particle_state = particle + 0x20;
                    particle_state->unk_48 = (s16) (rand() & 3);
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
        if (count_or_step >= (s32) sprite->color.at00.v) {
            sprite->color.at00u.v = 0;
            ((DelayStatusPrefix *)effect_arg)[-1].unk_00 = (u16) (((DelayStatusPrefix *)effect_arg)[-1].unk_00 | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        fade_level = sprite->color.at02.v - 0x10;
        sprite->color.at02.v = fade_level;
        sprite->color.at01.v = fade_level;
        sprite->color.at00.v = fade_level;

        return;
    }
}
