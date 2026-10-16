#include "common.h"
#include "shared/dungeon_status.h"

extern s32 func_800A6D30(void);

/* Stores the low four bits of the computed result in the global slot. */
void dungeonStoreMonsterDirectionNibble(void) {
    dungeonStatus.unk_06 = func_800A6D30() & 0xF;
}
