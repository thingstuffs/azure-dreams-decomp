#include "common.h"

extern s32 func_800AD058(u8 *, s32 *, u8 *, u8 *);

/* Forward all four effect callback arguments and the result. */
s32 func_80161BD8(u8 *state, s32 *position, u8 *sprite, u8 *entity_data) {
    return func_800AD058(state, position, sprite, entity_data);
}
