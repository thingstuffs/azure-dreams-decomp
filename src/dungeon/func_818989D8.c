#include "modules/dungeon_ovl_18b8824.h"

void func_800241D8(void *entry, void *unused, void *target)
{
    void *object;

    object = *(void **)entry;
    *(u16 *)((u8 *)object + 0x14) += 1;
    *(u16 *)((u8 *)entry + 4) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)entry - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
