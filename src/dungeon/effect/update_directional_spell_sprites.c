#include "common.h"
#include "dungeon/effect/spell_effect.h"
#include "dungeon/effect/screen.h"
#include "dungeon/effect/motion.h"
#include "dungeon/item.h"
#include "dungeon/level.h"
#include "engine/node/allocation.h"
#include "dungeon/data.h"
#include "dungeon/effect/sprite/timed_projectile_entries.h"
#include "dungeon/actor/ability_eligibility.h"
#include "dungeon/system.h"
#include "sdk/rand.h"
#include "sdk/abs.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_source.h"

typedef struct DirectionalSpell {
    SpellEffectHeader effect;
    u8 reserved_0c[0x44];
    s16 timer;
    s16 flags;
} DirectionalSpell;

typedef struct DelayedSpellSprite {
    DirectionalSpell *owner;
    u8 reserved_04[0x44];
    s16 delay;
    s16 reserved_4a;
    s16 phase;
    s16 interval;
} DelayedSpellSprite;

void update_directional_spell_sprites(DirectionalSpell *spell, ObjectPosition *position, SpriteFrameState *sprite) {
    ActorRecord *caster = spell->effect.caster;
    ObjectNodeHeader *caster_node;
    SpriteFrameState *caster_sprite = NODE_HEADER(caster)->sprite;
    int i = ((u16)caster->facing >> 9) & 7;
    int dx = dir_step_x[i], dy = dir_step_y[i];
    ObjectPosition endpoint;
    ObjectNodeHeader *node;
    SpriteFrameState *particle;
    DelayedSpellSprite *child;
    int j, distance, height;

    spell->timer--;
    caster_node = NODE_HEADER(caster);
    switch (spell->effect.phase) {
    case 0:
        if (!(*spell->effect.context & 0x80)) {
            return;
        }
        position->x.v = caster_node->position->x.v;
        position->y.v = caster_node->position->y.v;
        position->z.v = caster_node->position->z.v;
        position->velocity_x = dx << 19;
        position->velocity_y = dy << 19;
        caster->target = scan_actor_along_heading(caster, caster_sprite->tile_x,
            caster_sprite->tile_y, caster->facing, get_spell_range(4));
        if (!caster->target) {
            endpoint.x.w.i = ((caster_sprite->tile_x + dx * get_spell_range(4)) << 6) + 32;
            /* BUG: The no-target endpoint uses tile_x as the origin for both axes. */
            endpoint.y.w.i = ((caster_sprite->tile_x + dy * get_spell_range(4)) << 6) + 32;
            endpoint.z.w.i = sample_terrain_surface_height((u16)endpoint.x.w.i, (u16)endpoint.y.w.i,
                                                            caster_node->position->z.w.i - 48);
            if (endpoint.z.w.i > 0) {
                endpoint.z.w.i = 0;
            }
            for (distance = 0; get_spell_range(4) > distance; distance++) {
                i = ((caster_sprite->tile_x + dx * distance) << 6) + 32;
                j = ((caster_sprite->tile_y + dy * distance) << 6) + 32;
                /* The callee's last parameter is an integer in its other callers; the target pointer is passed as its value. */
                if ((s16)check_enabled_neighbor_height((u16)i, (u16)j, sample_terrain_surface_height((u16)i, (u16)j, -1024),
                        caster->facing, (long)caster->target) ||
                    (s16)sample_terrain_surface_height((u16)i, (u16)j, caster_node->position->z.w.i - 48) >= 512) {
                    break;
                }
            }
            i = dx * distance;
            j = dy * distance;
        } else {
            node = NODE_HEADER(caster->target);
            endpoint = *node->position;
            i = node->sprite->tile_x - caster_sprite->tile_x;
            j = node->sprite->tile_y - caster_sprite->tile_y;
            if ((node->sprite->flags & 0x8000) && (sprite->flags & 0x8000)) {
                spell->effect.phase = 1;
                spell->timer = 0;
                return;
            }
        }
        distance = abs(i);
        {
            int y = abs(j);
            if (distance < y) {
                distance = y;
            }
        }
        if (distance < 2) {
            i = 0;
            j = 3;
        } else {
            i = 1;
            j = 0;
        }
        height = caster_node->position->z.w.i;
        for (; i < distance; i++) {
            for (; j < 4; j++) {
                node = allocate_list_node(0x112, &scene_object_list_anchor.next);
                if (node) {
                    child = NODE_BODY(node);
                    node->update_callback = advance_delayed_sprite_animation;
                    particle = node->sprite;
                    node->position->x.w.i = ((caster_sprite->tile_x + i * dx) << 6) + 32 + dx * (j << 4);
                    node->position->y.w.i = ((caster_sprite->tile_y + i * dy) << 6) + 32 + dy * (j << 4);
                    node->position->z.w.i = sample_terrain_surface_height((u16)node->position->x.w.i, (u16)node->position->y.w.i,
                                                                          caster_node->position->z.w.i - 48);
                    if (node->position->z.w.i >= 512) {
                        node->position->z.w.i = height;
                    }
                    height = node->position->z.w.i;
                    particle->scale_x = particle->scale_y = ONE;
                    {
                        SpriteSourceEntry *entry = spark_sprite_entries;
                        void *command;
                        particle->unk_00 = entry;
                        command = entry->source;
                        particle->color.word = 0x808080;
                        particle->unk_04 = 0;
                        particle->frame_ticks = 0;
                        particle->source = command;
                    }
                    child->owner = spell;
                    child->delay = i * 4 + j * 2;
                    child->interval = 0;
                    child->phase = 0;
                }
            }
            j = 0;
        }
        spell->timer = distance * 4 + 2;
        if (caster->target) {
            node = allocate_list_node(0x112, &scene_object_list_anchor.next);
            if (node) {
                child = NODE_BODY(node);
                particle = node->sprite;
                node->update_callback = advance_delayed_sprite_animation;
                *node->position = endpoint;
                particle->scale_x = particle->scale_y = 0x2000;
                particle->tpage_abr = 0;
                particle->flags |= 12;
                {
                    SpriteSourceEntry *entry = spark_sprite_entries;
                    void *command;
                    particle->unk_00 = entry;
                    command = entry->source;
                    particle->unk_04 = 0;
                    particle->frame_ticks = 0;
                    particle->color.word = 0x808080;
                    particle->source = command;
                }
                child->owner = spell;
                child->delay = spell->timer;
                child->interval = 1;
                child->phase = 0;
            }
            for (i = 40; i >= 0; i--) {
                node = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (node) {
                    particle = node->sprite;
                    child = NODE_BODY(node);
                    node->update_callback = advance_delayed_sprite_animation;
                    node->position->x.w.i = endpoint.x.w.i + (rand() & 63) - 32;
                    node->position->y.w.i = endpoint.y.w.i + (rand() & 63) - 32;
                    node->position->z.w.i = endpoint.z.w.i - rand() % 72 - 16;
                    particle->scale_x = particle->scale_y = ONE;
                    particle->tpage_abr = 0x60;
                    particle->flags |= 12;
                    {
                        SpriteSourceEntry *entry = &timed_projectile_sprite_entries;
                        void *command;
                        particle->unk_00 = entry;
                        command = entry->source;
                        particle->unk_04 = 0;
                        particle->frame_ticks = 0;
                        particle->color.word = 0x606060;
                        particle->source = command;
                    }
                    child->owner = spell;
                    child->delay = spell->timer + rand() % 12 + 2;
                    child->interval = 0;
                    child->phase = 0;
                }
            }
            spell->timer += 22;
        }
        play_sound_if_enabled(0x300);
        spell->effect.phase++;
        break;
    case 1:
        if (spell->timer >= 22) {
            position->x.v += position->velocity_x;
            position->y.v += position->velocity_y;
            position->z.w.i = sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i,
                                                            caster_node->position->z.w.i - 48);
            if (position->z.w.i > 0) {
                position->z.w.i = 0;
            }
        }
        if (spell->timer < 0) {
            if (caster->target) {
                apply_attack_power_and_element_effects(caster->target, 8, spell->effect.variant, 1,
                                                       caster->facing, caster, 2);
            }
            spell->timer = 16;
            spell->effect.phase++;
        }
        break;
    case 2:
        if (spell->flags & 0x8000) {
            spell->flags &= 0x7fff;
        } else if (spell->timer <= 0) {
            ObjectFlagBlock *status = &object_flag_block;
            g_dungeon_status.active_actor = 0;
            NODE_HEADER(spell)->flags |= NODE_REMOVE;
            status->flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
