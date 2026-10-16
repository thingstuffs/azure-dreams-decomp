#include "common.h"
typedef struct { u8 pad[0x40]; void *value; } Child;
typedef struct { u8 pad[0x1C]; Child *child; } State;
extern State *D_80016000;
extern void *D_800174D0;
extern u8 D_80017404[], D_800176F5[];
void func_80016128(void) {
    D_800174D0 = D_80017404;
    D_80016000->child->value = D_800176F5;
}
