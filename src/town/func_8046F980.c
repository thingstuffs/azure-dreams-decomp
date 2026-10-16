#include "modules/town_ovl_3ef1c8.h"

s32 townDispatchCode7A0ByStatus(void) {
    s32 status;

    status = func_80019928();
    if (status == 0) {
        func_8001A418(0x7A0);
    } else {
        func_8001A490(0x7A0);
    }
    return status;
}
