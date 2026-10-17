#include "modules/dungeon_ovl_7f469800_p03.h"

/* Advances the actor along its stored path and updates its movement state. */
void func_80172CC0(void *movement, s32 actor_index, void *actor, void *path_state)
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
        current_table = ((Rec_D_80082E80 *)actor)->unk_2C.as_pu8;
        direction_table = (u8 *)&D_80175DC4;
        break;
    case 0xE:
        current_table = ((Rec_D_80082E80 *)actor)->unk_2C.as_pu8;
        direction_table = (u8 *)&D_80175DCC;
        break;
    case 0xF:
        current_table = ((Rec_D_80082E80 *)actor)->unk_2C.as_pu8;
        direction_table = (u8 *)&D_80175DD4;
        break;
    default:
        goto setup;
    }
    if (current_table != direction_table) {
        (*(u8 * *)((u8 *)actor + 0x2C)) = direction_table;
        direction_addr =
            ((gameWork.view.viewAngle + ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        func_80047784(actor, *(u8 *)direction_addr, 0);
    }

setup:
    cell_flags = 0x3000;
    x = ((Rec_D_80082E80 *)actor)->unk_24;
    y = ((Rec_D_80082E80 *)actor)->unk_25;
    if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
        cell_flags = 0x300;
    }
    func_8009A3D0(x, y, cell_flags);

    heading = dungeonGetRoundedFacingAndRoundingFlag(x, y,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_74,
        ((T_80172CC0_S_80172CC0_4 *)((u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98);
    move_result = (s16)dungeonCheckMovementClearanceAndHeight(heading, actor, state, 0x20);

    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    ((Rec_D_80082E80 *)actor)->unk_24 = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_74;
    cell_flags = 0x3000;
    path_entry = (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s;
    do {
    } while (0);
    ((Rec_D_80082E80 *)actor)->unk_25 = ((T_80172CC0_S_80172CC0_2 *)path_entry)->unk_7C;
    ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.u++;
    {
        s32 next_x = ((Rec_D_80082E80 *)actor)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)actor)->unk_25;

        if (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C & 0x2000) {
            cell_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, cell_flags);
    }

    ((T_80172CC0_S_80172CC0_0 *)state)->unk_2A = heading;
    if (move_result == 3 && !(dungeonStatus.flags & 0x80) && !(((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000)) {
        dungeonResetActorDirectionalAnimation(movement, actor_index, actor, state);
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    } else {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80172CC0_arg0 *)movement)->unk_8C.as_s32 = 0;
    }
    (((T_80172CC0_S_80172CC0_0 *)state)->unk_1C) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 0;
        return;
    }

    ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8;
    x = ((T_80172CC0_S_80172CC0_0 *)state)->unk_71.u;
    if (x > 0) {
        ((Rec_func_80172CC0_arg0 *)movement)->unk_96.as_s16 = 8 / x;
    }
}
