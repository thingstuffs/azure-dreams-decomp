#include "modules/dungeon_resource12_slot0.h"

void advance_actor_path_script_step(void *controller, void *context, void *entity, void *path_state)
{
    void *state = path_state;
    s32 move_flags;
    s16 direction;
    s16 move_result;
    s16 x;
    s32 y;
    s32 control_flags;

    if (((R12_801713D4_S_8017139C_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((R12_801713D4_S_8017139C_0 *)state)->unk_71.u <= ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != ((u8 *)D_80175A4C)) {
        (*(u8 * *)((u8 *)entity + (0x2C))) = ((u8 *)D_80175A4C);
        func_80047784(
            entity,
            ((u8 *)D_80175A4C)[((g_game_work.view.viewAngle + ((R12_801713D4_S_8017139C_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (((R12_801713D4_S_8017139C_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    direction = ((s16)get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_74,
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)controller + 0x98));
    move_result = ((s16)check_movement_clearance_and_height(direction, entity, state, 0x20));

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_7C;
    ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (((R12_801713D4_S_8017139C_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    ((R12_801713D4_S_8017139C_0 *)state)->unk_2A = direction;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            advance_linked_actor_motion_script(controller, context, entity, state);
        } else {
            ((R12_801713D4_S_8017139C_2 *)controller)->unk_9A = 0xF;
        }
    } else {
        control_flags = ((R12_801713D4_S_8017139C_2 *)controller)->unk_98;
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_9A = 0xF;
        control_flags &= ~8;
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_98 = control_flags;
    }
    ((R12_801713D4_S_8017139C_2 *)controller)->unk_8C = 0;
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 0;
        return;
    }

    ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 8;
    {
        s32 step_count = ((R12_801713D4_S_8017139C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 8 / step_count;
        }
    }
}
