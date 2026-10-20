#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"


extern s32 select_sprite_entry();
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s32 check_movement_clearance_and_height();
extern s16 get_rounded_facing_and_rounding_flag();
extern s32 func_8016C698();

extern u8 D_80174674[];


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

typedef struct S_8016BD14_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8016BD14_2;   /* arg1 in advance_entity_along_path */


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
void advance_entity_along_path(void *actor, void *action, void *entity, void *path_arg) {
    register void *path;
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

    if (((S_8016BD14_0 *)path)->unk_71.s <= 0) {
        return;
    }

    move_state = 15;
    if (((S_8016BD14_1 *)actor)->unk_9A != move_state) {
        ((S_8016BD14_1 *)actor)->unk_90 = 0;
        ((S_8016BD14_2 *)action)->unk_14 = 0;
        ((S_8016BD14_1 *)actor)->unk_9D = 0;
    }

    if (((S_8016BD14_0 *)path)->unk_71.u <= ((S_8016BD14_0 *)path)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != D_80174674) {
        (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8) = D_80174674;
        select_sprite_entry(
            entity,
            D_80174674[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016BD14_0 *)path)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_tile_flags = ((S_8016BD14_0 *)path)->unk_1C;
    tile_x = ((Rec_D_80082E80 *)entity)->unk_24;
    tile_y = ((Rec_D_80082E80 *)entity)->unk_25;
    old_tile_flags = old_tile_flags & 0x2000;
    update_map_cell_flags_with_item_limit(tile_x, tile_y, old_tile_flags ? 0x300 : 0x3000);

    heading = get_rounded_facing_and_rounding_flag(tile_x, tile_y,
                            ((S_8016BD14_5 *)((u8 *)path + ((S_8016BD14_0 *)path)->unk_8A.s))->unk_74,
                            ((S_8016BD14_5 *)((u8 *)path + ((S_8016BD14_0 *)path)->unk_8A.s))->unk_7C,
                            (u8 *)actor + 0x98);
    raw_result = check_movement_clearance_and_height(heading, entity, path, 0x20);

    next_x = ((S_8016BD14_5 *)((u8 *)path + ((S_8016BD14_0 *)path)->unk_8A.s))->unk_74;
    raw_result = raw_result << 16;
    ((Rec_D_80082E80 *)entity)->unk_24 = next_x;
    step = (u8 *)path + ((S_8016BD14_0 *)path)->unk_8A.s;
    move_result = raw_result >> 16;
    do {
        ((Rec_D_80082E80 *)entity)->unk_25 = ((S_8016BD14_4 *)step)->unk_7C;
        step_index = ((S_8016BD14_0 *)path)->unk_8A.u;
    } while (0);
    new_tile_flags = ((S_8016BD14_0 *)path)->unk_1C;
    step_index = step_index + 1;
    new_tile_flags = new_tile_flags & 0x2000;
    ((S_8016BD14_0 *)path)->unk_8A.u = step_index;
    cycle_map_cell_flags(((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25,
                  new_tile_flags ? 0x300 : 0x3000);
    ((S_8016BD14_0 *)path)->unk_2A = heading;

    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            func_8016C698(actor, action, entity, path);
        } else {
            ((S_8016BD14_1 *)actor)->unk_9A = 15;
        }
    } else {
        ((S_8016BD14_1 *)actor)->unk_9A = move_state;
    }

    ((S_8016BD14_1 *)actor)->unk_8C = 0;
    ((S_8016BD14_0 *)path)->unk_1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((S_8016BD14_1 *)actor)->unk_96 = 0;
        return;
    }

    ((S_8016BD14_1 *)actor)->unk_96 = 8;
    tile_x = ((S_8016BD14_0 *)path)->unk_71.u;
    if (tile_x > 0) {
        ((S_8016BD14_1 *)actor)->unk_96 = 8 / tile_x;
    }
}
