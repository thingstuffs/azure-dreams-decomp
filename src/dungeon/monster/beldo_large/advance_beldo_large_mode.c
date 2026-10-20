#include "common.h"

typedef struct { u8 pad[0x96]; s16 timer; u8 pad98[2]; u8 mode, next; } Work;
extern u8 *D_80175D54;
void advance_beldo_large_mode(s32 value) {
    Work *state = (Work *)(D_80175D54 + 0x20);
    state->timer = 0; state->mode++;
}
