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
    if (effect->unk_1E == 0) {
        if (*effect->unk_08 & 1) {
            target_scale = 0x1400;
        }

        owner_base = effect->unk_0C;
        owner = NODE_BODY(owner_base);
        if ((((u32)owner->flags1C) & 0x00800000) ||
            (owner_base->flags & 0x8000) ||
            (owner->unk_8C.address == (void *)transfer_linked_object_state) ||
            ((get_entity_effect_value(owner, STATUS_FROG) << 16) != 0)) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }

        if (((s8)owner->unk_87) != -1) {
            MovingPosition *sample_position = (MovingPosition *)effect->unk_18;

            sampled_height = sample_terrain_surface_height(sample_position->x,
                                sample_position->y,
                                (s16)(sample_position->z - 4));
        } else {
            sampled_height = effect->unk_18->z.unsigned_parts.integer;
        }

        source_position = effect->unk_18;
        height_scale = height_scale - ((sampled_height - source_position->z.unsigned_parts.integer) << 6);
        if (height_scale < 0) {
            height_scale = 0;
        }
        if (height_scale >= 0x1801) {
            height_scale = 0;
        }

        if (height_scale >= 0xF81) {
            out_position->x = source_position->x.unsigned_parts.integer;
            out_position->y = effect->unk_18->y.unsigned_parts.integer;
            out_position->z = sampled_height;

            scale_cap = target_scale;
            if (scale_cap == 0x1000) {
                scale_value = effect->unk_1C.u;
                if (effect->unk_1C.s >= 0x1001) {
                    next_scale = scale_value - 0x400;
                    effect->unk_1C.s = next_scale;
                    if (next_scale < 0x1000) {
                        effect->unk_1C.s = scale_cap;
                    }
                } else {
                    next_scale = scale_value + 0x400;
                    effect->unk_1C.s = next_scale;
                    if (next_scale >= 0x1001) {
                        effect->unk_1C.s = scale_cap;
                    }
                }
            } else {
                next_scale = effect->unk_1C.u + 0x800;
                effect->unk_1C.s = next_scale;
                if (scale_cap < next_scale) {
                    effect->unk_1C.s = target_scale;
                }
            }
        } else {
            next_scale = effect->unk_1C.u - 0x400;
            effect->unk_1C.s = next_scale;
            if (next_scale < 0) {
                effect->unk_1C.s = 0;
            }
        }

        out_render->clut = effect->unk_14->clut;
        out_render->color.word = effect->unk_14->color.word;
        out_render->scale_x = effect->unk_1C.u +
            (rcos(effect->unk_20.s << 8) >> 4);
        out_render->scale_y = effect->unk_1C.u +
            (rsin(effect->unk_20.s << 8) >> 4);

        effect_kind = *effect->unk_04;
        if (effect_kind == 0xF) {
            effect->unk_22 =
                (rcos(effect->unk_20.s << 8) >> 3) + 0x1000;
            effect->unk_24 =
                (rsin(effect->unk_20.s << 8) >> 3) + 0x1000;
            effect->unk_26 =
                (rcos((effect->unk_20.s << 8) + 0x200) >> 3) + 0x1000;
            effect->unk_28 =
                (rsin((effect->unk_20.s << 8) + 0x200) >> 3) + 0x1000;
            effect->unk_2A =
                (rcos((effect->unk_20.s << 8) + 0x400) >> 3) + 0x1000;
            effect->unk_2C =
                (rsin((effect->unk_20.s << 8) + 0x400) >> 3) + 0x1000;
            effect->unk_2E =
                (rcos((effect->unk_20.s << 8) + 0x600) >> 3) + 0x1000;
            effect->unk_30 =
                (rsin((effect->unk_20.s << 8) + 0x600) >> 3) + 0x1000;
        } else if (effect_kind == 0) {
            effect->unk_1C.s = 0;
        } else {
            effect->unk_30 = 0x1000;
            effect->unk_2E = 0x1000;
            effect->unk_2C = 0x1000;
            effect->unk_2A = 0x1000;
            effect->unk_28 = 0x1000;
            effect->unk_26 = 0x1000;
            effect->unk_24 = 0x1000;
            effect->unk_22 = 0x1000;
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
    effect->unk_20.u++;
}
