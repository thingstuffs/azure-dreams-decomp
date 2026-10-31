#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/object_links.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/player/object.h"

struct EntityLinkNode;



void unlink_entity_node(struct EntityLinkNode *node);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void * detach_record_and_update_slot_state(void *record);
s16 sample_terrain_surface_height();



   /* the 0x2 bytes before arg3 in advance_entity_motion_fade_and_removal, addressed as arg3[-1] */

typedef struct S_801731FC_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_801731FC_1;   /* arg3 in advance_entity_motion_fade_and_removal */

typedef struct S_801731FC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801731FC_2;   /* arg1 in advance_entity_motion_fade_and_removal */


/* Advance an entity through motion, fading, and removal. */
void advance_entity_motion_fade_and_removal(ActorRecord *state, S_801731FC_2 *motion, SpriteFrameState *sprite, void *entity) {
    s32 sound_flags;
    s32 velocity_x;
    s32 velocity_y;
    s32 direction_offset;
    s32 status_flags;
    u16 next_brightness;
    u32 phase;
    u32 sound_x;
    u32 sound_y;
    u8 brightness;

    phase = state->action_phase.u;
    direction_offset = ((u16) ((S_801731FC_1 *)entity)->unk_6A >> 8) & 0xE;
    velocity_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    velocity_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    switch (phase) {
    case 0:
    {
        u32 clear_bit_27 = 0xF7FFFFFF;
        u32 clear_bit_18;
        u32 entity_flags;
        u16 state_flags;

        state_flags = state->action_state_flags;
        clear_bit_18 = 0xFFFBFFFF;
        state_flags |= 8;
        state->action_state_flags = state_flags;
        entity_flags = ((S_801731FC_1 *)entity)->unk_1C.u;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        ((S_801731FC_1 *)entity)->unk_1C.u = entity_flags;
        motion->unk_0C = velocity_x << 0x10;
        motion->unk_10 = velocity_y << 0x10;
        motion->unk_14 = 0xFFF40000;
        state->action_phase.u = state->action_phase.u + 1;
    }
    case 1:
        motion->unk_14 += 0x1C000;
        if (sample_terrain_surface_height(motion->unk_02, motion->unk_06, motion->unk_0A) >= 0x200) {
            motion->unk_14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        state->action_phase.u = state->action_phase.u + 1;
    case 2:
        status_flags = ((S_801731FC_1 *)entity)->unk_14;
        if (status_flags & 0x4000) {
            if (!(status_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;
        sprite->clut -= 0x80;
        state->action_phase.u = state->action_phase.u + 1;
    case 3:
        motion->unk_14 += 0x1C000;
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        state->action_timer.u = 0x80U;
        state->action_phase.u = state->action_phase.u + 1;
        return;
    case 4:
        ((S_801731FC_1 *)entity)->unk_1C.s |= 0x10000000;
        brightness = (u8)state->action_timer.u;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
        next_brightness = state->action_timer.u - 0x18;
        state->action_timer.u = next_brightness;
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
        if (((S_801731FC_1 *)entity)->unk_1C.s & 0x2000) {
            sound_flags = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_flags);
        unlink_entity_node(entity);
        ((ObjectRetirementFlags *)entity)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}
