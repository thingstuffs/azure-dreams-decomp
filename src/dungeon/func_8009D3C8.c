#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/sys_flags.h"

extern u8 D_800E3D20;

/* Returns whether D_800E3D20 is set while bit 1 of D_80013714 is clear. */
s32 is_dungeon_action_enabled(void) {
    if (!(D_80013714 & 2) && D_800E3D20) {
        return 1;
    }
    return 0;
}
