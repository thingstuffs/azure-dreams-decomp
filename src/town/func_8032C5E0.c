#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001EC4B[];
extern u8 D_8001EB04[];

/* Select D_8001EB04 or D_8001EC4B based on the query for 0xD83. */
void *func_80016DE0(void) {
    if (func_8001ADE0(0xD83) == 0) {
        return D_8001EB04;
    }
    return D_8001EC4B;
}
