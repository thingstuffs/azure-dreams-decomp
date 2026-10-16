#include "modules/dungeon_ovl_1831cd8.h"

void dungeonHandleMenuGridInput(ovl_1831cd8_818124F0_S_800274F0_Arg *menu) {
    GameWork *input;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 index_step = 0;
    s32 repeat_ticks;
    s32 next_index;
    s32 selected_index;
    s32 item_count;
    s32 remaining_items;
    s32 repeat_buttons;

    input = &gameWork;
    held_buttons = input->buttons;
    if (held_buttons == 0)
        return;
    pressed_buttons = ((s32)input->unk_010);
    if (pressed_buttons & 0x20) {
        SD_Call(0x515, input);
        func_800274A8(menu);
        return;
    }
    if (pressed_buttons & 0x10) {
        SD_Call(0x503, input);
        func_800274A8(menu);
        dungeonForwardStoredObjectValue(menu->unk44);
        return;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(0x503, input);
        dungeonDispatchMenuStateUpdate(&menu->unk38, menu->unk14,
                      (menu->unk8 / 72) * 72, menu->unk28);
        func_800265B8(func_8002553C(menu->unk44),
                      menu->unk40 + ((menu->unk8 % 72) * 2));
        if (menu->unk14 == 1 ||
            dungeonHasAvailableObject(menu->unk48->unk28) != 0) {
            func_800274A8(menu);
            dungeonForwardStoredObjectValue(menu->unk44);
        }
        return;
    }

    if (held_buttons & 0xF000) {
        if (pressed_buttons & 0xF000) {
            menu->unkC = 0;
            pressed_buttons = ((s32)input->unk_010);
            if (pressed_buttons & 0x8000) {
                index_step = -1;
            } else if (pressed_buttons & 0x2000) {
                index_step = 1;
            } else if (pressed_buttons & 0x1000) {
                index_step = -9;
            } else if (pressed_buttons & 0x4000) {
                index_step = 9;
            }
        } else {
            repeat_ticks = menu->unkC;
            if (repeat_ticks >= 9) {
                menu->unkC = repeat_ticks - 1;
                repeat_buttons = input->buttons;
                if (repeat_buttons & 0x8000) {
                    index_step = -1;
                } else if (repeat_buttons & 0x2000) {
                    index_step = 1;
                } else if (repeat_buttons & 0x1000) {
                    index_step = -9;
                } else if (repeat_buttons & 0x4000) {
                    index_step = 9;
                }
            } else {
                menu->unkC = repeat_ticks + 1;
            }
        }
    }

    if (index_step == 0)
        return;
    SD_Call(0x502, input);
    selected_index = menu->unk8;
    item_count = menu->unk3C;
    next_index = selected_index + index_step;
    remaining_items = item_count - next_index;
    if (!(remaining_items > 0 && item_count >= remaining_items))
        return;
    menu->unk8 = next_index;
    if ((next_index - index_step) / 72 == next_index / 72) {
        dungeonPositionMenuGridEntries(menu->unk88, next_index);
        return;
    }
    dungeonClearMenuStateValues(menu->unk88);
    *(void **)((u8 *)menu - 0x10) = (void *)dungeonRunMenuCountdownCallback;
    menu->unk0 = menu->unk4;

    return;
}
