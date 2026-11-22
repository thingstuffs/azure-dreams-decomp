#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/spell_resource_ids_data.h"
#include "dungeon/effect/particle/get_a_random_sign_either.h"
#include "dungeon/effect/rectangle_effect_updated_data.h"
#include "dungeon/effect/screen.h"
#include "dungeon/effect/screen/menu.h"
#include "dungeon/effect/spell_effect.h"
#include "dungeon/system.h"
#include "dungeon/system/random.h"
#include "engine/graphics.h"
#include "engine/node/registration.h"
#include "sdk/abs.h"
#include "sdk/rand.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/entity_height_offsets.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "shared/slus_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_part_command.h"

/* Body of the spell node: a pulsing sprite that flies from the caster to the caster's target. */
typedef struct PulsingOrbSpell {
    SpellEffectHeader effect;
    u8 reserved_0c[0x6C];
    s16 target_height;
    u8 flags;
    s8 flight_ticks;
    u8 reserved_7c[2];
    s16 direction;
    u8 reserved_80[2];
    s16 timer;
    u8 reserved_84[4];
    s16 initial_ticks;
    s16 ticks_squared;
    u8 reserved_8c[4];
    s16 shrinking;
    s16 pulse_ticks;
    s16 pulse_period;
    u16 pulse_step;
    u8 reserved_98[4];
    s16 flash_done;
    u8 reserved_9e[4];
    SpritePartTexture part;
    u8 reserved_ae[0xC];
    s8 next_tile_x;
    s8 next_tile_y;
} PulsingOrbSpell;

/* Body shared by the three child effects (update_timed_value_ramp_effect, update_timed_rectangle_effect and
 * update_grayscale_fade_effect each use part of it). */
typedef struct OrbChildEffect {
    s16 reserved_00;
    s16 ticks;
    s16 age;
    u8 reserved_06[4];
    s16 interval;
    s16 count;
    u8 reserved_0e[0x12];
    SpritePartTexture parts[2];
    ActorRecord *caster;
    ActorRecord *target;
    PulsingOrbSpell *spell;
    struct OrbChildEffect *reserved_44;
    struct OrbChildEffect *ramp;
    u8 reserved_4c[4];
    u8 values[60];
    s16 reserved_8c;
    s16 value_8e;
} OrbChildEffect;

/* The JAL at DUNGEON +0x190ead0 uses the three-argument chance-action ABI. */
s32 try_apply_action_by_chance(void *actor, s32 chance, s32 action);

/* The ellipse parameter block is local to the selector 37 bank. */
extern DungeonParameters D_80026410;
/* The absolute operand at DUNGEON +0x190e704 selects the fading child texture. */
extern SpritePartTexture D_800263E0;
/* The absolute operand at DUNGEON +0x190e590 selects the ramp child textures. */
extern SpritePartTexture D_800263EC[];
/* The bank-local texture operand at DUNGEON +0x190deb4 supplies the spell sprite. */
extern SpritePartTexture pulsing_orb_sprite_part;

