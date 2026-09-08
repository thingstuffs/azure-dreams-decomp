#include "common.h"

extern s32 func_80019618();
extern s32 func_80019814();
extern s32 func_80019880();
extern s32 func_8001A510();

/* Dispatch inputs according to flag 0x798, returning 1 for the fallback handler. */
s32 func_80017098(s32 primaryInput, s32 secondaryInput) {
    s32 result;

    if (func_8001A510(0x798) != 0) {
        func_80019880();
        result = func_80019814(primaryInput, secondaryInput);
    } else {
        func_80019618(primaryInput, secondaryInput);
        result = 1;
    }

    return result;
}
