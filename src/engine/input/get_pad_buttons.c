#include "common.h"
#include "shared/game_work.h"

#include "engine/input.h"


/* Returns the current pad button bits from g_game_work.buttons. */
s32 get_held_pad_buttons(void) {
    return g_game_work.buttons;
}
