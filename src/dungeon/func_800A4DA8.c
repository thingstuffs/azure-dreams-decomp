#include "common.h"
#include "shared/dungeon_status.h"

/* Sets the entity state to 3, clears its progress, and increments the global counter. */
void func_800AA508(void *entity) {
    *(s8 *)((s8 *)entity + 0x9A) = 3;
    *(s8 *)((s8 *)entity + 0x9B) = 0;
    *(s32 *)((s8 *)entity + 0x8C) = 0;
    *(s16 *)((s8 *)entity + 0x96) = 4;
    dungeonStatus.unk_0A += 1;
}
