#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/dungeon_status.h"


/* Clear D_800DCF4F and decrement the sixth counter in D_80083460. */
void func_800A2AE4(void) {

    D_800DCF4F[0] = 0;
    dungeonStatus.unk_0A--;
}
