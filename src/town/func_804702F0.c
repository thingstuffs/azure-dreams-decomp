#include "modules/town_ovl_3ef1c8.h"

s32 townDispatchEntryBy799Flag(s32 context, s32 entryIndex) {
    s32 result;

    if (func_8001A510(0x799) != 0) {
        D_8001B208 = 0;
        result = func_80019928(context, entryIndex);
    } else {
        func_80019618(context, entryIndex);
        result = 1;
    }
    return result;
}
