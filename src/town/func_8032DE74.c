#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001EC35[];
extern u8 D_8001ED0E[];

/* Select a data pointer based on the result of querying 0xD81. */
void *func_80018674(void) {
    if (func_8001ADE0(0xD81) != 0) {
        return D_8001ED0E;
    }
    return D_8001EC35;
}
