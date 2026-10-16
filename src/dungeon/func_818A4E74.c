#include "modules/dungeon_ovl_18c4828.h"

void func_80024674(void **object_ref, s32 unused, Row_818A4E74_S_func_818A4E74_1 *target) {
    s32 random_value;
    s32 random_quotient;
    Row_818A4E74_S_func_818A4E74_0 *object;

    object = *object_ref;
    object->unk_14 = (u16)(object->unk_14 + 1);
    random_value = rand();
    random_quotient = random_value / 0x1000;
    target->unk_1A = (s16)(random_value - (random_quotient << 12));
}
