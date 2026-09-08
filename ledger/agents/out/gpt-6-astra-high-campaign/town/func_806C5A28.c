#include "common.h"

extern s32 func_800175A8();

/* Submit command 8 with its flag set and remaining arguments cleared. */
void func_80016A28(void) {
    s8 command_args[4];

    command_args[1] = 1;
    command_args[0] = 8;
    command_args[2] = 0;
    command_args[3] = 0;
    func_800175A8(command_args);
}
