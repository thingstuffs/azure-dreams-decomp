#include "shared/actor_status_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"




void unlink_entity_node(void *node);
void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 flag_mask);
void * detach_record_and_update_slot_state(void *record);
s32 get_entity_effect_value(void *entry, s32 effect_id);

/* Fade the entity to dark gray, then remove it and update its tile flags. */
s32 fade_actor_to_removal(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *visual, ActorRecord *entity) {

    s16 fade_frames;
    s32 tile_flags;
    s16 frames_left;
    s32 entity_ref;
    u8 blue;
    u8 phase;
    u8 red;
    u8 green;
    u8 tile_x;
    u8 tile_y;

    phase = state->action_phase.u;
    switch (phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return 0;
        }
        visual->tpage_abr = 0x20;
        visual->clut = (u16) (visual->clut - 0x80);
        visual->flags = (u16) (visual->flags | 0xC);
        entity->flags1C = (s32) (entity->flags1C | 0x10000000);
        play_sound_if_enabled(0x805);
        visual->color.word = 0x808080;
        state->action_timer.s = 0x10;
        state->action_phase.u = (u8) (state->action_phase.u + 1);
    case 1:
        break;
    default:
        return 0;
    }
    red = visual->color.c.r;
    fade_frames = state->action_timer.s;
    visual->color.c.r = (u8) (red + ((s32) (0x20 - red) / fade_frames));
    green = visual->color.c.g;
    blue = visual->color.c.b;
    fade_frames = state->action_timer.s;
    visual->color.c.g = (u8) (green + ((s32) (0x20 - green) / fade_frames));
    visual->color.c.b = (u8) (blue + ((s32) (0x20 - blue) / (s16) state->action_timer.s));
    frames_left = (u16) state->action_timer.s - 1;
    state->action_timer.s = frames_left;
    if (!(((frames_left << 0x10) > 0) && ((visual->flags & 0x8000) == 0))) {
        entity_ref = ((s32)g_dungeon_status.pending_display_owner);
        if (entity_ref == NODE_HEADER(entity)) {
            g_dungeon_status.pending_display_owner = (s32) (entity_ref & 0x7FFFFFFF);
        }
        detach_record_and_update_slot_state(entity);
        if ((get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 0x10) == 0) {
            tile_x = visual->tile_x;
            tile_y = visual->tile_y;
            tile_flags = 0x3000;
            if (entity->flags1C & ACTOR_PLAYER_SIDE) {
                tile_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_flags);
        }
        unlink_entity_node(entity);
        NODE_HEADER(entity)->flags = (u16) (NODE_HEADER(entity)->flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return 1;
    }
    return 0;
}
