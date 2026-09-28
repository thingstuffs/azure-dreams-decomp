#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


/* Decrements the record countdown and marks completion when it reaches zero. */
void func_800CC9BC(void *record) {
    u8 countdown;

    countdown = *(u8 *)((u8 *)record + 7) - 1;
    *(u8 *)((u8 *)record + 7) = countdown;
    if (!(countdown & 0xFF)) {
        dungeonStatus.unk_0A = (u16)(((u16)dungeonStatus.unk_0A) - 1);
        *(u16 *)((u8 *)record - 2) =
            (u16)(*(u16 *)((u8 *)record - 2) | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
