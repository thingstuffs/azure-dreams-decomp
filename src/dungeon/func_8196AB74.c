#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/object_flags.h"


/* Subtracts 8 from the object counter and sets flags when it reaches zero. */
void advance_counter_and_propagate_target_flags(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800269B4 = 1;
    counter -= 8;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
