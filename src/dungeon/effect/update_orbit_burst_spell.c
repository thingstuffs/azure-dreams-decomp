#include "common.h"
#include "dungeon/effect/spell_effect.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/orbit_ring_spell.h"
#include "shared/object_flags.h"
#include "dungeon/effect/screen.h"
#include "dungeon/level.h"
#include "dungeon/level/tile_flags.h"
#include "dungeon/system.h"
#include "engine/node/registration.h"
#include "engine/scene.h"
#include "sdk/abs.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "shared/sprite_frame_state.h"


/* Body of the spell node: a sprite that flies to the target (or along the facing), then a core sprite with
 * thirty-two orbiting sprites at the target, then the hit. */
typedef struct OrbitBurstSpell {
    SpellEffectHeader effect;
    u16 flags;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 age;
    s16 busy;
    ObjectNodeHeader *core;
    ObjectNodeHeader *orbs[32];
} OrbitBurstSpell;

/* The object completion word, declared as a plain word: the removal stores below are scheduled as retail has
 * them only against a scalar. */
/* BYTES: The scalar declaration keeps the completion-word store in retail order. */
extern s32 D_800814A0;


void update_orbit_burst_spell(OrbitBurstSpell *spell, SpellMotion *motion, SpriteFrameState *sprite) {
    ActorRecord *caster = spell->effect.caster;
    ObjectPosition destination;
    s16 delta[3];
    ObjectNodeHeader *caster_node;
    ObjectPosition *target_position;
    int i;
    u16 tile_x, tile_y;
    u16 end_tile_x, end_tile_y;
    s16 grid_x, grid_y;
    u16 height;
    int end_x, end_y;

    spell->timer++;
    spell->age++;
    switch (spell->effect.phase) {
    case 0:
        spell->timer = 0;
        spell->effect.phase++;
        spell->direction = ((u16)caster->facing >> 9) & 7;
        spell->age = 0;
        spell->busy = 0;
        spell->core = 0;
        for (i = 0; i < 32; i++) {
            spell->orbs[i] = 0;
        }
        sprite->color.word = 0x808080;
        /* fall through */
    case 1:
        caster_node = NODE_HEADER(caster);
        if (!resolve_record_orientation_or_fallback(caster_node->sprite->source, caster_node->sprite, (SVECTOR *)delta, 0) &&
            !(caster_node->sprite->flags & 0x8000)) {
            break;
        }
        {
            ObjectPosition *source = caster_node->position;

            motion->x.w.i = source->x.w.i;
            motion->y.w.i = source->y.w.i;
            motion->z.w.i = source->z.w.i;
        }
        if (!(caster_node->sprite->flags & 0x8000)) {
            motion->x.w.i += delta[0];
            motion->y.w.i += delta[1];
            motion->z.w.i += delta[2];
        } else {
            motion->z.w.i -= 64;
        }
        if (!(spell->flags & 1)) {
            register_node(NODE_HEADER(spell), dispatch_effect_rendering);
            spell->flags |= 1;
        }
        if (!(*spell->effect.context & 0x80)) {
            break;
        }
        if (caster->target) {
            target_position = NODE_HEADER(caster->target)->position;
            delta[0] = abs(target_position->x.w.i - motion->x.w.i);
            delta[1] = abs(target_position->y.w.i - motion->y.w.i);
            {
                ActorRecord *target = caster->target;
                delta[2] = abs(target->ground_height - motion->z.w.i);
            }
            spell->duration = delta[0];
            for (i = 1; i < 3; i++) {
                if (delta[i] > spell->duration) {
                    spell->duration = delta[i];
                }
            }
            spell->duration >>= 5;
            if (spell->duration == 0) {
                spell->duration = 1;
            }
            motion->step_x.w.i = (target_position->x.w.i - motion->x.w.i) / spell->duration;
            motion->step_y.w.i = (target_position->y.w.i - motion->y.w.i) / spell->duration;
            {
                ActorRecord *target = caster->target;
                motion->step_z.w.i = (target->ground_height - motion->z.w.i) / spell->duration;
            }
            spell->effect.phase++;
        } else {
            i = 0;
            tile_x = caster_node->sprite->tile_x;
            tile_y = caster_node->sprite->tile_y;
            end_tile_x = tile_x;
            end_tile_y = tile_y;
            while (i < 8) {
                grid_x = tile_x;
                grid_y = tile_y;
                if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0, caster->ground_height,
                                                   (s16)(spell->direction << 9))) {
                    break;
                }
                height = sample_terrain_surface_height((((grid_x + dir_step_x[spell->direction]) << 6) + 32) & 0xFFE0,
                                                       (((grid_y + dir_step_y[spell->direction]) << 6) + 32) & 0xFFE0,
                                                       caster->ground_height - 32);
                if ((s16)height > 512 || (s16)(height - caster->ground_height) < -63) {
                    break;
                }
                i++;
                tile_x += dir_step_x[spell->direction];
                tile_y += dir_step_y[spell->direction];
                end_tile_y = tile_y;
                end_tile_x = tile_x;
            }
            target_position = &destination;
            end_x = ((end_tile_x << 16) >> 10) + ((dir_step_x[spell->direction] + 1) << 5);
            target_position->x.w.i = end_x;
            end_y = ((end_tile_y << 16) >> 10) + ((dir_step_y[spell->direction] + 1) << 5);
            target_position->y.w.i = end_y;
            target_position->z.w.i = motion->z.w.i + 32;
            delta[0] = abs(target_position->x.w.i - motion->x.w.i);
            delta[1] = abs(target_position->y.w.i - motion->y.w.i);
            delta[2] = abs(target_position->z.w.i - motion->z.w.i);
            spell->duration = delta[0];
            for (i = 1; i < 3; i++) {
                if (delta[i] > spell->duration) {
                    spell->duration = delta[i];
                }
            }
            spell->duration >>= 5;
            if (spell->duration == 0) {
                spell->duration = 1;
            }
            motion->step_x.v = (target_position->x.v - motion->x.v) / spell->duration;
            motion->step_y.v = (target_position->y.v - motion->y.v) / spell->duration;
            motion->step_z.v = (target_position->z.v - motion->z.v) / spell->duration;
            spell->effect.phase = 7;
        }
        spell->timer = 0;
        spell->age = 0;
        break;
    case 2:
        motion->x.w.i += motion->step_x.w.i;
        motion->y.w.i += motion->step_y.w.i;
        motion->z.w.i += motion->step_z.w.i;
        if (spell->timer >= spell->duration) {
            spell->timer = 0;
            spell->effect.phase++;
            target_position = NODE_HEADER(caster->target)->position;
            motion->x.w.i = target_position->x.w.i;
            motion->y.w.i = target_position->y.w.i;
            {
                ActorRecord *target = caster->target;
                motion->z.w.i = target->ground_height;
            }
            spell->core = create_effect_sprite_at((MovingPosition *)motion);
            play_sound_if_enabled(0x300);
        } else {
            allocate_effect_at_coordinates((LinkedSpriteCounter *)spell, (ObjectPosition *)motion);
        }
        break;
    case 3:
        if (spell->timer >= 16) {
            for (i = 31; i >= 0; i--) {
                spell->orbs[i] = create_orbit_sprite_at_index((MovingPosition *)motion, i);
            }
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 4:
        if (!(spell->timer & 3)) {
            spawn_sprite_at_random_radial_offset((MovingPosition *)motion);
        }
        if (spell->timer >= 32) {
            spell->timer = 0;
            spell->effect.phase++;
            if (spell->core) {
                spell->core->flags |= NODE_REMOVE;
                D_800814A0 |= OBJECT_REMOVE_PENDING;
                spell->core = 0;
            }
            for (i = 31; i >= 0; i--) {
                if (spell->orbs[i]) {
                    spell->orbs[i]->flags |= NODE_REMOVE;
                    D_800814A0 |= OBJECT_REMOVE_PENDING;
                    spell->orbs[i] = 0;
                }
            }
        }
        break;
    case 5:
        if (spell->timer >= 16) {
            apply_attack_power_and_element_effects(caster->target, 19, spell->effect.variant, 1, spell->direction << 9,
                                                   caster, 1);
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 6:
        if (!spell->busy) {
            g_dungeon_status.active_actor = 0;
            /* BYTES: The direct halfword access keeps the two flag stores in retail order. */
            *((u16 *)spell - 1) |= NODE_REMOVE;
            D_800814A0 |= OBJECT_REMOVE_PENDING;
        }
        break;
    case 7:
        if (spell->timer < 5 && spell->timer <= spell->duration) {
            motion->x.w.i += motion->step_x.w.i * spell->timer;
            motion->y.w.i += motion->step_y.w.i * spell->timer;
            motion->z.w.i += motion->step_z.w.i * spell->timer;
            create_random_rotation_effect_sprite(spell, (MovingPosition *)motion);
            motion->x.w.i -= motion->step_x.w.i * spell->timer;
            motion->y.w.i -= motion->step_y.w.i * spell->timer;
            motion->z.w.i -= motion->step_z.w.i * spell->timer;
        } else if (spell->timer <= spell->duration) {
            if (spell->duration < 4) {
                motion->x.w.i += motion->step_x.w.i * (spell->duration + 1);
                motion->y.w.i += motion->step_y.w.i * (spell->duration + 1);
                motion->z.w.i += motion->step_z.w.i * (spell->duration + 1);
                create_random_rotation_effect_sprite(spell, (MovingPosition *)motion);
                motion->x.w.i -= motion->step_x.w.i * spell->duration;
                motion->y.w.i -= motion->step_y.w.i * spell->duration;
                motion->z.w.i -= motion->step_z.w.i * spell->duration;
            } else {
                motion->x.w.i += motion->step_x.w.i * 5;
                motion->y.w.i += motion->step_y.w.i * 5;
                motion->z.w.i += motion->step_z.w.i * 5;
                create_random_rotation_effect_sprite(spell, (MovingPosition *)motion);
                motion->x.w.i -= motion->step_x.w.i * 4;
                motion->y.w.i -= motion->step_y.w.i * 4;
                motion->z.w.i -= motion->step_z.w.i * 4;
            }
        } else if (spell->timer <= spell->duration + 4 && spell->timer <= spell->duration * 2) {
            motion->x.w.i += motion->step_x.w.i;
            motion->y.w.i += motion->step_y.w.i;
            motion->z.w.i += motion->step_z.w.i;
        } else {
            spell->effect.phase = 6;
            spell->timer = 0;
        }
        break;
    }
    spell->busy = 0;
}
