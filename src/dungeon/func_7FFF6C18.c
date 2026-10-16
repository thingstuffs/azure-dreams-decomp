#include "modules/dungeon_ovl_16b08_local.h"

void dungeonInitializeActionObject(M2C_UNK **object) {
    townCallTheHandlerSelectsNonzeroEntry(&D_800D00B8, object);
    *object = (void *)townUpdateThresholdBoundObject;
}
