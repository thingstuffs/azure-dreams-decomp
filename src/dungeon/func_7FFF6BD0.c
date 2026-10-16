#include "modules/dungeon_ovl_16b08_local.h"

void dungeonInitializeActionObjectTypeSix(Rec_func_80094268_arg0 *object) {
    townCallTheHandlerSelectsNonzeroEntry(&D_800D00C0, object);
    object->unk_00.as_pm = (void *)townUpdateCountdownAndFallback;
    object->unk_0A.as_s16 = 6;
}
