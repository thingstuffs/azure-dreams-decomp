#include "modules/dungeon_ovl_1830850.h"

void func_800258B8(void *item_object)
{
    s32 category;
    s32 subobject_base;
    void *object = item_object;
    ovl_1830850_818108B8_S_800258B8_1 *subobject;

    subobject_base = ((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_14;
    category = ((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_0C;
    subobject = (void *)(subobject_base + 0x20);
    if (category != 0x13) {
        if (subobject->unk_08 != 0) {
            func_8004A7D8(category, subobject->unk_1C);
            D_80073414[((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_0C]
            .records[subobject->unk_1C].value =
                subobject->unk_08;
            return;
        }
    }
    strcpy(((ovl_1830850_818108B8_S_800258B8_0 *)object)->unk_88, (u8 *)object + 0x78);
}
