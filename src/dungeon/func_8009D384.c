#include "common.h"
#include "shared/dungeon_status.h"

extern s8 D_800DCF4F;

/* Clear D_800DCF4F and decrement the sixth counter in D_80083460. */
void func_800A2AE4(void) {

    D_800DCF4F = 0;
    dungeonStatus.unk_0A--;
}