void update_pulsing_orb_spell(PulsingOrbSpell *spell, ObjectPosition *position, SpriteFrameState *sprite) {
    ActorRecord *caster = spell->effect.caster;
    SpriteAttachmentVector offset;
    GpuRectBuffer rect;
    s16 steps[8][2] = {
        { 32, 0 }, { 32, 32 }, { 0, 32 }, { -32, 32 }, { -32, 0 }, { -32, -32 }, { 0, -32 }, { 32, -32 }
    };
    ObjectNodeHeader *caster_node;
    ObjectPosition *caster_position;
    ObjectNodeHeader *ramp_node;
    ObjectNodeHeader *node;
    ObjectPosition *target_position;
    ObjectPosition *child_position;
    SpriteFrameState *child_sprite;
    OrbChildEffect *child;
    int i;

    caster_node = NODE_HEADER(caster);
    caster_position = caster_node->position;
    switch (spell->effect.phase) {
    case 0:
        sprite->color.word = 0x808080;
        spell->part = pulsing_orb_sprite_part;
        sprite->source = &spell->part;
        spell->direction = ((u16)caster->facing >> 9) & 7;
        D_80026410.center_color.c.r = 0x80;
        D_80026410.center_color.c.g = 0x80;
        D_80026410.center_color.c.b = 0x80;
        D_80026410.outer_color.c.r = 4;
        D_80026410.outer_color.c.g = 4;
        D_80026410.outer_color.c.b = 4;
        rect.words[0] = 0x01400340;
        rect.words[1] = 0x00400040;
        draw_textured_ellipse(&D_80026410, &rect.rect, 1, 0);
        rectangle_effect_updated = 1;
        spell->effect.phase++;
    case 1:
        if (!get_sprite_attachment_vector(caster_node->sprite->source, caster_node->sprite, &offset, 0) &&
            !(caster_node->sprite->flags & 0x8000)) {
            break;
        }
        position->x.w.i = caster_position->x.w.i;
        position->y.w.i = caster_position->y.w.i;
        position->z.w.i = caster_position->z.w.i;
        if (!(caster_node->sprite->flags & 0x8000)) {
            position->x.w.i += offset.x;
            position->y.w.i += offset.y;
            position->z.w.i += offset.z;
        } else {
            position->z.w.i -= 64;
        }
        if (!(*spell->effect.context & 0x80)) {
            break;
        }
        if (!(spell->flags & 4)) {
            register_node(NODE_HEADER(spell), project_sprite_chain);
            sprite->tpage_abr = 0x20;
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0x80;
            sprite->scale_x = sprite->scale_y = 2000;
            sprite->flags |= 12;
            spell->flags |= 4;
        }
        if (caster->target) {
            SpriteFrameState *caster_sprite;

            target_position = NODE_HEADER(caster->target)->position;
            spell->target_height = target_position->z.w.i - (entity_height_offsets[((ActorRecord *)caster->target)->species] + 64);
            caster_sprite = NODE_HEADER(caster)->sprite;
            spell->next_tile_x = caster_sprite->tile_x + dir_step_x[spell->direction];
            spell->next_tile_y = caster_sprite->tile_y + dir_step_y[spell->direction];
            spell->flight_ticks = abs(caster->target_tile_x != caster_sprite->tile_x
                                          ? caster->target_tile_x - caster_sprite->tile_x
                                          : caster->target_tile_y - caster_sprite->tile_y) * 2 - 1;
        } else {
            spell->target_height = caster->ground_height - 80;
            spell->flight_ticks = 32;
        }
        position->velocity_x = steps[spell->direction][0] << 16;
        position->velocity_y = steps[spell->direction][1] << 16;
        position->velocity_z = ((spell->target_height << 16) - position->z.v) / spell->flight_ticks;
        spell->timer = 0;
        spell->shrinking = 0;
        spell->pulse_ticks = 0;
        spell->pulse_period = 5;
        spell->pulse_step = 200;
        spell->effect.phase++;
        spell->initial_ticks = spell->flight_ticks;
        spell->ticks_squared = spell->flight_ticks * spell->flight_ticks;
        break;
    case 2:
        for (i = 0; i < 4; i++) {
            spawn_linked_effect_particle(NODE_HEADER(spell), spell->direction, 0xE02020, (rand() & 0xFF) | 0x80, 0, 0, 0);
        }
        if (check_adjacent_tile_height_clearance(position->x.w.i, position->y.w.i, position->z.w.i, caster->target)) {
            spell->effect.phase = 8;
            spell->timer = 0;
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0;
            break;
        }
        sprite->angle_z += 400;
        if (sprite->angle_z > 0x1000) {
            sprite->angle_z -= 0x1000;
        }
        if (!spell->shrinking) {
            sprite->scale_x += spell->pulse_step;
            sprite->scale_y += spell->pulse_step;
        } else {
            sprite->scale_x -= spell->pulse_step;
            sprite->scale_y -= spell->pulse_step;
        }
        /* BYTES: The single-iteration loop weights references to spell so the compiler preserves the saved-register order. */
        do {
            if (++spell->pulse_ticks >= spell->pulse_period) {
                spell->pulse_ticks = 0;
                spell->shrinking ^= 1;
            }
        } while (0);
        if (--spell->flight_ticks <= 0) {
            if (caster->target) {
                spell->effect.phase = 3;
                spell->timer = 0;
                target_position = NODE_HEADER(caster->target)->position;
                position->x.w.i = target_position->x.w.i;
                position->y.w.i = target_position->y.w.i;
                position->z.w.i = spell->target_height;
                play_sound_if_enabled(0x300);
            } else {
                spell->effect.phase = 8;
                spell->timer = 0;
                sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0;
            }
            break;
        }
        position->x.v += position->velocity_x;
        position->y.v += position->velocity_y;
        position->z.v += position->velocity_z;
        break;
    case 3:
        sprite->angle_z += 400;
        if (sprite->angle_z > 0x1000) {
            sprite->angle_z -= 0x1000;
        }
        if (!spell->shrinking) {
            sprite->scale_x += spell->pulse_step;
            sprite->scale_y += spell->pulse_step;
        } else {
            sprite->scale_x -= spell->pulse_step;
            sprite->scale_y -= spell->pulse_step;
        }
        /* BYTES: runs once; see phase 2. */
        do {
            if (++spell->pulse_ticks >= spell->pulse_period) {
                spell->pulse_ticks = 0;
                spell->shrinking ^= 1;
            }
        } while (0);
        if (++spell->timer == 4) {
            ramp_node = allocate_flagged_object_node(0x212);
            child = NODE_BODY(ramp_node);
            if (ramp_node) {
                child->ticks = 120;
                for (i = 0; i < 60; i++) {
                    child->values[i] = 0;
                }
                child->value_8e = 200;
                ramp_node->update_callback = update_timed_value_ramp_effect;
                register_node(ramp_node, project_sprite_chain);
                child_sprite = ramp_node->sprite;
                child_sprite->flags &= ~12;
                child_sprite->tpage_abr = 0x20;
                child_sprite->depth_bias = 0;
                child_sprite->flags |= 0x80;
                child_position = ramp_node->position;
                child->interval = 0;
                child->count = 0;
                target_position = NODE_HEADER(caster->target)->position;
                child_position->x.v = target_position->x.v;
                child_position->y.v = target_position->y.v;
                child_position->z.v = target_position->z.v;
                child_sprite = ramp_node->sprite;
                child_sprite->scale_x = child_sprite->scale_y = ONE;
                child_sprite->color.c.r = child_sprite->color.c.g = child_sprite->color.c.b = 0x80;
                for (i = 0; i < 1; i++) {
                    child->parts[i] = D_800263EC[i];
                }
                child_sprite->source = child->parts;
            }
            node = allocate_flagged_object_node(0x212);
            child = NODE_BODY(node);
            if (node) {
                child->caster = caster;
                child->target = caster->target;
                child->spell = spell;
                child->ramp = NODE_BODY(ramp_node);
                node->update_callback = update_timed_rectangle_effect;
                register_node(node, project_sprite_chain);
                child_sprite = node->sprite;
                child_sprite->tpage_abr = 0x20;
                child_sprite->flags |= 12;
                child_sprite->depth_bias = 6;
                child_sprite->flags |= 0x80;
                child_position = node->position;
                child->interval = 0;
                child->count = 0;
                target_position = NODE_HEADER(caster->target)->position;
                child_position->x.v = target_position->x.v;
                child_position->y.v = target_position->y.v;
                child_position->z.v = target_position->z.v - (entity_height_offsets[((ActorRecord *)caster->target)->species] >> 1);
                child_sprite = node->sprite;
                child_sprite->scale_x = child_sprite->scale_y = 0x1400;
                child_sprite->color.c.r = child_sprite->color.c.g = child_sprite->color.c.b = 0x80;
                child->parts[0] = D_800263E0;
                child_sprite->source = child->parts;
            }
            if (spell->timer == 4) {
                spell->effect.phase = 4;
                spell->timer = 0;
                spell->flash_done = 0;
            }
        }
        break;
    case 4:
        spell->timer++;
        for (i = 0; i < 5; i++) {
        }
        sprite->angle_z += 400;
        if (sprite->angle_z > 0x1000) {
            sprite->angle_z -= 0x1000;
        }
        if (!spell->shrinking) {
            sprite->scale_x += spell->pulse_step;
            sprite->scale_y += spell->pulse_step;
        } else {
            sprite->scale_x -= spell->pulse_step;
            sprite->scale_y -= spell->pulse_step;
        }
        /* BYTES: runs once; see phase 2. */
        do {
            if (++spell->pulse_ticks >= spell->pulse_period) {
                spell->pulse_ticks = 0;
                spell->shrinking ^= 1;
            }
        } while (0);
        if (spell->timer > 10 && spell->timer < 28) {
            sprite->color.c.r = ((30 - spell->timer) << 7) / 20;
            sprite->color.c.g = ((30 - spell->timer) << 7) / 20;
            sprite->color.c.b = ((30 - spell->timer) << 7) / 20;
        }
        if (spell->timer >= 40) {
            sprite->flags |= 0x80;
        }
        if (!(spell->timer & 3) && spell->timer < 80) {
            node = allocate_flagged_object_node(0x212);
            child = NODE_BODY(node);
            if (node) {
                child->ticks = 20;
                child->interval = 10;
                child->age = 0;
                node->update_callback = update_grayscale_fade_effect;
                register_node(node, project_sprite_chain);
                child_sprite = node->sprite;
                child_sprite->tpage_abr = 0x20;
                child_sprite->flags |= 12;
                target_position = NODE_HEADER(caster->target)->position;
                child_position = node->position;
                child_position->x.v = target_position->x.v + ((((rand() & 31) + 16) * random_sign()) << 16);
                child_position->y.v = target_position->y.v + ((((rand() & 31) + 16) * random_sign()) << 16);
                child_position->z.v = target_position->z.v - (entity_height_offsets[((ActorRecord *)caster->target)->species] << 15) -
                                      ((rand() & 31) << 16);
                child_sprite = node->sprite;
                child_sprite->scale_x = child_sprite->scale_y = 0x800;
                child_sprite->color.c.r = child_sprite->color.c.g = child_sprite->color.c.b = 0;
                child->parts[0] = D_800263EC[0];
                child_sprite->source = child->parts;
            }
        }
        if (spell->timer == 80 && !try_trigger_target_record_effect(caster->target, 1, caster)) {
            int amount = (spell->effect.variant >> 2) + 2 + (generate_random_value() & 3);
            int chance = 16;

            if (current_spell_effect_variant == 0xFF) {
                chance = 0xFF;
            }
            try_apply_action_by_chance(caster->target, chance, amount);
        }
        if (spell->timer >= 120) {
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 5:
        if (spell->flash_done) {
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 6:
        if (++spell->timer > 10) {
            spell->effect.phase = 8;
            spell->timer = 30;
        }
        break;
    case 8:
        if (++spell->timer > 30) {
            spell->timer--;
            if (!rectangle_effect_updated) {
                g_dungeon_status.active_actor = 0;
                NODE_HEADER(spell)->flags |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            } else {
                rectangle_effect_updated = 0;
            }
        }
        break;
    }
}
