#include "common.h"

extern s32 update_actor_defeat_removal(u8 *, s32 *, u8 *, u8 *);

/* Forward all four effect callback arguments and the result. */
s32 func_8016D314(u8 *state, s32 *position, u8 *sprite, u8 *entity_data) {
    return update_actor_defeat_removal(state, position, sprite, entity_data);
}
