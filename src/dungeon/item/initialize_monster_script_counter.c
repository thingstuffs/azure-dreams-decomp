#include "common.h"
#include "shared/game_state.h"
#include "dungeon/item.h"


/* Clears the value at 0x80013718 and increments the counter at 0x8001371A. */
void initialize_monster_script_counter(void) {
    u16 counter;

    counter = GAME_STATE->log.head.cursor;
    GAME_STATE->log.head.repeat = 0;
    GAME_STATE->log.head.cursor = (s16)(counter + 1);
}
