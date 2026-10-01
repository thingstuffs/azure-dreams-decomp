#include "common.h"

extern s8 D_80089268[];
extern s32 get_player_homerank();

/* Return the selected value from the three global entries. */
u8 func_800B2918(void) {
    s8 values[3];

    memcpy(values, D_80089268, 3);
    return values[get_player_homerank()];
}
