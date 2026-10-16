#include "modules/dungeon_ovl_16b08_local.h"

void func_8009455C(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra) {
    object->unk_3E.as_s16 = 6;
    townStoreTheValidSharedAngleInOffsetHex10(object);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0130, object, context);
    object->unk_00.as_pm = (void *)townUpdateActorPositionAndInteraction;
}
