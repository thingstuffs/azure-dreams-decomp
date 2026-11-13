#include "common.h"
#include "shared/game_work.h"

#include "engine/input.h"


/* Returns the newly pressed pad button bits from g_game_work.pressed_buttons. */
s32 get_pressed_pad_buttons(void) {
    return (g_game_work.pressed_buttons);
}
