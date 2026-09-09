#include "common.h"

extern u8 D_800A4D4C[];
extern u8 D_80100D98[];

typedef struct {
    void *value;
    s32 pad[2];
} State;

extern State D_80100DE0;

/* tcame_chase2_set: Set the alternate camera chase handler and target pointers. */
void tcame_chase2_set(void) {
    u8 *state = (u8 *)&D_80100DE0;

    *(void **)(state + 0x28) = D_800A4D4C;
    D_80100DE0.value = D_80100D98;
    *(void **)(state + 0x2C) = D_80100D98;
}
