#include "modules/dungeon_ovl_1831370.h"

void release_object_handle(ovl_1831370_81811B44_S_80026B44_0 *owner) {
    s32 handle;

    handle = *owner->unk_0C;
    if (handle != 0) {
        func_8004E99C(handle);
        *owner->unk_0C = 0;
    }
}
