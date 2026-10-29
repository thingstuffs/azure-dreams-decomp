#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"

typedef struct S_80171FC8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171FC8_0;   /* arg3 in advance_entity_path_state */

typedef struct S_80171FC8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_2;   /* tile in advance_entity_path_state */

typedef struct S_80171FC8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_80171FC8_3;   /* arg0 in advance_entity_path_state */

typedef struct S_80171FC8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171FC8_4;   /* (u8 *)arg3 + ((S_80171FC8_0 *)arg3)->unk_8A.s in advance_entity_path_state */

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

extern u8 death_direction_frames[];

/* Advance the entity along its path and update its movement state. */
void advance_entity_path_state(ActorRecord *motion_state, ObjectPosition *unused, SpriteFrameState *entity, ActorRecord *path_state) {
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    u16 hp;
    u16 energy;
    u16 step_index;
    S_80171FC8_2 *path_entry;

    if (((S_80171FC8_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if ((s32)path_state->movement_queue_state <= path_state->unk_8A) {
        return;
    }

    if (*(u8 **)&entity->frameTable != death_direction_frames) {
        (entity->frameTable) = death_direction_frames;
        select_sprite_entry(entity,
                      death_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + path_state->facing + 0x100) >> 9) & 7],
                      0);
    }

    path_entry = (S_80171FC8_2 *)((u8 *)path_state + path_state->unk_8A);
    if (entity->tile_x == path_entry->unk_74 &&
        entity->tile_y == path_entry->unk_7C) {
        hp = motion_state->unk_90.parts.high.u;
        energy = ((S_80171FC8_0 *)path_state)->unk_88;
        motion_state->unk_90.parts.high.u = hp + 0x20;
        step_index = ((S_80171FC8_0 *)path_state)->unk_8A.u;
        path_state->ground_height = energy - 0x20;
        path_state->unk_8A = step_index + 1;
    } else {
        flags = path_state->flags1C;
        old_x = entity->tile_x;
        old_y = entity->tile_y;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        entity->tile_x = ((S_80171FC8_4 *)((u8 *)path_state
            + path_state->unk_8A))->unk_74;
        entity->tile_y = ((S_80171FC8_4 *)((u8 *)path_state
            + path_state->unk_8A))->unk_7C;
        ((S_80171FC8_0 *)path_state)->unk_8A.u += 1;

        cycle_map_cell_flags(entity->tile_x, entity->tile_y,
                      (path_state->flags1C & 0x2000) ? 0x300 : 0x3000);

        path_state->facing =
            get_rounded_facing_and_rounding_flag(old_x, old_y, entity->tile_x,
                          entity->tile_y, &motion_state->action_state_flags);
    }

    motion_state->action_id.s = 0xF;
    ((S_80171FC8_3 *)motion_state)->unk_8C = 0;
    path_state->flags1C |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        motion_state->action_timer.u = 0;
        return;
    }

    motion_state->action_timer.u = 8;
    step_count = path_state->movement_queue_state;
    if (step_count > 0) {
        motion_state->action_timer.u = 8 / step_count;
    }

    return;
}
