#include "dungeon/player.h"

/* Return the base value plus an optional signed modifier, clamped to 0 through 99. */
s16 get_clamped_adjusted_value(ActorRecord *actor) {
    s16 adjusted_value;
    u8 modifier_byte;

    adjusted_value = (u8)actor->attack_bonus;
    if (actor->weapon != 0) {
        modifier_byte = *((u8 *)actor->weapon + 2);
        adjusted_value += (s8)modifier_byte;
    }
    if (adjusted_value < 0) {
        adjusted_value = 0;
    }
    if (adjusted_value >= 100) {
        adjusted_value = 99;
    }
    return adjusted_value;
}
