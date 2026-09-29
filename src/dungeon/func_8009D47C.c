#include "common.h"
#include "shared/dungeon_status.h"

/* Return whether any checked global state value or flag is set. */
s32 func_800A2BDC(void) {
    if (dungeonStatus.unk_0C != 0 ||
        dungeonStatus.unk_10 != 0 ||
        *(s32 *)&dungeonStatus.unk_08 != 0 ||
        (dungeonStatus.flags & 0x2008) != 0) {
        return 1;
    }
    return 0;
}
