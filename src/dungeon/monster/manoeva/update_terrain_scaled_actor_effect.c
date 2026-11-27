#include "shared/actor_status_ids.h"
#include "dungeon/monster/manoeva.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/level.h"
#include "engine/entity.h"
#include "sdk/libgte.h"




   /* sample in update_terrain_scaled_actor_effect */


   /* arg1 in update_terrain_scaled_actor_effect */




/* Updates effect position and animated scales, flagging invalid or fully expanded effects. */
void update_terrain_scaled_actor_effect(ManoevaTerrainEffectBody *effect, MovingPosition *out_position, SpriteFrameState *out_render)
{
    ObjectNodeHeader *owner_base;
    ActorRecord *owner;
    ObjectPosition *source_position;
    s16 target_scale;
    s32 sampled_height;
    s32 scale_cap;
    s16 height_scale;
    s16 next_scale;
    u16 scale_value;
    u8 effect_kind;

    height_scale = 0x1000;
    target_scale = height_scale;
    if (effect->expanding == 0) {
        if (*effect->owner_action_flags & 1) {
            target_scale = 0x1400;
        }

        owner_base = effect->owner_node;
        owner = NODE_BODY(owner_base);
        if (((owner->flags1C) & 0x00800000) ||
            (owner_base->flags & 0x8000) ||
            (owner->unk_8C.address == (void *)transfer_linked_object_state) ||
            ((get_entity_effect_value(owner, STATUS_FROG) << 16) != 0)) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }

        if (((s8)owner->unk_87) != -1) {
            MovingPosition *sample_position = (MovingPosition *)effect->owner_position;

            sampled_height = sample_terrain_surface_height(sample_position->x,
                                sample_position->y,
                                (s16)(sample_position->z - 4));
        } else {
            sampled_height = effect->owner_position->z.unsigned_parts.integer;
        }

        source_position = effect->owner_position;
        height_scale = height_scale - ((sampled_height - source_position->z.unsigned_parts.integer) << 6);
        if (height_scale < 0) {
            height_scale = 0;
        }
        if (height_scale >= 0x1801) {
            height_scale = 0;
        }

        if (height_scale >= 0xF81) {
            out_position->x = source_position->x.unsigned_parts.integer;
            out_position->y = effect->owner_position->y.unsigned_parts.integer;
            out_position->z = sampled_height;

            scale_cap = target_scale;
            if (scale_cap == 0x1000) {
                scale_value = effect->base_scale.u;
                if (effect->base_scale.s >= 0x1001) {
                    next_scale = scale_value - 0x400;
                    effect->base_scale.s = next_scale;
                    if (next_scale < 0x1000) {
                        effect->base_scale.s = scale_cap;
                    }
                } else {
                    next_scale = scale_value + 0x400;
                    effect->base_scale.s = next_scale;
                    if (next_scale >= 0x1001) {
                        effect->base_scale.s = scale_cap;
                    }
                }
            } else {
                next_scale = effect->base_scale.u + 0x800;
                effect->base_scale.s = next_scale;
                if (scale_cap < next_scale) {
                    effect->base_scale.s = target_scale;
                }
            }
        } else {
            next_scale = effect->base_scale.u - 0x400;
            effect->base_scale.s = next_scale;
            if (next_scale < 0) {
                effect->base_scale.s = 0;
            }
        }

        out_render->clut = effect->owner_sprite->clut;
        out_render->color.word = effect->owner_sprite->color.word;
        out_render->scale_x = effect->base_scale.u +
            (rcos(effect->wobble_phase.s << 8) >> 4);
        out_render->scale_y = effect->base_scale.u +
            (rsin(effect->wobble_phase.s << 8) >> 4);

        effect_kind = *effect->owner_action;
        if (effect_kind == 0xF) {
            effect->corner0_scale_x =
                (rcos(effect->wobble_phase.s << 8) >> 3) + 0x1000;
            effect->corner0_scale_y =
                (rsin(effect->wobble_phase.s << 8) >> 3) + 0x1000;
            effect->corner1_scale_x =
                (rcos((effect->wobble_phase.s << 8) + 0x200) >> 3) + 0x1000;
            effect->corner1_scale_y =
                (rsin((effect->wobble_phase.s << 8) + 0x200) >> 3) + 0x1000;
            effect->corner2_scale_x =
                (rcos((effect->wobble_phase.s << 8) + 0x400) >> 3) + 0x1000;
            effect->corner2_scale_y =
                (rsin((effect->wobble_phase.s << 8) + 0x400) >> 3) + 0x1000;
            effect->corner3_scale_x =
                (rcos((effect->wobble_phase.s << 8) + 0x600) >> 3) + 0x1000;
            effect->corner3_scale_y =
                (rsin((effect->wobble_phase.s << 8) + 0x600) >> 3) + 0x1000;
        } else if (effect_kind == 0) {
            effect->base_scale.s = 0;
        } else {
            effect->corner3_scale_y = 0x1000;
            effect->corner3_scale_x = 0x1000;
            effect->corner2_scale_y = 0x1000;
            effect->corner2_scale_x = 0x1000;
            effect->corner1_scale_y = 0x1000;
            effect->corner1_scale_x = 0x1000;
            effect->corner0_scale_y = 0x1000;
            effect->corner0_scale_x = 0x1000;
        }
    } else {
        scale_value = out_render->scale_x + 0x100;
        out_render->scale_x = scale_value;
        if (scale_value > 0x2000U) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        out_render->scale_y += 0x100;
    }
    effect->wobble_phase.u++;
}
