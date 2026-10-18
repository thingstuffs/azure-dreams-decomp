#include "modules/dungeon_ovl_1830850.h"

void inventory_select_null_or_default_data(void *object)
{
    if (check_object_byte_pairs_content(*(s32 *)((u8 *)*(void **)((u8 *)object + 0x18) + 0x28))) {
        **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = 0;
        return;
    }

    **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = D_800294C4;
}
