#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/input.h"


/* Returns the current value of D_80083170. */
s32 runtime_get_state_value_83170(void) {
    return ((s32)g_game_work.pressed_buttons);
}
