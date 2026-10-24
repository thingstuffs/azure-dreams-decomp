#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/input.h"


/* Returns the newly pressed pad button bits from g_game_work.pressed_buttons. */
s32 runtime_get_state_value_83170(void) {
    return (g_game_work.pressed_buttons);
}
