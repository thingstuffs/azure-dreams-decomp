#include "common.h"

typedef struct {
    void *value;
    s32 pad[9];
    void (*callback)(void *);
} State;

extern void func_800A4B94(void *);
extern u8 D_80100D98[];
extern State D_80100DE0;

/* tcame_chase_set: Set the camera chase callback and target. */
void func_800A5094(void) {
    u8 *state_bytes = (u8 *)&D_80100DE0;

    *(void (**)(void *))(state_bytes + 0x28) = func_800A4B94;
    D_80100DE0.value = D_80100D98;
}
