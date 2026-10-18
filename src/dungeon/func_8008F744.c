#include "common.h"
#include "shared/game_work.h"


/* Check for flags in mask 0xF0A3 while flag 0x10 is clear. */
s32 has_action_input_without_modifier(void) {
    if (!(g_game_work.buttons & 0x10)) {
        if (g_game_work.buttons & 0xF0A3) {
            return 1;
        }
    }
    return 0;
}
