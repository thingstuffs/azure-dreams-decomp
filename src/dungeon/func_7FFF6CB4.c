#include "modules/dungeon_ovl_16b08_local.h"

void func_80094414(M2C_UNK **object, M2C_UNK unused, M2C_UNK context) {
    SD_Call(0x50B);
    func_80094C1C(object);
    func_80094984(&D_800D0110, object, context);
    *object = (void *)func_800924EC;
}
