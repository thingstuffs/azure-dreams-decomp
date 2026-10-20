#include "common.h"
typedef struct { u8 pad[0x40]; void *value; } Child;
typedef struct { u8 pad[0x1C]; Child *child; } State;
extern State *D_80016000;
extern void *D_800174D8;
extern u8 D_80017404[], D_8001770A[];
void set_shared_buffer_pointers(void) {
    D_800174D8 = D_80017404;
    D_80016000->child->value = D_8001770A;
}
