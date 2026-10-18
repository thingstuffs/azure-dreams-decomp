#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8008C13C_2 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8008C13C_2;   /* arg0 in try_move_carrying_player */


extern u8 D_8008EAC8[];
extern u8 D_800DCFD8[8];
extern u8 D_800DD0B8[8];

extern void func_80048A44(void *, s32, s32, s32);
extern void check_tile_entry_at_adjusted_height(void *, s32, void *, void *);
extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern s16 classify_adjacent_tile_height(s16, s32, void *, s16, s32);
extern void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);
extern s32 check_action_available_without_nearby_actor(void);
extern void clear_pending_item_action_state(void);


/* Synthetic batch key: func_800869DC; true rowbase link symbol: try_move_carrying_player. */
/* Attempts a move and updates the actor position, animation, and movement state. */
void try_move_carrying_player(void *controller, s32 actor_id, void *actor, EntityRec *actor_data) {
    GameWork *dungeon_state;
    s16 move_result;
    u8 direction_index;
    u8 tile_x;
    u8 *x_offsets;

    dungeon_state = &g_game_work;
    move_result = classify_adjacent_tile_height(actor_data->facing, actor_id, actor,
                           actor_data->unk_88, 0x20);

    if (move_result > 0) {
        update_map_cell_flags_with_item_limit(((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25, 0x300);

        direction_index = ((u16)actor_data->facing >> 8) & 0xE;
        x_offsets = ((u8 *)dir_step_x);
        tile_x = ((Rec_D_80082E80 *)actor)->unk_24;
        tile_x += x_offsets[direction_index];
        ((Rec_D_80082E80 *)actor)->unk_24 = tile_x;
        ((Rec_D_80082E80 *)actor)->unk_25 += ((u8 *)dir_step_y)[direction_index];

        cycle_map_cell_flags(((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25, 0x300);

        g_dungeon_status.flags |= 8;
        ((S_8008C13C_2 *)controller)->unk_8C.s = 0;

        if (move_result != 4) {
            if (D_80013714 & 2) {
                g_dungeon_status.flags |= 0x80;
            } else if ((dungeon_state->buttons & 0x20) && check_action_available_without_nearby_actor()) {
                g_dungeon_status.flags |= 0x80;
            }
        }

        if ((g_dungeon_status.flags & 0x80) || (move_result == 1)) {
            if (((Rec_D_80082E80 *)actor)->unk_2C.as_pv != D_800DCFD8) {
                (*(void * *)((u8 *)actor + 0x2C)) = D_800DCFD8;
                direction_index = ((g_game_work.view.viewAngle + actor_data->facing + 0x100) >> 9) & 7;
                func_80048A44(actor, D_800DCFD8[direction_index], 0, 1);
            }
            process_unflagged_linked_entries_alt(actor_data->unk_5C);
            process_unflagged_linked_entries(actor_data->unk_5C);
            g_dungeon_status.unk_04 = 8;
            ((S_8008C13C_2 *)controller)->unk_9A = 0x1D;
        } else {
            ((S_8008C13C_2 *)controller)->unk_98 |= 0xC;
            ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x4000;
            check_tile_entry_at_adjusted_height(controller, actor_id, actor, actor_data);
            if (move_result == 2) {
                ((S_8008C13C_2 *)controller)->unk_9B = 8;
            }
            g_dungeon_status.unk_04 = 8;
            ((S_8008C13C_2 *)controller)->unk_9A = 0x1E;
            actor_data->flags1C |= 0x40000000;
            append_packed_action_record(actor_data, 8, 0, 0);
            return;
        }

        append_packed_action_record(actor_data, 8, 0, 0);
    } else {
        ((Rec_D_80082E80 *)actor)->unk_2C.as_pv = D_800DD0B8;
        direction_index = ((dungeon_state->view.viewAngle + actor_data->facing + 0x100) >> 9) & 7;
        func_80048A44(actor, D_800DD0B8[direction_index], 0, 1);
        ((S_8008C13C_2 *)controller)->unk_8C.u = D_8008EAC8;
        return;
    }

    clear_pending_item_action_state();
    check_tile_entry_at_adjusted_height(controller, actor_id, actor, actor_data);
    actor_data->flags1C |= 0x40000000;
    g_dungeon_status.flags |= 0x812;
}
