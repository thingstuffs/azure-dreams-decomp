#include "modules/dungeon_ovl_1831370.h"

void update_menu_selection_from_input(ovl_1831370_8181140C_MenuState *menu) {
    s32 direction = 0;
    s32 buttons;
    s32 repeat_ticks;
    s32 selection;

    if (g_game_work.buttons != 0) {
        if (((s32)g_game_work.unk_010) & 0xC) {
            menu->field4 = 0;
            buttons = ((s32)g_game_work.unk_010);
            if (buttons & 4) {
                direction = -1;
            } else if (buttons & 8) {
                direction = 1;
            }
        } else if (g_game_work.buttons & 0xC) {
            repeat_ticks = menu->field4;
            if (repeat_ticks >= 9) {
                menu->field4 = repeat_ticks - 1;
                buttons = g_game_work.buttons;
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
            selection = adjust_selection_by_item_count(direction, menu->field8, menu->field10);
            menu->field8 = selection;
            set_indexed_object_field(menu->field70, selection);
        }
    }
}
