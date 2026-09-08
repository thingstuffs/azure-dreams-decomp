#include "common.h"

extern s32 func_80016D10(void *, void *, s32, s32);
extern u8 D_8001795C[];
extern u8 D_80017A94[];

/* Processes the requested entry and value using the two shared tables. */
s32 func_8054F9D4(s32 entry_id, s32 unused, s32 value)
{
    return func_80016D10(D_8001795C, D_80017A94, entry_id, value);
}
