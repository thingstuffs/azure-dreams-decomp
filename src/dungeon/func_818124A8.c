#include "modules/dungeon_ovl_1831cd8.h"

void reset_menu_object_state_2(void *record) {
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_00 = (void *)tick_menu_countdown;
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_10 = (s32) ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_14;
    reset_object_to_default_data(((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_54);
    clear_menu_embedded_state(record - 0x20);
}
