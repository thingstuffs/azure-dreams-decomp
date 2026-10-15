#include "modules/dungeon_ovl_1830850.h"

void func_800262EC(s32 object_addr) {
    ovl_1830850_818112EC_S_800262EC_0 *object_data;

    object_data = object_addr + 0x20;
    object_data->unk_10 = 0;
    func_80025C4C(object_data->unk_54);
}
