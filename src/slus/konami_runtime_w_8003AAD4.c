#include "common.h"
#include "shared/game_work.h"

#include "common.h"


/* Returns the current value of D_80083170. */
s32 runtimeGetStateValue83170(void) {
    return ((s32)gameWork.unk_010);
}
