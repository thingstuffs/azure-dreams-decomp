#include "modules/dungeon_ovl_1830850.h"

void inventorySelectNullOrDefaultData(void *object)
{
    if (dungeonCheckObjectBytePairsContent(*(s32 *)((u8 *)*(void **)((u8 *)object + 0x18) + 0x28))) {
        **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = 0;
        return;
    }

    **(void ***)((u8 *)*(void **)((u8 *)object + 0x54) + 0x30) = D_800294C4;
}
