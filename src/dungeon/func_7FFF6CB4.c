#include "modules/dungeon_ovl_16b08_local.h"

void func_80094414(M2C_UNK **object, M2C_UNK unused, M2C_UNK context) {
    SD_Call(0x50B);
    townStoreTheValidSharedAngleInOffsetHex10(object);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0110, object, context);
    *object = (void *)townUpdateActorInputActions;
}
