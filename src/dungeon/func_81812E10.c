#include "modules/dungeon_ovl_1831cd8.h"

void tick_menu_countdown(s32 *countdownState) {
    D_80029524[countdownState[5]](countdownState);
    countdownState[0]--;
    if (countdownState[0] < 0) {
        countdownState[0] = 0;
        countdownState[-4] = (s32)(void *)handle_menu_record_check;
    }
    invoke_enabled_menu_callback(countdownState);
}
