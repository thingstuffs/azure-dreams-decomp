#include "common.h"

extern u8 D_800A4D4C[];
extern u8 D_80100D98[];

typedef struct {
    void *value;
    s32 pad[2];
} State;

extern State D_80100DE0;

void func_800A50B8(void) {
    u8 *base = (u8 *)&D_80100DE0;

    *(void **)(base + 0x28) = D_800A4D4C;
    D_80100DE0.value = D_80100D98;
    *(void **)(base + 0x2C) = D_80100D98;
}
