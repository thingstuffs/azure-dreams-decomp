#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern void *D_80016000;
extern s32 D_80018340;
extern u8 D_800183D0;

/* Submit the global value and command 0x17, and save the callback result. */
void func_8065C3AC(void) {
    s8 command_args[2];

    command_args[1] = 0x17;
    command_args[0] = D_800183D0;
    D_80018340 = FIELD(FIELD(D_80016000, void **, 0x20), s32 (**)(s8 *), 0x50)(command_args);
}
