#include "common.h"

extern void func_800A09F4(void *arg0, s32 arg1);

/* Runs the shared town script handler with argument 8. */
void func_800A0A34(void *script_context) {
    func_800A09F4(script_context, 8);
}
