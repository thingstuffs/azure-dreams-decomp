#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    u8 pad[0x20];
    void *ptr;
} State;
typedef struct {
    u8 pad[0x190];
    M2C_UNK (*func)(M2C_UNK);
} CallTable;

extern State *D_80016000;
extern M2C_UNK D_800174BC;
extern M2C_UNK *D_8001758C;

/* Select D_800174BC and invoke the state callback with zero. */
void func_804D0958(void) {
    D_8001758C = &D_800174BC;
    ((CallTable *)D_80016000->ptr)->func(0);
}

/* MECHANISM: Preserve the seed's 24-byte frame and sole $ra save.
   Passing literal zero emits retail's move $a0,$zero in the jalr delay slot;
   literal 2 was the only linked-word substitution. */
