#include "modules/dungeon_ovl_1831cd8.h"

void invoke_enabled_menu_callback(s32 *record) {
    if (record[8] != 0) {
        D_80029514[record[5]](record);
    }
}
