#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern u8 D_80096384[];
extern u8 D_800DD274[];

extern s32 func_8003DB94();
extern void check_tile_entry_at_adjusted_height();
extern void process_unflagged_linked_entries();
extern void process_unflagged_linked_entries_alt();
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s32 classify_adjacent_tile_height();
extern void append_packed_action_record();
extern s32 check_action_available_without_nearby_actor();
extern void clear_pending_item_action_state(void);

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define P32(p, o) (*(void **)((u8 *)(p) + (o)))

/* Moves the actor and updates its animation, movement state, and map flags. */
void update_actor_movement_and_map_flags(void *obj, s32 move_mode, void *actor, void *map)
{
    GameWork *globals;
    register s16 move_kind;
    register s32 move_result;
    register u16 *move_state;
    DungeonGlobalStatus *updated_state;
    register u8 *anim_table;
    register s32 facing_offset;

    globals = &g_game_work;
    clear_pending_item_action_state();
    move_result = classify_adjacent_tile_height(S16(map, 0x2A), move_mode, actor, S16(map, 0x88), 0x20);
    move_kind = (s16)move_result;
    if (move_kind > 0) {
        U8(obj, 0x9B) = 0;
        update_map_cell_flags_with_item_limit(U8(actor, 0x24), U8(actor, 0x25), 0x300);
        {
            u8 *x_offsets;
            s16 step_index;

            step_index = (U16(map, 0x2A) >> 8) & 0xE;
            x_offsets = ((u8 *)dir_step_x);
            U8(actor, 0x24) = U8(actor, 0x24) + x_offsets[step_index];
            U8(actor, 0x25) = U8(actor, 0x25) + ((u8 *)dir_step_y)[step_index];
        }
        cycle_map_cell_flags(U8(actor, 0x24), U8(actor, 0x25), 0x300);

        move_state = (u16 *)&g_dungeon_status;
        move_state[1] |= 8;
        S32(obj, 0x8C) = 0;

        if (move_kind != 4) {
            if (D_80013714 & 2) {
                void *anim_entry;

                move_state[1] |= 0x80;
                anim_table = D_800DD274;
                if (P32(actor, 0x2C) != anim_table) {
                    P32(actor, 0x2C) = anim_table;
                    facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
                    anim_entry = anim_table + (facing_offset & 0x1C);
                    func_8003DB94(actor, *(void **)anim_entry, 0);
                }
            } else if ((S32(globals, 8) & 0x20) && check_action_available_without_nearby_actor()) {
                register u8 *alternate_anim;

                move_state[1] |= 0x80;
                alternate_anim = D_800DD274;
                P32(actor, 0x2C) = alternate_anim;
                facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
                func_8003DB94(actor, *(void **)(alternate_anim + (facing_offset & 0x1C)), 0);
            } else {
                move_result = 5;
                U8(obj, 0x9B) = 10;
            }
        }

        {
            s16 move_kind;

            updated_state = &g_dungeon_status;
            move_kind = (s16)move_result;
            if ((updated_state->flags & 0x80) || move_kind == 1) {
                process_unflagged_linked_entries_alt(S32(map, 0x5C));
                process_unflagged_linked_entries(S32(map, 0x5C));
                if (!(updated_state->flags & 0x80)) {
                    P32(actor, 0x2C) = D_800DD274;
                    facing_offset = (g_game_work.view.viewAngle + S16(map, 0x2A) + 0x100) >> 7;
                    func_8003DB94(actor, *(void **)(D_800DD274 + (facing_offset & 0x1C)), 0);
                    U8(obj, 0x9A) = 0x35;
                } else {
                    U8(obj, 0x9A) = 0x35;
                }
                updated_state->unk_04 = 8;
            } else {
                U16(obj, 0x98) |= 0xC;
                P32(actor, 0x2C) = D_800DD274 + 0x20;
                facing_offset = (g_game_work.view.viewAngle + S16(map, 0x2A) + 0x100) >> 7;
                func_8003DB94(actor, *(void **)((D_800DD274 + 0x20) + (facing_offset & 0x1C)), 0);
                if (move_kind < 4) {
                    U16(obj, 0xA2) |= 1;
                } else if (move_kind == 2 || move_kind == 4) {
                    U8(obj, 0x9B) = 8;
                }
                check_tile_entry_at_adjusted_height(obj, move_mode, actor, map);
                {
                    g_dungeon_status.unk_04 = 8;
                    U8(obj, 0x9A) = 0x36;
                    U16(obj, 0x96) = 2;
                    S32(map, 0x1C) |= 0x40000000;
                    append_packed_action_record(map, 8, 0, 0);
                }
                return;
            }
            append_packed_action_record(map, 8, 0, 0);
        }
    } else {
        u8 *idle_anim;

        idle_anim = D_800DD274;
        P32(actor, 0x2C) = idle_anim;
        facing_offset = (S16(globals, 0xC8) + S16(map, 0x2A) + 0x100) >> 7;
        func_8003DB94(actor, *(void **)(idle_anim + (facing_offset & 0x1C)), 0);
        S32(obj, 0x8C) = (s32)D_80096384;
        return;
    }

    check_tile_entry_at_adjusted_height(obj, move_mode, actor, map);
    S32(map, 0x1C) |= 0x40000000;
    g_dungeon_status.flags |= 0x812;
}
