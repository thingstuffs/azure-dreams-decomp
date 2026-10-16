/* Relink of matched dungeon/dungeonIsGlobalEffectEnabled; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/sys_flags.h"


/* Returns whether bit 0x10 is set in D_80013714[0]. */
s32 func_80170BAC(void) {
    if (D_80013714 & 0x10) {
        return 1;
    }
    return 0;
}
