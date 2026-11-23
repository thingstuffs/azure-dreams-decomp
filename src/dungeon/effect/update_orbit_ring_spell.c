#include "common.h"
#include "dungeon/effect/spell_effect.h"
#include "dungeon/effect/sprite/create_coordinate_sprite_effect.h"
#include "dungeon/level.h"
#include "dungeon/level/tile_flags.h"
#include "dungeon/system.h"
#include "engine/scene.h"
#include "sdk/abs.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity_height_offsets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "shared/sprite_frame_state.h"

/* This spell's view of the node's ObjectPosition (same 0x18 bytes; fold it into that record once the velocity
 * members settle). The three steps are added as whole units when the spell flies to a target, and as 16.16 words
 * when it flies along the caster's facing. */
typedef struct SpellMotion {
    Fixed1616 x;
    Fixed1616 y;
    Fixed1616 z;
    Fixed1616 step_x;
    Fixed1616 step_y;
    Fixed1616 step_z;
} SpellMotion;

/* Body of the spell node: a sprite that flies to the target (or along the facing) and then opens a ring of ten
 * orbiting sprites around it. */
typedef struct OrbitRingSpell {
    SpellEffectHeader effect;
    s16 reserved_0c;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 busy;
    s16 spin;
    s16 orbit;
    s16 reserved_1a;
    ObjectNodeHeader *trail;
    ObjectNodeHeader *ring;
    ObjectNodeHeader *orbs[10];
} OrbitRingSpell;

/* The object completion word, declared as a plain word: the removal stores below are scheduled as retail has
 * them only against a scalar. */
/* BYTES: The scalar declaration keeps the completion-word store in retail order. */
extern s32 D_800814A0;


void update_orbit_ring_spell(OrbitRingSpell *spell, SpellMotion *motion, SpriteFrameState *sprite) {
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
    spell->spin = (spell->spin + 64) % 4096;
    spell->orbit = (spell->orbit + 128) % 4096;
    switch (spell->effect.phase) {
    case 0:
        spell->timer = 0;
        spell->effect.phase++;
        spell->direction = ((u16)caster->facing >> 9) & 7;
        spell->ring = 0;
        for (i = 0; i < 10; i++) {
            spell->orbs[i] = 0;
        }
        sprite->color.word = 0x808080;
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
        if (!(*spell->effect.context & 0x80)) {
            break;
        }
        if (caster->target) {
            target_position = NODE_HEADER(caster->target)->position;
            delta[0] = abs(target_position->x.w.i - motion->x.w.i);
            delta[1] = abs(target_position->y.w.i - motion->y.w.i);
            {
                ActorRecord *target = caster->target;
                delta[2] = abs(target_position->z.w.i - (entity_height_offsets[target->species] >> 1) - motion->z.w.i);
            }
            spell->duration = delta[0];
            for (i = 1; i < 3; i++) {
                if (delta[i] > spell->duration) {
                    spell->duration = delta[i];
                }
            }
            spell->duration >>= 4;
            if (spell->duration == 0) {
                spell->duration = 1;
            }
            motion->step_x.w.i = (target_position->x.w.i - motion->x.w.i) / spell->duration;
            motion->step_y.w.i = (target_position->y.w.i - motion->y.w.i) / spell->duration;
            {
                ActorRecord *target = caster->target;
                motion->step_z.w.i = (target_position->z.w.i - (entity_height_offsets[target->species] >> 1) -
                                      motion->z.w.i) / spell->duration;
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
            target_position->z.w.i = motion->z.w.i;
            delta[0] = abs(target_position->x.w.i - motion->x.w.i);
            delta[1] = abs(target_position->y.w.i - motion->y.w.i);
            delta[2] = abs(target_position->z.w.i - motion->z.w.i);
            spell->duration = delta[0];
            for (i = 1; i < 3; i++) {
                if (delta[i] > spell->duration) {
                    spell->duration = delta[i];
                }
            }
            spell->duration >>= 4;
            if (spell->duration == 0) {
                spell->duration = 1;
            }
            motion->step_x.v = (target_position->x.v - motion->x.v) / spell->duration;
            motion->step_y.v = (target_position->y.v - motion->y.v) / spell->duration;
            motion->step_z.v = (target_position->z.v - motion->z.v) / spell->duration;
            spell->effect.phase = 7;
        }
        spell->trail = create_coordinate_sprite_effect(spell, (ObjectPosition *)motion);
        spell->timer = 0;
        break;
    case 2:
        motion->x.w.i += motion->step_x.w.i;
        motion->y.w.i += motion->step_y.w.i;
        motion->z.w.i += motion->step_z.w.i;
        if (spell->trail) {
            *spell->trail->position = *(ObjectPosition *)motion;
        }
        if (spell->timer >= spell->duration) {
            spell->timer = 0;
            spell->spin = 0;
            spell->orbit = 0x800;
            spell->effect.phase++;
            target_position = NODE_HEADER(caster->target)->position;
            motion->x.w.i = target_position->x.w.i;
            motion->y.w.i = target_position->y.w.i;
            {
                ActorRecord *target = caster->target;
                motion->z.w.i = target_position->z.w.i - (entity_height_offsets[target->species] >> 1);
            }
            spell->ring = create_randomly_rotated_effect(spell, (ObjectPosition *)motion);
            for (i = 9; i >= 0; i--) {
                spell->orbs[i] = create_random_radial_effect(spell, (ObjectPosition *)motion, i * -25, i);
            }
            play_sound_if_enabled(0x300);
        }
        break;
    case 3:
        spell->ring->sprite->color.word += 0x040404;
        spell->ring->sprite->scale_x = spell->ring->sprite->scale_y += 0x80;
        if (spell->trail && spell->timer == 1) {
            spell->trail->flags |= NODE_REMOVE;
            D_800814A0 |= OBJECT_REMOVE_PENDING;
            spell->trail = 0;
        }
    case 4:
        if (spell->timer >= 32) {
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 5:
        spell->ring->sprite->color.word -= 0x040404;
        spell->ring->sprite->scale_x -= 0x80;
        spell->ring->sprite->scale_y -= 0x80;
        if (spell->timer >= 32) {
            apply_small_random_value_gain(caster->target, spell->effect.variant, caster);
            spell->timer = 0;
            spell->effect.phase++;
            if (spell->ring) {
                spell->ring->flags |= NODE_REMOVE;
                D_800814A0 |= OBJECT_REMOVE_PENDING;
                spell->ring = 0;
            }
            for (i = 9; i >= 0; i--) {
                if (spell->orbs[i]) {
                    spell->orbs[i]->flags |= NODE_REMOVE;
                    D_800814A0 |= OBJECT_REMOVE_PENDING;
                    spell->orbs[i] = 0;
                }
            }
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
        motion->x.w.i += motion->step_x.w.i;
        motion->y.w.i += motion->step_y.w.i;
        motion->z.w.i += motion->step_z.w.i;
        if (spell->trail) {
            *spell->trail->position = *(ObjectPosition *)motion;
        }
        if (spell->timer > spell->duration) {
            if (spell->trail) {
                spell->trail->flags |= NODE_REMOVE;
                D_800814A0 |= OBJECT_REMOVE_PENDING;
                spell->trail = 0;
            }
            spell->effect.phase = 6;
            spell->timer = 0;
        }
        break;
    }
    spell->busy = 0;
}
