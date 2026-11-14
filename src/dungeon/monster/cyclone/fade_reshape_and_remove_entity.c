#include "dungeon/level/unlink_entity_node_api.h"
#include "shared/actor_status_ids.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor.h"
#include "engine/entity.h"
#include "dungeon/effect.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"

#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"


/* Fades and reshapes the sprite, then removes the entity when the effect ends. */
void fade_reshape_and_remove_entity(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity)
{
    u8 fade_phase;
    u16 frames_left;

    fade_phase = body->action_phase;
    switch (fade_phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }

        body->action_phase = 1;
        sprite->tpage_abr = 0x20;
        sprite->clut -= 0x80;
        sprite->flags |= 0xC;
        entity->flags1C |= 0x10000000;
        play_sound_if_enabled(0x805);
        sprite->color.word = 0x00808080;
        body->action_timer = 0xC;
    case 1:
        break;
    default:
        return;
    }

    sprite->color.c.r -= sprite->color.c.r / body->action_timer;
    sprite->color.c.g -= sprite->color.c.g / body->action_timer;
    sprite->color.c.b -= sprite->color.c.b / body->action_timer;

    sprite->scale_x >>= 2;
    sprite->scale_y >>= 1;
    sprite->scale_x *= 3;
    sprite->scale_y *= 3;

    frames_left = body->action_timer - 1;
    body->action_timer = frames_left;
    if (((s32)frames_left << 16) > 0) {
        if ((sprite->flags & 0x8000) == 0) {
            return;
        }
    }

    if ((((u32)entity->flags14) & 0x20000000) == 0) {
        DungeonGlobalStatus *entity_tracker = &g_dungeon_status;
        if (entity_tracker->pending_display_owner == NODE_HEADER(entity)) {
            (*(u32 *)&entity_tracker->pending_display_owner) &= 0x7FFFFFFF;
        }
    }

    if ((((u32)entity->flags14) & ACTOR_PARTY_MEMBER) == 0) {
        distribute_experience_and_report_gains((EntityRec *)entity);
        detach_record_and_update_slot_state(entity);
        if (entity->unk_49 != 0 &&
            (entity->unk_4B & 0x20) == 0) {
            create_item_drop_effect(position->x.w.i, position->y.w.i,
                          entity->ground_height, (u8 *)entity + 0x48);
        }
        if ((get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 16) == 0) {
            s32 entity_flags = ((u32)entity->flags1C);
            s32 effect_color_0 = sprite->tile_x;
            s32 effect_color_1 = sprite->tile_y;
            s32 effect_mask = 0x3000;
            if (entity_flags & 0x2000) {
                effect_mask = 0x300;
            }
            update_map_cell_flags_with_item_limit(effect_color_0, effect_color_1, effect_mask);
        }
        unlink_entity_node((struct EntityLinkNode *)entity);
        (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    if ((((u32)entity->flags14) & 0x20000000) == 0) {
        announce_familiar_defeat(entity);
    }
    distribute_experience_and_report_gains((EntityRec *)entity);
    detach_record_and_update_slot_state(entity);
    if ((get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 16) == 0) {
        s32 entity_flags = ((u32)entity->flags1C);
        s32 effect_color_0 = sprite->tile_x;
        s32 effect_color_1 = sprite->tile_y;
        s32 effect_mask = 0x3000;
        if (entity_flags & 0x2000) {
            effect_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(effect_color_0, effect_color_1, effect_mask);
    }
    unlink_entity_node((struct EntityLinkNode *)entity);
    (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    play_sound_if_enabled(0x609);
}
