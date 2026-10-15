#include "modules/town_player_init.h"

/* plt_init_sleep_set: set the sleep initialization pointer. */
void plt_init_sleep_set(void) {
    D_800D0438 = &func_80090378;
}
