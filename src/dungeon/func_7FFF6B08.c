#include "modules/dungeon_ovl_16b08_local.h"

void dungeonInitializeActionObjectTypeThree(Rec_func_80094268_arg0 *object) {
    townCallTheHandlerSelectsNonzeroEntry(&D_800D00A0, object);
    object->unk_00.as_pm = (void *)func_80091F64;
    object->unk_0A.as_s16 = 3;
}
