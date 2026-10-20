#include "dungeon/monster/troll/advance_actor_stored_path.h"
#include "shared/sprite_frame_state.h"

/* Advances the actor along its stored path and updates its movement state. */
void advance_actor_stored_path_2(void *movement, s32 actor_index, void *actor, void *path_state)
{
    void *state = path_state;
    s32 cell_flags;
    s32 move_result;
    s16 heading;
    s32 x;
    s32 y;
    s32 move_kind;
    s32 path_length;
    unsigned long direction_addr;
    u8 *direction_table;
    u8 *current_table;
    u8 *path_entry;

    if (((T_80172CC0_S_80172CC0_0 *)state)->unk_71.s <= 0) {
        return;
    }
    path_length = ((T_80172CC0_S_80172CC0_0 *)state)->unk_71.u;
    if (!(((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s < path_length)) {
        return;
    }

    move_kind = ((T_80172CC0_S_80172CC0_0 *)state)->unk_48;
    switch (move_kind) {
    case 0xD:
        current_table = *(u8 * *)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&D_80175DC4;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    case 0xE:
        current_table = *(u8 * *)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&D_80175DCC;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    case 0xF:
        current_table = *(u8 * *)&((SpriteFrameState *)actor)->frameTable;
        direction_table = (u8 *)&D_80175DD4;
    if (current_table != direction_table) {
        ((SpriteFrameState *)actor)->frameTable = direction_table;
        direction_addr =
            ((g_game_work.view.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        select_sprite_entry(actor, *(u8 *)direction_addr, 0);
    }
        break;
    default:
        break;
    }

    cell_flags = 0x3000;
    x = ((SpriteFrameState *)actor)->unk_24;
    y = ((SpriteFrameState *)actor)->unk_25;
    if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
        cell_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, cell_flags);

    heading = get_rounded_facing_and_rounding_flag(x, y,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_74,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98);
    move_result = (s16)check_movement_clearance_and_height(heading, actor, state, 0x20);

    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    ((SpriteFrameState *)actor)->unk_24 = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_74;
    cell_flags = 0x3000;
    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    do {
    } while (0);
    ((SpriteFrameState *)actor)->unk_25 = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_7C;
    ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.u++;
    {
        s32 next_x = ((SpriteFrameState *)actor)->unk_24;
        s32 next_y = ((SpriteFrameState *)actor)->unk_25;

        if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
            cell_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, cell_flags);
    }

    ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A = heading;
    if (move_result == 3 && !(g_dungeon_status.flags & 0x80) && !(((SpriteFrameState *)actor)->flags & 0x8000)) {
        reset_actor_directional_animation(movement, actor_index, actor, state);
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    } else {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    }
    (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 0;
        return;
    }

    ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8;
    x = ((T_80172CC0_S_80172CC0_0 *)state)->unk_71.u;
    if (x > 0) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8 / x;
    }
}
