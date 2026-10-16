#include "modules/dungeon_ovl_18c4828.h"

void func_80024230(void **object_ref, long long value) {
    void *object;
    u16 *counter;
    u32 low_value;

    object = *object_ref;
    counter = (u16 *)((s8 *)object + 0x14);
    low_value = value;
    *counter = (u16)(*counter + 1);
    func_800478B8(low_value);
}
