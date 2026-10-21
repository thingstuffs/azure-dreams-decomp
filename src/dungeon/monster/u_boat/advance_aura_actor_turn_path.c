#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern s32 get_entity_effect_value();
extern void select_sprite_entry();
extern void cycle_map_cell_flags();
extern void update_map_cell_flags_with_item_limit();
extern s16 check_movement_clearance_and_height();
extern s16 get_rounded_facing_and_rounding_flag();
extern void create_owner_linked_directional_object();
extern void advance_arcing_actor_move();
extern u8 uboat_default_frames[];


typedef struct S_80172144_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_80172144_0;   /* state in advance_aura_actor_turn_path */

typedef struct S_80172144_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x15];
    u8 unk_B0;
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80172144_1;   /* arg0 in advance_aura_actor_turn_path */

typedef struct S_80172144_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 ** unk_2C;
} S_80172144_2;   /* entity in advance_aura_actor_turn_path */

typedef struct S_80172144_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_3;   /* temp_v0_2 in advance_aura_actor_turn_path */

typedef struct S_80172144_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_4;   /* (u8 *)state + ((S_80172144_0 *)state)->unk_8A in advance_aura_actor_turn_path */

/* Advance the entity along its path and update its movement state. */
void advance_aura_actor_turn_path(void *actor, s32 actor_slot, void *entity_arg, void *state_arg) {
    register void *state = state_arg;
    register void *entity = entity_arg;
    s32 tile_flags;
    s16 direction;
    s16 move_result;
    s32 effect_status;
    s16 old_x_early;
    s16 old_x;
    s16 old_y;
    s32 step_count;
    S_80172144_3 *path_step;

    if ((((S_80172144_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_80172144_0 *)state)->unk_71.u > ((S_80172144_0 *)state)->unk_8A)) {
        if ((((S_80172144_1 *)actor)->unk_B5 == 0) &&
            (((S_80172144_2 *)entity)->unk_2C != uboat_default_frames)) {
            ((S_80172144_2 *)entity)->unk_2C = uboat_default_frames;
            select_sprite_entry(entity,
                uboat_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172144_0 *)state)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_80172144_1 *)actor)->unk_B0 == 0) {
                create_owner_linked_directional_object(actor, actor_slot, entity);
            }
        }
        old_x_early = ((S_80172144_2 *)entity)->unk_24;
        old_y = ((S_80172144_2 *)entity)->unk_25;
        effect_status = get_entity_effect_value(state, 0x1B);
        old_x = old_x_early;
        if ((effect_status << 0x10) == 0) {
            s32 tile_x;
            s32 tile_y;
            s32 flags;
            s32 mode;

            tile_x = old_x;
            mode = 0x3000;
            flags = ((S_80172144_0 *)state)->unk_1C;
            tile_y = old_y;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, mode);
        }
        path_step = (u8 *)state + ((S_80172144_0 *)state)->unk_8A;
        direction = get_rounded_facing_and_rounding_flag(old_x, old_y,
            path_step->unk_74, path_step->unk_7C,
            (u8 *)actor + 0x98);
        move_result = check_movement_clearance_and_height(direction, entity, state, 0x20);
        ((S_80172144_2 *)entity)->unk_24 = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_74;
        ((S_80172144_2 *)entity)->unk_25 = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_7C;
        ((S_80172144_0 *)state)->unk_8A = (u16)((S_80172144_0 *)state)->unk_8A + 1;
        if ((effect_status << 0x10) == 0) {
            s32 new_x;
            s32 new_y;

            tile_flags = 0x3000;
            new_x = ((S_80172144_2 *)entity)->unk_24;
            new_y = ((S_80172144_2 *)entity)->unk_25;
            if (((S_80172144_0 *)state)->unk_1C & 0x2000) {
                tile_flags = 0x300;
            }
            cycle_map_cell_flags(new_x, new_y, tile_flags);
        }
        ((S_80172144_0 *)state)->unk_2A = direction;
        if (move_result == 3 && (((S_80172144_1 *)actor)->unk_B5 == 0) && !(g_dungeon_status.flags & 0x80) &&
            !(((S_80172144_2 *)entity)->unk_14 & 0x8000)) {
            advance_arcing_actor_move(actor, actor_slot, entity, state);
            ((S_80172144_1 *)actor)->unk_8C = 0;
            ((S_80172144_0 *)state)->unk_1C |= 0x40000000;
        } else {
            ((S_80172144_1 *)actor)->unk_9A = 0xF;
            ((S_80172144_1 *)actor)->unk_8C = 0;
            ((S_80172144_0 *)state)->unk_1C |= 0x40000000;
        }
        if (g_dungeon_status.flags & 0x80) {
            ((S_80172144_1 *)actor)->unk_96 = 0;
            return;
        }
        ((S_80172144_1 *)actor)->unk_96 = 8;
        step_count = ((S_80172144_0 *)state)->unk_71.u;
        if ((s32)step_count > 0) {
            ((S_80172144_1 *)actor)->unk_96 = 8 / (s32)step_count;
        }
    }
}
