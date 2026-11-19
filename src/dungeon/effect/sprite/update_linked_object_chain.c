#include "shared/object_node.h"
#include "shared/dungeon_effect_status.h"
#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"

#include "slus/gp_shared_81510.h"
#include "engine/node.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/sprite/linked_object_chain.h"
#include "dungeon/data.h"

s32 func_8002589C(ObjectNodeHeader *, s32, s32);        /* extern */
void func_80026548(MATRIX *dest, LinkedSpriteFrame *source);                 /* extern */
void func_800266D0(SpriteFrameState *sprite, s16 entry_index);                  /* extern */
s32 find_eligible_entry_at_coordinates();                /* extern */
void apply_attack_power_and_element_effects(); /* extern */
s32 check_layer_offset_height();              /* extern */
#include "dungeon/effect/sprite_effect_count_data.h"
extern s32 D_800C9034();




/* Updates effect movement and fading, or copies the chain head's position and appearance. */
void update_linked_object_chain(LinkedObjectChainBody *effect_in, ObjectPosition *motion_in, SpriteFrameState *sprite_in) {
    SpriteFrameState *sprite;
    s32 x_step;
    s32 end_frame;
    TileObject *resident_sprite;
    ObjectPosition *source_data;
    ActorRecord *source_data_2;
    s16 *update_ptr;
    s16 *update_y_base;
    s16 *update_y_ptr;
    s32 update_y_offset;
    u16 linked_flags;
    ObjectFlagBlock *linked_global;
    s16 frame_toggle;
    s16 fade_ticks;
    s16 next_z;
    s16 move_ticks;
    s16 phase;
    s16 rise_ticks;
    s16 follow_ticks;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    struct SpriteAttachment *transform_result;
    s32 tile_object;
    s32 found_tile;
    u16 steps_left;
    u16 update_x;
    u16 update_y;
    u8 frame;
    u8 brightness;
    u8 next_brightness;
    u8 start_tile_y;
    ObjectNodeHeader *head;
    SpriteFrameState *linked_sprite;

    head = effect_in->head;
    sprite = sprite_in;
    sprite_effect_update_count = sprite_effect_update_count + 1;
    if (head == NULL) {
        step_entry_index_within_bounds(sprite, &effect_in->unk_32, effect_in->unk_38,
            effect_in->unk_36);
        func_80026548(&effect_in->transform, sprite->unk_00);
        phase = effect_in->unk_2C;
        switch (phase) {
        case 0:
            motion_in->z.v =
                (s32) (motion_in->z.v + 0xFFFF0000);
            brightness = sprite->color.c.r;
            next_brightness = brightness + ((s32) (0x80 - brightness) / effect_in->unk_30);
            sprite->color.c.r = next_brightness;
            sprite->color.c.b = next_brightness;
            sprite->color.c.g = next_brightness;
            frame_toggle = (effect_in->unk_30 ^ 1) & 1;
            effect_in->unk_32 = frame_toggle;
            rise_ticks = effect_in->unk_30 - 1;
            effect_in->unk_30 = rise_ticks;
            if (((rise_ticks << 0x10) <= 0) && (sprite->flags & 0x4000)) {
                end_frame = 8;
                source_data_2 = dungeon_actor_ring_anchor;
                effect_in->unk_38 = end_frame;
                effect_in->unk_36 = 0xF;
                effect_in->unk_32 = 1;
                effect_in->unk_3A = source_data_2->ground_height;
                effect_in->unk_40 = (source_data_2->facing >> 9) & 7;
                resident_sprite = &reference_tile_object;
                effect_in->unk_3C = resident_sprite->tile_position.parts.tile_x;
                start_tile_y = resident_sprite->tile_position.parts.tile_y;
                effect_in->unk_42 = end_frame;
                effect_in->unk_30 = 3;
                effect_in->unk_2C = (s16) ((u16) effect_in->unk_2C + 1);
                effect_in->unk_3E = start_tile_y;
            }
            break;
        case 1:
            sprite = (SpriteFrameState *)&reference_tile_object;
            {
                SVECTOR *offset = &effect_in->position_offset;

                transform_result = resolve_record_orientation_or_fallback(sprite->source, sprite, offset, 0);
            }
            follow_ticks = effect_in->unk_30 - 1;
            effect_in->unk_30 = follow_ticks;
            if ((follow_ticks << 0x10) <= 0 || transform_result == 0
                || (sprite->flags & 0x8000) != 0) {
                if (reference_tile_object.sprite_flags & 0x8000) {
                    motion_in->x.w.i = ((u16)view_reference_entity.x.w.i);
                    motion_in->y.w.i = ((u16)view_reference_entity.y.w.i);
                    motion_in->z.w.i = ((u16)view_reference_entity.z.w.i) - 0x10;
                }
                effect_in->unk_30 = 0;
                effect_in->unk_2C = (u16) effect_in->unk_2C + 1;
            } else {
                motion_in->x.w.i =
                    (s16) (((u16)view_reference_entity.x.w.i) + (u16)effect_in->position_offset.vx);
                motion_in->y.w.i =
                    (s16) (((u16)view_reference_entity.y.w.i) + (u16)effect_in->position_offset.vy);
                motion_in->z.w.i =
                    (s16) (((u16)view_reference_entity.z.w.i) + (u16)effect_in->position_offset.vz);
            }
            break;
        case 2:
            if (effect_in->unk_30 == 0) {
                if ((check_layer_offset_height(((effect_in->unk_3C << 6) + 0x20) & 0xFFE0,
                    ((effect_in->unk_3E << 6) + 0x20) & 0xFFE0,
                    (s16) (effect_in->unk_3A - 0x20),
                    (s16) (effect_in->unk_40 << 9)) << 0x10) != 0
                    || (steps_left = effect_in->unk_42 - 1,
                        effect_in->unk_42 = steps_left, (steps_left << 0x10) <= 0)) {
                    effect_in->unk_2C = 0x10;
                    ((Fixed1616 *)&motion_in->velocity_x)->w.i =
                        dir_step_x[effect_in->unk_40] * 8;
                    ((Fixed1616 *)&motion_in->velocity_y)->w.i =
                        dir_step_y[effect_in->unk_40] * 8;
                    x_step = 8;
                    ((Fixed1616 *)&motion_in->velocity_z)->w.i = x_step;
                    effect_in->unk_30 = x_step;
                } else {
                    update_ptr = &dir_step_x[effect_in->unk_40];
                    update_x = (u16) effect_in->unk_3C;
                    update_x += ((u16) *update_ptr);
                    effect_in->unk_3C = update_x;
                    update_y_base = dir_step_y;
                    update_y_offset = effect_in->unk_40 << 1;
                    update_y_ptr = (s16 *) ((unsigned long) update_y_offset + (unsigned long) update_y_base);
                    update_y = (u16) effect_in->unk_3E + *update_y_ptr;
                    effect_in->unk_30 = 3;
                    effect_in->unk_3E = update_y;
                }
            }
            target_x = effect_in->unk_3C << 6;
            delta_x = motion_in->x.w.i - 0x20;
            motion_in->x.w.i =
                (u16) motion_in->x.w.i
            + ((target_x - delta_x) / effect_in->unk_30);
            tile_object = effect_in->unk_3E;
            tile_object <<= 6;
            delta_y = motion_in->y.w.i - 0x20;
            tile_object -= delta_y;
            tile_object /= effect_in->unk_30;
            next_z = (u16) motion_in->z.w.i + 5;
            motion_in->z.w.i = next_z;
            motion_in->y.w.i =
                (u16) motion_in->y.w.i + tile_object;
            if (((s16) effect_in->unk_3A - 0x10) < next_z) {
                motion_in->z.w.i =
                    (s16) (effect_in->unk_3A - 0x10);
            }
            move_ticks = effect_in->unk_30 - 1;
            effect_in->unk_30 = move_ticks;
            if (move_ticks == 2) {
                found_tile = find_eligible_entry_at_coordinates(dungeon_actor_ring_anchor, (u16) effect_in->unk_3C,
                    (u16) effect_in->unk_3E);
                if (found_tile != 0) {
                    tile_object = found_tile;
                    apply_attack_power_and_element_effects(tile_object, 0xC, linked_effect_chain_attack_option, 9,
                        (s32) (s16) (effect_in->unk_40 << 9), linked_effect_chain_attack_event[0], 5);
                }
            }
            func_8002589C(NODE_HEADER(effect_in), effect_in->unk_40, 0xF0);
            break;
        case 0x10:
            motion_in->x.v += motion_in->velocity_x;
            motion_in->y.v += motion_in->velocity_y;
            motion_in->z.v += motion_in->velocity_z;
            motion_in->velocity_x -= motion_in->velocity_x
            >> 2;
            motion_in->velocity_y -= motion_in->velocity_x
            >> 2;
            if (((s16) effect_in->unk_3A - 0x10)
                < motion_in->z.w.i) {
                motion_in->z.w.i =
                    (s16) (effect_in->unk_3A - 0x10);
            }
            sprite->color.c.r = sprite->color.c.r
            - ((s32) sprite->color.c.r / effect_in->unk_30);
            sprite->color.c.g = sprite->color.c.g
            - ((s32) sprite->color.c.g / effect_in->unk_30);
            sprite->color.c.b = sprite->color.c.b
            - ((s32) sprite->color.c.b / effect_in->unk_30);
            fade_ticks = effect_in->unk_30 - 1;
            effect_in->unk_30 = fade_ticks;
            if ((fade_ticks << 0x10) <= 0) {
                linked_effect_chain_updated[0] = 0;
                linked_flags = NODE_HEADER(effect_in)->flags;
                linked_global = &object_flag_block;
                linked_flags |= 0x8000;
                NODE_HEADER(effect_in)->flags = linked_flags;
                linked_global->flags |= 0x8000;
                return;
            }
            frame = ((u8)(sprite->unk_04));
            if ((s8) frame == effect_in->unk_36) {
                effect_in->unk_32 = -1;
            } else if ((s8) frame == effect_in->unk_38) {
                effect_in->unk_32 = 1;
            }
            func_8002589C(NODE_HEADER(effect_in), effect_in->unk_40, 0xF0);
            break;
        }
    } else {
        if (head->flags & 0x8000) {
            linked_flags = NODE_HEADER(effect_in)->flags;
            linked_global = &object_flag_block;
            linked_flags |= 0x8000;
            NODE_HEADER(effect_in)->flags = linked_flags;
            linked_global->flags |= 0x8000;
            return;
        }
        source_data = head->position;
        motion_in->x.w.i = source_data->x.w.i;
        motion_in->y.w.i = source_data->y.w.i;
        motion_in->z.w.i = source_data->z.w.i;
        linked_sprite = effect_in->head->sprite;
        func_800266D0(sprite, linked_sprite->unk_04);
        func_80026548(&effect_in->transform, sprite->unk_00);
        sprite->scale_x = linked_sprite->scale_x;
        sprite->scale_y = linked_sprite->scale_y;
        sprite->offset_x = linked_sprite->offset_x;
        sprite->color.word = linked_sprite->color.word;
        sprite->angle_x = linked_sprite->angle_x;
        sprite->angle_y = linked_sprite->angle_y;
        sprite->angle_z = linked_sprite->angle_z;
    }
    if (effect_in->unk_2E == 0) {
        register_node(NODE_HEADER(effect_in), &D_800C9034);
        effect_in->unk_2E = (s16) ((u16) effect_in->unk_2E + 1);
    }
}
