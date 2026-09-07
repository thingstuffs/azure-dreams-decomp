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

s32 func_80039884(S_80039884_Arg *arg0)
{
    s32 result = 0;
    S_80039884_Global *global = &D_80083160;

    if (arg0->field87 == 0) {
        if ((global->field8 & 0x60) != 0) {
            goto done;
        }
    }

    result = 1;
done:
    return result;
}
