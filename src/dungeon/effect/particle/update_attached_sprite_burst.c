#include "common.h"
#include "dungeon/effect/attached_sprite_burst.h"
#include "dungeon/effect/decrement_flagged_item_parameters.h"
#include "engine/node/registration.h"
#include "sdk/libgte.h"
#include "sdk/libc.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity_objects.h"
#include "shared/object_node_flags.h"
#include "shared/sprite_frame_state.h"
#include "slus/imports.h"

void update_attached_sprite_burst(AttachedSpriteBurst *effect, ObjectPosition *position,
                                  SpriteFrameState *sprite) {
    s16 offset[3];
    int remaining = -1;
    int shift, burst, i;
    void *command;
    ObjectNodeHeader *node;
    DriftingEffect *child;
    SpriteFrameState *particle;

    effect->ticks++;
    effect->parent->flags |= 0x8000;
    advance_sprite_animation_and_textures(sprite);
    switch (effect->phase) {
    case 0:
        effect->phase++;
        break;
    case 1:
        remaining = (effect->ticks >> 1) + 5;
        if (sprite->scale_y >= 0x140) {
            sprite->scale_x = sprite->scale_y = sprite->scale_y - 0x140;
        }
        if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source,
                                                   &reference_tile_object, offset, 0)) {
            int ticks = effect->ticks;
            effect->x.v += (offset[0] + view_reference_entity.x.w.i - effect->x.w.i) << 14;
            effect->y.v += (offset[1] + view_reference_entity.y.w.i - effect->y.w.i) << 14;
            effect->z.v += (offset[2] + view_reference_entity.z.w.i - effect->z.w.i) << 14;
            effect->z.v -= rsin((ticks << 11) / 10) << 9;
            position->x = effect->x;
            position->y = effect->y;
            position->z = effect->z;
            sprite->color.c.r -= sprite->color.c.r >> 1;
            sprite->color.c.g -= sprite->color.c.g >> 1;
        } else {
            position->x.v += (effect->x.v - position->x.v) >> 1;
            position->y.v += (effect->y.v - position->y.v) >> 1;
            position->z.v += (effect->z.v - position->z.v) >> 1;
        }
        if (effect->ticks >= 10) {
            effect->phase++;
        }
        break;
    case 2:
        if (sprite->scale_y >= 0xa00) {
            sprite->scale_x = sprite->scale_y = sprite->scale_y - 0x200;
        } else {
            sprite->scale_x = sprite->scale_y = 0x800;
        }
        remaining = 9;
        if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source,
                                                   &reference_tile_object, offset, 0)) {
            effect->x.v += (offset[0] + view_reference_entity.x.w.i - effect->x.w.i) << 15;
            effect->y.v += (offset[1] + view_reference_entity.y.w.i - effect->y.w.i) << 15;
            effect->z.v += (offset[2] + view_reference_entity.z.w.i - effect->z.w.i) << 15;
            sprite->color.c.r -= sprite->color.c.r >> 1;
            sprite->color.c.g -= sprite->color.c.g >> 1;
        }
        if (effect->ticks >= 12) {
            effect->phase++;
        }
        break;
    case 3:
        remaining = 10;
        if (resolve_record_orientation_or_fallback(reference_tile_object.sprite_source,
                                                   &reference_tile_object, offset, 0)) {
            effect->x.v += (offset[0] + view_reference_entity.x.w.i - effect->x.w.i) << 15;
            effect->y.v += (offset[1] + view_reference_entity.y.w.i - effect->y.w.i) << 15;
            effect->z.v += (offset[2] + view_reference_entity.z.w.i - effect->z.w.i) << 15;
        }
        if (primary_actor_record->target && effect->ticks >= 25) {
            for (i = 3; i >= 0; i--) {
                node = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (node) {
                    node->update_callback = update_drifting_effect;
                    register_node(node, project_sprite_chain);
                    particle = node->sprite;
                    child = NODE_BODY(node);
                    child->parent = effect->parent;
                    node->position->x.w.i = effect->x.w.i + (func_80069EF8() & 63) - 32;
                    node->position->y.w.i = effect->y.w.i + (func_80069EF8() & 63) - 32;
                    node->position->z.w.i = effect->z.w.i - func_80069EF8() % 96;
                    particle->scale_x = particle->scale_y = ONE;
                    particle->tpage_abr = 0x60;
                    particle->unk_00 = effect_sprite_sources;
                    particle->flags |= 12;
                    particle->source = effect_sprite_sources[0].source;
                    particle->unk_04 = 0;
                    particle->frame_ticks = 0;
                    particle->color.word = 0x808080;
                }
            }
        }
        if (effect->ticks >= 28) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
    shift = 10;
    if (effect->phase != 3) {
        shift = 12;
    }
    burst = (u16)effect->ticks >= 18 && (u16)effect->ticks < 22;
    for (i = remaining + burst * 4; i >= 0; i--) {
        node = allocate_list_node(0x312, &scene_object_list_anchor.next);
        if (node) {
            node->update_callback = update_drifting_effect;
            register_node(node, project_sprite_chain);
            particle = node->sprite;
            child = NODE_BODY(node);
            child->parent = effect->parent;
            node->position->x.v = effect->x.v + (((func_80069EF8() & 1023) - 511) << (shift + burst));
            node->position->y.v = effect->y.v + (((func_80069EF8() & 1023) - 511) << (shift + burst));
            node->position->z.v = effect->z.v + (((func_80069EF8() & 1023) - 511)
                                         << (effect->phase == 3 ? shift + 1 : shift - 1));
            if (effect->phase != 3) {
                node->position->velocity_z = 0;
            } else {
                node->position->velocity_z = -0x80000 - func_80069EF8() * 8;
            }
            particle->scale_x = ONE + (burst << 10);
            particle->scale_y = effect->phase == 3 ? 0x15e0 + (burst << 10) : ONE;
            particle->tpage_abr = 0x60;
            particle->flags |= 12;
            particle->unk_00 = &secondary_sprite;
            command = secondary_sprite.source;
            particle->unk_04 = 0;
            particle->frame_ticks = 0;
            particle->color.word = 0x4040c0;
            particle->source = command;
        }
    }
}
