#include "common.h"
#include "shared/dungeon_status.h"

/* Return whether any checked global state value or flag is set. */
s32 func_800A2BDC(void) {
    if (dungeonStatus.unk_0C != 0) {
        goto ret_one;
    }
    if (dungeonStatus.unk_10 != 0) {
        goto ret_one;
    }
    if (*(s32 *)&dungeonStatus.unk_08 != 0) {
        goto ret_one;
    }
    if ((dungeonStatus.flags & 0x2008) != 0) {
        goto ret_one;
    }
    goto ret_zero;
ret_one:
    return 1;
ret_zero:
    return 0;
}
