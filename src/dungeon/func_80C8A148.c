#include "common.h"

extern s32 dungeonUpdateActorDefeatRemoval(u8 *, s32 *, u8 *, u8 *);

/* Forward all four effect callback arguments and the result. */
s32 func_80155948(u8 *state, s32 *position, u8 *sprite, u8 *entity_data) {
    return dungeonUpdateActorDefeatRemoval(state, position, sprite, entity_data);
}
