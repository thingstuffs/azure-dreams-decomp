#include "modules/town_ovl_3ef1c8.h"

s32 townCheckInteraction13Type3(void) {
    s32 result = 0;

    if ((func_800196F4(13, 3) != 0) ||
        (func_80019778(13, 3) != 0)) {
        result = 1;
    }
    return result;
}
