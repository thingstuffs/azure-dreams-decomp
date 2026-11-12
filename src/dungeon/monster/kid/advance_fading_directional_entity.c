#include "dungeon/level/unlink_entity_node_api.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/object.h"
#include "shared/object_node.h"

struct EntityLinkNode;



#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

   /* the 0x2 bytes before arg3 in advance_fading_directional_entity, addressed as arg3[-1] */





/* Advance an entity through directional motion, fading, and removal. */
void advance_fading_directional_entity(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity) {
    s32 sound_flags;
    s32 direction_x;
    s32 direction_y;
    s32 direction_offset;
    s32 status_flags;
    u16 next_brightness;
    u32 phase;
    u32 sound_x;
    u32 sound_y;
    u8 brightness;

    phase = body->action_phase;
    direction_offset = (((ActorRecord *)entity)->movement_facing >> 8) & 0xE;
    direction_x = dir_step_x[direction_offset >> 1];
    direction_y = dir_step_y[direction_offset >> 1];
    switch (phase) {
    case 0:
    {
        ActorRecord *entity_view = entity;
        u32 clear_bit_27 = 0xF7FFFFFF;
        u32 clear_bit_18;
        u32 entity_flags;
        u16 anim_flags;

        anim_flags = body->action_state_flags;
        clear_bit_18 = 0xFFFBFFFF;
        anim_flags |= 8;
        body->action_state_flags = anim_flags;
        entity_flags = ((u32)entity_view->flags1C);
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        entity_view->flags1C = entity_flags;
        motion->velocity_x = direction_x << 0x10;
        motion->velocity_y = direction_y << 0x10;
        motion->velocity_z = 0xFFF40000;
        play_sound_if_enabled(0x805);
        body->action_phase = body->action_phase + 1;
    }
    case 1:
        (motion->velocity_z) += 0x1C000;
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        body->action_phase = body->action_phase + 1;
    case 2:
        status_flags = ((ActorRecord *)entity)->flags14;
        if (status_flags & 0x4000) {
            if (!(status_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        sprite->tpage_abr = 0x60;
        sprite->flags |= 0xC;
        body->action_phase = body->action_phase + 1;
    case 3:
        motion->velocity_z += 0x1C000;
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        body->action_timer = 0x80U;
        body->action_phase = body->action_phase + 1;
        return;
    case 4:
    {
        ActorRecord *entity_view = entity;
        entity_view->flags1C |= 0x10000000;
        motion->velocity_z += 0x20000;
        brightness = body->action_timer;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
        next_brightness = body->action_timer - 0x18;
        body->action_timer = next_brightness;
        if ((s16)next_brightness >= 0x18) {
            return;
        }
        if (((s32)g_dungeon_status.pending_display_owner) == (entity - 0x20)) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        sound_x = sprite->tile_x;
        sound_y = sprite->tile_y;
        sound_flags = 0x3000;
        if (entity_view->flags1C & 0x2000) {
            sound_flags = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_flags);
        unlink_entity_node(entity);
        NODE_HEADER(entity)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    default:
        return;
    }
}
