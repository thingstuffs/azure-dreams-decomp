#include "common.h"

#include "common.h"

typedef struct {
    char pad0[8];
    s32 field8;
} S_80039884_Global;

typedef struct {
    char pad0[0x87];
    s8 field87;
} S_80039884_Arg;

extern S_80039884_Global D_80083160;

/* Returns whether the state flag is set or global flag bits 0x60 are clear. */
s32 func_80039884(S_80039884_Arg *state)
{
    s32 result = 0;
    S_80039884_Global *global = &D_80083160;

    if (state->field87 == 0) {
        if ((global->field8 & 0x60) != 0) {
            goto done;
        }
    }

    result = 1;
done:
    return result;
}
