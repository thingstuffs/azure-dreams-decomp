#include "modules/dungeon_ovl_1831cd8.h"

void func_800274A8(void *record) {
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_00 = (void *)dungeonTickMenuCountdown;
    ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_10 = (s32) ((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_14;
    dungeonResetObjectToDefaultData(((ovl_1831cd8_818124A8_S_800274A8_0 *)((u8 *)record - 0x10))->unk_54);
    dungeonClearMenuEmbeddedState(record - 0x20);
}
