#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/monster/ghosh.h"

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 check_movement_clearance_and_height();
extern void func_8016C698(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation);

extern u8 ghosh_frame_set_7[];

typedef struct S_8016BD14_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8016BD14_0;   /* ctx in advance_entity_along_path */

typedef struct S_8016BD14_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x2];
    u8 unk_9D;
} S_8016BD14_1;   /* arg0 in advance_entity_along_path */

typedef struct S_8016BD14_4 {
    u8 pad_00[0x7C];
    u8 unk_7C;
} S_8016BD14_4;   /* row in advance_entity_along_path */

typedef struct S_8016BD14_5 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016BD14_5;   /* (u8 *)ctx + ((S_8016BD14_0 *)ctx)->unk_8A.s in advance_entity_along_path */

/* Advance the entity along its path and update its heading and movement state. */
void advance_entity_along_path(void *actor, ObjectPosition *position, SpriteFrameState *sprite, void *path_arg) {
    ActorRecord *path_actor = actor;
    register S_8016BD14_0 *path;
    s32 step_index;
    s32 old_tile_flags;
    s16 heading;
    s32 move_result;
    s32 raw_result;
    u8 *step;
    s32 new_tile_flags;
    s32 tile_x;
    s32 tile_y;
    s32 move_state;
    s32 next_x;

    path = path_arg;

    if (path->unk_71.s <= 0) {
        return;
    }

    move_state = 15;
    if (((S_8016BD14_1 *)actor)->unk_9A != move_state) {
        ((S_8016BD14_1 *)actor)->unk_90 = 0;
        position->velocity_z = 0;
        ((S_8016BD14_1 *)actor)->unk_9D = 0;
    }

    if (path->unk_71.u <= path->unk_8A.s) {
        return;
    }

    if (*(u8 **)&sprite->frameTable != ghosh_frame_set_7) {
        (sprite->frameTable) = ghosh_frame_set_7;
        select_sprite_entry(
            sprite,
            ghosh_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + path->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_tile_flags = path->unk_1C;
    tile_x = sprite->tile_x;
    tile_y = sprite->tile_y;
    old_tile_flags = old_tile_flags & 0x2000;
    update_map_cell_flags_with_item_limit(tile_x, tile_y, old_tile_flags ? 0x300 : 0x3000);

    heading = get_rounded_facing_and_rounding_flag(tile_x, tile_y,
                            ((S_8016BD14_5 *)((u8 *)path + path->unk_8A.s))->unk_74,
                            ((S_8016BD14_5 *)((u8 *)path + path->unk_8A.s))->unk_7C,
                            &path_actor->action_state_flags);
    raw_result = check_movement_clearance_and_height(heading, sprite, path, 0x20);

    next_x = ((S_8016BD14_5 *)((u8 *)path + path->unk_8A.s))->unk_74;
    raw_result = raw_result << 16;
    sprite->tile_x = next_x;
    step = (u8 *)path + path->unk_8A.s;
    move_result = raw_result >> 16;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_81324514). */
    do {
        sprite->tile_y = ((S_8016BD14_4 *)step)->unk_7C;
        step_index = path->unk_8A.u;
    } while (0);
    new_tile_flags = path->unk_1C;
    step_index = step_index + 1;
    new_tile_flags = new_tile_flags & 0x2000;
    path->unk_8A.u = step_index;
    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  new_tile_flags ? 0x300 : 0x3000);
    path->unk_2A = heading;

    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(sprite->flags & 0x8000)) {
            func_8016C698(actor, position, sprite, path);
        } else {
            ((S_8016BD14_1 *)actor)->unk_9A = 15;
        }
    } else {
        ((S_8016BD14_1 *)actor)->unk_9A = move_state;
    }

    ((S_8016BD14_1 *)actor)->unk_8C = 0;
    path->unk_1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((S_8016BD14_1 *)actor)->unk_96 = 0;
        return;
    }

    ((S_8016BD14_1 *)actor)->unk_96 = 8;
    tile_x = path->unk_71.u;
    if (tile_x > 0) {
        ((S_8016BD14_1 *)actor)->unk_96 = 8 / tile_x;
    }
}
