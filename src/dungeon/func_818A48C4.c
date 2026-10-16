#include "modules/dungeon_ovl_18c4828.h"

void func_800240C4(Row_818A48C4_Func818A48C4Object **source_ref, s32 unused,
                   Row_818A48C4_Func818A48C4Object *target) {
    Row_818A48C4_Func818A48C4Object *source;
    s32 random_value;

    source = *source_ref;
    source->flags += 1;
    func_800478B8(target);
    random_value = rand();
    target->value = (s16)(random_value % 0x1000);
    if (target->flags & 0x6000) {
        func_8003DB94(target, D_80025238, 0);
    }
}
