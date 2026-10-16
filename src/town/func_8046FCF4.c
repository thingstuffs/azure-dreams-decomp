#include "modules/town_ovl_3ef1c8.h"

s32 townWaitForDialogueThenClose(void) {
    if (func_80019928() != 0) {
        return 1;
    }
    func_800187AC();
    return 0;
}
