#include "modules/town_ovl_3ef1c8.h"

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
