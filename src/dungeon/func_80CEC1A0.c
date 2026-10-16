#include "modules/dungeon_ovl_7f469800_p07.h"

/* Updates the display table and directional entry for kinds 13 through 15. */
void func_801759A0(T_801759A0_Obj0 *actor, void *context, T_801759A0_Obj2 *display_arg, T_801759A0_Obj3 *state_arg)
{
    T_801759A0_Obj2 *display = display_arg;
    T_801759A0_Obj3 *state = state_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E54;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E24;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
            func_80047784(display, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 14:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E5C;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E2C;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
            func_80047784(display, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 15:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E64;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E34;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
            func_80047784(display, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    default:
        break;
    }

    if (func_800AC82C(actor, context, display, state) != 0) {
        if ((func_800AD9B4(display, state) << 16) > 0) {
            actor->field8c = func_801724BC;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (display->table2c != D_80175E54 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DC4;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DC4), 0);
        return;
    case 14:
        if (display->table2c != D_80175E5C ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DCC;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DCC), 0);
        return;
    case 15:
        if (display->table2c != D_80175E64 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DD4;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DD4), 0);
        return;
    default:
        return;
    }

}
