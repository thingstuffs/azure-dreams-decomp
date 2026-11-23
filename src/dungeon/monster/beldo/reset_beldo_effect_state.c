#include "common.h"
#include "shared/game_state.h"
#include "dungeon/monster/beldo.h"

extern u8 *D_80173F90;


/* Resets global state fields and flags and loads the configured value. */
void reset_beldo_effect_state(void) {
    u8 *page = (u8 *)0x80010000;
    u16 flags;
    u8 *value;

    flags = *(u16 *)(page + 0x3714);
    *(s16 *)(page + 0x371A) = 0;
    *(s16 *)(page + 0x3718) = 0;
    *(s16 *)(page + 0x3716) = 0;
    *(s16 *)(page + 0x3714) = (flags | 9) & 0xFFEF;
    value = D_80173F90;
    GAME_STATE->log.data = value;
}
