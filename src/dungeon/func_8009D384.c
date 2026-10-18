#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/dungeon_status.h"


/* Clear D_800DCF4F and decrement the sixth counter in D_80083460. */
void clear_monster_event_and_decrement_count(void) {

    D_800DCF4F[0] = 0;
    g_dungeon_status.unk_0A--;
}
