#include "common.h"
#include "shared/game_work.h"

#include "common.h"


/* Returns the current value of D_80083168. */
s32 runtimeGetStateValue83168(void) {
    return gameWork.buttons;
}
