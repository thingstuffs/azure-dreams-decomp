#include "common.h"
#include "dungeon/actor.h"

/* Cap and return the adjustment so the base plus adjustment stays within the limit. */
s32 cap_pending_actor_value_delta(void *entry) {

    s16 adjustment;
    u8 base;
    u8 limit;
    __typeof__(limit - base) hoisted_1;

    adjustment = ((ActorRecord *)entry)->hp_delta;
    base = ((ActorRecord *)entry)->hp;
    limit = ((ActorRecord *)entry)->max_hp;
    if ((s32)limit < (adjustment + base)) {
        hoisted_1 = limit - base;
        ((ActorRecord *)entry)->hp_delta = hoisted_1;
    }
    return ((ActorRecord *)entry)->hp_delta;
}
