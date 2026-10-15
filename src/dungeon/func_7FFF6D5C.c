#include "modules/dungeon_ovl_16b08_local.h"

void func_800944BC(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    SD_Call(0x511);
    func_80094984(&D_800D0120, object, context);
    object->unk_00.as_pm = (void *)func_80092698;
    object->unk_0A.as_s16 = 6;
}
