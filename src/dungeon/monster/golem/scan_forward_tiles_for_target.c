
struct ObjectPosition;
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/monster/golem.h"

typedef struct S_80172504_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_80172504_0;   /* entity in scan_forward_tiles_for_target */

typedef struct S_80172504_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    s16 unk_AA;
    s16 unk_AC;
    u8 unk_AE;
} S_80172504_1;   /* state in scan_forward_tiles_for_target */

typedef struct S_80172504_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172504_2;   /* (void *)scratch in scan_forward_tiles_for_target */


extern s32 find_eligible_entry_at_coordinates();
extern void prepare_directional_attack();
extern s32 try_claim_dungeon_action_slot();
extern s32 check_layer_offset_height();
extern void advance_status_timers();
extern s16 sample_terrain_surface_height();
extern void select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);
extern void apply_camera_offset_and_select_target();


/* Scan up to eight tiles ahead for a valid target and update the entity action state. */
s32 scan_forward_tiles_for_target(void *action_state, void *transfer_data, void *origin, void *actor) {
    u32 dir_index;
    u16 initial_direction;
    s16 *delta_x;
    s16 *delta_y;
    s32 step_count;
    u16 tile_x;
    u16 tile_y;
    s32 signed_x;
    s32 signed_y;
    s32 direction_offset;
    s32 check_result;
    s32 world_x;
    s32 next_world_x;
    s32 world_y;
    void *copy_dest;
    s16 next_height;
    u16 direction;

    ((S_80172504_0 *)actor)->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(((S_80172504_0 *)actor)->unk_46 & 0x8000) && (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, transfer_data, 8, 0x300);
    check_result = try_claim_dungeon_action_slot(actor);
    step_count = 0;
    if ((check_result << 16) != 0) {
        return -1;
    }

    dir_index = (((S_80172504_0 *)actor)->unk_2A.s >> 9) & 7;
    direction_offset = dir_index * 2;
    tile_x = ((S_80172504_2 *)origin)->unk_24;
    tile_y = ((S_80172504_2 *)origin)->unk_25;
    delta_x = (s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    direction = dir_index;
    ((S_80172504_1 *)action_state)->unk_A8 = tile_x;
    ((S_80172504_1 *)action_state)->unk_AA = tile_y;

    do {
        delta_x = (s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
        signed_x = (s16)tile_x;
        world_x = (signed_x << 6) & 0xFFC0;
        signed_y = (s16)tile_y;
        world_y = (signed_y << 6) & 0xFFC0;
        if ((check_layer_offset_height(world_x,
                           world_y,
                           ((S_80172504_0 *)actor)->unk_88.s, direction << 9) << 16) != 0) {
            break;
        }

        next_world_x = (((signed_x + *delta_x) << 6) + 0x20) & 0xFFE0;
        delta_y = (s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
        next_height = sample_terrain_surface_height(
            next_world_x,
            (((signed_y + *delta_y) << 6) + 0x20) & 0xFFE0,
            (s16)(((S_80172504_0 *)actor)->unk_88.u - 0x20));
        if (next_height >= 0x201) {
            break;
        }
        if ((u16)(next_height - ((S_80172504_0 *)actor)->unk_88.u + 0x3F) >= 0x7F) {
            break;
        }

        {
            s32 step_x;
            u32 step_y;

            step_x = (u16)*delta_x;
            step_y = (u16)*delta_y;
            step_x = (u16)(tile_x + step_x);
            step_y = (u16)(tile_y + step_y);
            check_result = find_eligible_entry_at_coordinates(actor, step_x, step_y);
        }
        if (check_result != 0) {
            ((S_80172504_1 *)action_state)->unk_AE = 2;
            ((S_80172504_1 *)action_state)->unk_AC = step_count + 1;
            ((S_80172504_0 *)actor)->unk_60 = check_result;
            break;
        }
        {
            u16 next_y;

            step_count++;
            initial_direction = (u32)(tile_x + (u16)*delta_x);
            tile_x = (s32)initial_direction;
            next_y = tile_y + (u16)*delta_y;
            tile_y = next_y;
            ((S_80172504_1 *)action_state)->unk_AA = next_y;
            ((S_80172504_1 *)action_state)->unk_A8 = (s32)initial_direction;
        }
    } while (step_count < 8);

    ((S_80172504_1 *)action_state)->unk_9A = 0x1A;
    ((S_80172504_1 *)action_state)->unk_9B = 0;
    ((S_80172504_1 *)action_state)->unk_8C = 0;
    ((S_80172504_1 *)action_state)->unk_96 = 8;
    ((S_80172504_0 *)actor)->unk_84 = 0x7E;
    ((S_80172504_0 *)actor)->unk_85 = 8;
    advance_status_timers(actor);
    ((S_80172504_0 *)actor)->unk_6D--;
    copy_dest = (u8 *)actor - 0x20;
    if (((S_80172504_1 *)action_state)->unk_AE == 2) {
        prepare_directional_attack(actor, origin, ((S_80172504_0 *)actor)->unk_2A.u,
                      (s16)(step_count + 1), ((S_80172504_0 *)actor)->unk_60);
    } else {
        select_nearby_target_and_initialize_slot(copy_dest, transfer_data, 8, 0x300);
    }
    return 0;
}
