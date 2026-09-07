#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern s8 D_80016000[];

/* Calls the state handler and copies two state values to the output. */
void func_8001A854(void *output, s32 handler_arg) {
    FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x20), void (**)(s32), 0x258)(handler_arg);
    FIELD(output, u16 *, 0) = FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x1C), u16 *, 4);
    FIELD(output, u16 *, 2) = FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x1C), u16 *, 8);
}
