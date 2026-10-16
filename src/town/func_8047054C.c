#include "modules/town_ovl_3ef1c8.h"

s32 townDispatchEntryBy798And799Flags(s32 context, s32 entry_index) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_80019618(context, entry_index);
        return 1;
    }
    return func_80019928(context, entry_index);
}
