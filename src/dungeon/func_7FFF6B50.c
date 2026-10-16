#include "modules/dungeon_ovl_16b08_local.h"

void func_800942B0(Rec_func_80094268_arg0 *object, EntityRec *state, M2C_UNK setupArg) {
    townDispatchSoundByGlobalFlag();
    state->flags14 = 0xFFEF0000;
    townCallTheHandlerSelectsNonzeroEntry(&D_800D00B0, object, setupArg);
    object->unk_00.as_pm = (void *)townUpdateActorAndDispatchState;
    object->unk_0A.as_s16 = 0;
}
