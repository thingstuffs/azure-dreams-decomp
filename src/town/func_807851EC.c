#include "common.h"
typedef struct { u8 pad[0x40]; void *value; } Child;
typedef struct { u8 pad[0x1C]; Child *child; } State;
extern State *D_80016000;
extern void *D_800174E0;
extern u8 D_80016084[], D_8001601C[];
void func_800161EC(void) {
    D_800174E0 = D_80016084;
    D_80016000->child->value = D_8001601C;
}
