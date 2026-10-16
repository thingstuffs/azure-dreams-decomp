#include "modules/dungeon_ovl_1831370.h"

void dungeonUpdateMenuSelectionFromInput(ovl_1831370_8181140C_MenuState *menu) {
    s32 direction = 0;
    s32 buttons;
    s32 repeat_ticks;
    s32 selection;

    if (gameWork.buttons != 0) {
        if (((s32)gameWork.unk_010) & 0xC) {
            menu->field4 = 0;
            buttons = ((s32)gameWork.unk_010);
            if (buttons & 4) {
                direction = -1;
            } else if (buttons & 8) {
                direction = 1;
            }
        } else if (gameWork.buttons & 0xC) {
            repeat_ticks = menu->field4;
            if (repeat_ticks >= 9) {
                menu->field4 = repeat_ticks - 1;
                buttons = gameWork.buttons;
                if (buttons & 4) {
                    direction = -1;
                } else if (buttons & 8) {
                    direction = 1;
                }
            } else {
                menu->field4 = repeat_ticks + 1;
            }
        }

        if (direction != 0) {
            SD_Call(0x502);
            selection = dungeonAdjustSelectionByItemCount(direction, menu->field8, menu->field10);
            menu->field8 = selection;
            dungeonSetIndexedObjectField(menu->field70, selection);
        }
    }
}
