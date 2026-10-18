#include "modules/dungeon_ovl_7e711800.h"

void decrement_effect_counter_by_twelve(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800259AC = 1;
    counter -= 12;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
