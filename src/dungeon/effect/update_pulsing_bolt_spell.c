#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/spell_resource_ids_data.h"
#include "dungeon/effect/motion/decrement_effect_counter_by_twelve.h"
#include "dungeon/effect/screen.h"
#include "dungeon/effect/shade/update_oscillating_fading_effect.h"
#include "dungeon/effect/sprite/draw.h"
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
typedef struct PulsingBoltSpell {
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
    s16 burst_done;
    u8 reserved_9e[4];
    SpritePartTexture part;
    u8 reserved_ae[0xC];
    s8 next_tile_x;
    s8 next_tile_y;
} PulsingBoltSpell;

/* Body of the burst left on the target when the bolt arrives. */
typedef struct BoltBurst {
    s16 reserved_00;
    s16 ticks_left;
    u8 reserved_04[0x16];
    SpritePartTexture part;
    u8 reserved_26[2];
    ActorRecord *caster;
    ActorRecord *target;
    PulsingBoltSpell *spell;
    u8 reserved_34[0xC];
    s32 base_height;
} BoltBurst;

s32 try_apply_action_by_chance(void *actor, s32 chance, s32 action);

/* Set by the spell and by its child callbacks while they run; the spell retires once it stays clear. */
extern s16 D_800259AC;
extern DungeonParameters D_80025988;
extern SpritePartTexture D_80025970;
extern SpritePartTexture D_800259A0;

/* BYTES: Declare the updater before its entry pointer so it heads the bank rodata. */
void update_pulsing_bolt_spell(PulsingBoltSpell *spell, ObjectPosition *position, SpriteFrameState *sprite);

void (*const dungeon_1912800_entry)(PulsingBoltSpell *, ObjectPosition *, SpriteFrameState *) =
    update_pulsing_bolt_spell;

void update_pulsing_bolt_spell(PulsingBoltSpell *spell, ObjectPosition *position, SpriteFrameState *sprite) {
    ActorRecord *caster = spell->effect.caster;
    SpriteAttachmentVector offset;
    GpuRectBuffer rect;
    s16 steps[8][2] = {
        { 32, 0 }, { 32, 32 }, { 0, 32 }, { -32, 32 }, { -32, 0 }, { -32, -32 }, { 0, -32 }, { 32, -32 }
    };
    ObjectNodeHeader *caster_node;
    ObjectPosition *caster_position;
    ObjectNodeHeader *node;
    ObjectPosition *target_position;
    ObjectPosition *burst_position;
    SpriteFrameState *burst_sprite;
    BoltBurst *burst;
    int i;

    caster_node = NODE_HEADER(caster);
    caster_position = caster_node->position;
    switch (spell->effect.phase) {
    case 0:
        sprite->color.word = 0x808080;
        spell->part = D_800259A0;
        sprite->source = &spell->part;
        spell->direction = ((u16)caster->facing >> 9) & 7;
        D_80025988.center_color.c.r = 0xE0;
        D_80025988.center_color.c.g = 0xE0;
        D_80025988.center_color.c.b = 0xE0;
        D_80025988.outer_color.c.r = 0;
        D_80025988.outer_color.c.g = 0;
        D_80025988.outer_color.c.b = 0;
        rect.words[0] = 0x01400340;
        rect.words[1] = 0x00400040;
        draw_textured_ellipse(&D_80025988, &rect.rect, 1, 0);
        D_800259AC = 1;
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
            ActorRecord *target = caster->target;
            SpriteFrameState *caster_sprite;

            target_position = NODE_HEADER(target)->position;
            spell->target_height = target_position->z.w.i - (entity_height_offsets[target->species] >> 1);
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
        for (i = 0; i < 16; i++) {
            /* The effect's definition still takes the stand-in actor record and an untyped payload: it is given the
               spell's node and the colour word. */
            create_jittered_countdown_effect((EntityRec *)NODE_HEADER(spell), spell->direction, (void *)0xFF4040, (rand() & 63) | 64, 0, 0, 0);
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
        if (++spell->pulse_ticks >= spell->pulse_period) {
            spell->pulse_ticks = 0;
            spell->shrinking ^= 1;
        }
        if (--spell->flight_ticks <= 0) {
            if (caster->target) {
                spell->effect.phase = 3;
                spell->timer = 0;
                {
                    ActorRecord *target = caster->target;
                    target->flags14 |= 0x100000;
                }
                play_sound_if_enabled(0x300);
                target_position = NODE_HEADER(caster->target)->position;
                position->x.w.i = target_position->x.w.i;
                position->y.w.i = target_position->y.w.i;
                {
                    ActorRecord *target = caster->target;
                    position->z.w.i = target_position->z.w.i - entity_height_offsets[target->species];
                }
                node = allocate_flagged_object_node(0x212);
                if (node) {
                    burst = NODE_BODY(node);
                    burst->ticks_left = 120;
                    burst->caster = caster;
                    burst->target = caster->target;
                    burst->spell = spell;
                    node->update_callback = update_oscillating_fading_effect;
                    register_node(node, draw_linked_gap_effects);
                    burst_sprite = node->sprite;
                    burst_sprite->tpage_abr = 0x20;
                    burst_sprite->depth_bias = 0;
                    burst_sprite->flags |= 12;
                    target_position = NODE_HEADER(caster->target)->position;
                    burst_position = node->position;
                    burst_position->x.v = target_position->x.v;
                    burst_position->y.v = target_position->y.v;
                    burst_position->z.v = target_position->z.v - (20 << 16);
                    {
                        ActorRecord *target = caster->target;
                        burst_position->z.v = -((entity_height_offsets[target->species] >> 1) << 16);
                    }
                    if (burst_position->z.v > -(20 << 16)) {
                        burst_position->z.v = -(20 << 16);
                    }
                    burst_position->z.v += target_position->z.v;
                    burst->base_height = target_position->z.v;
                    burst_sprite = node->sprite;
                    burst_sprite->color.c.r = burst_sprite->color.c.g = burst_sprite->color.c.b = 0x80;
                    burst_sprite->scale_x = burst_sprite->scale_y = 0;
                    burst->part = D_80025970;
                    burst_sprite->source = &burst->part;
                }
            } else {
                spell->effect.phase = 8;
                spell->timer = 0;
            }
            sprite->color.c.r = sprite->color.c.g = sprite->color.c.b = 0;
            sprite->scale_x = sprite->scale_y = 0;
            break;
        }
        position->x.v += position->velocity_x;
        position->y.v += position->velocity_y;
        position->z.v += position->velocity_z;
        break;
    case 3:
        if (++spell->timer == 4) {
            spell->effect.phase = 4;
            spell->timer = 0;
            spell->burst_done = 0;
        }
        break;
    case 4:
        if (++spell->timer == 100) {
            if (!try_trigger_target_record_effect(caster->target, 2, caster)) {
                int amount = (spell->effect.variant >> 2) + 2 + (generate_random_value() & 3);
                int chance = 16;


                if (current_spell_effect_variant == 0xFF) {
                    chance = 0xFF;
                }
                try_apply_action_by_chance(caster->target, chance, amount);
            }
            {
                ActorRecord *target = caster->target;
                target->flags14 &= ~0x100000;
            }
        }
        if (spell->timer >= 120) {
            spell->timer = 0;
            spell->effect.phase++;
        }
        break;
    case 5:
        if (spell->burst_done) {
            ActorRecord *target = caster->target;

            target->flags14 &= ~0x100000;
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
            if (!D_800259AC) {
                g_dungeon_status.active_actor = 0;
                NODE_HEADER(spell)->flags |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            } else {
                D_800259AC = 0;
            }
        }
        break;
    }
}
