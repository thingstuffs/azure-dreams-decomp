#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/input.h"


/* Returns the current pad button bits from g_game_work.buttons. */
s32 runtime_get_state_value_83168(void) {
    return g_game_work.buttons;
}
