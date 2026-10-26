#include "shared/actor_status_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_800D1A80_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D1A80_0;   /* arg0 in fade_actor_to_removal */

typedef struct S_800D1A80_1 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D1A80_1;   /* arg2 in fade_actor_to_removal */

typedef struct S_800D1A80_2_pre {
    u16 unk_00;
} S_800D1A80_2_pre;   /* the 0x2 bytes before arg3 in fade_actor_to_removal, addressed as arg3[-1] */


typedef struct S_800D1A80_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D1A80_3;

void unlink_entity_node(void *node);
void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 flag_mask);
void * detach_record_and_update_slot_state(void *record);
void play_sound_if_enabled(s32 query_value);
s32 get_entity_effect_value(void *entry, s32 effect_id);

/* Fade the entity to dark gray, then remove it and update its tile flags. */
s32 fade_actor_to_removal(S_800D1A80_0 *state, void *unused, S_800D1A80_1 *visual, void *entity) {
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

    phase = state->unk_9B;
    switch (phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return 0;
        }
        visual->unk_10 = 0x20;
        visual->unk_12 = (u16) (visual->unk_12 - 0x80);
        visual->unk_14 = (u16) (visual->unk_14 | 0xC);
        ((ActorRecord *)entity)->flags1C = (s32) (((ActorRecord *)entity)->flags1C | 0x10000000);
        play_sound_if_enabled(0x805);
        visual->unk_0C.at00.v = 0x808080;
        state->unk_96 = 0x10;
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 1:
        break;
    default:
        return 0;
    }
    red = visual->unk_0C.at00u.v;
    fade_frames = state->unk_96;
    visual->unk_0C.at00u.v = (u8) (red + ((s32) (0x20 - red) / fade_frames));
    green = visual->unk_0C.at01.v;
    blue = visual->unk_0C.at02.v;
    fade_frames = state->unk_96;
    visual->unk_0C.at01.v = (u8) (green + ((s32) (0x20 - green) / fade_frames));
    visual->unk_0C.at02.v = (u8) (blue + ((s32) (0x20 - blue) / (s16) state->unk_96));
    frames_left = (u16) state->unk_96 - 1;
    state->unk_96 = frames_left;
    if (!(((frames_left << 0x10) > 0) && ((visual->unk_14 & 0x8000) == 0))) {
        entity_ref = ((s32)g_dungeon_status.pending_display_owner);
        if (entity_ref == (entity - 0x20)) {
            g_dungeon_status.pending_display_owner = (s32) (entity_ref & 0x7FFFFFFF);
        }
        detach_record_and_update_slot_state(entity);
        if ((get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 0x10) == 0) {
            tile_x = visual->unk_24;
            tile_y = visual->unk_25;
            tile_flags = 0x3000;
            if (((ActorRecord *)entity)->flags1C & ACTOR_PLAYER_SIDE) {
                tile_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_flags);
        }
        unlink_entity_node(entity);
        ((S_800D1A80_2_pre *)entity)[-1].unk_00 = (u16) (((S_800D1A80_2_pre *)entity)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return 1;
    }
    return 0;
}
