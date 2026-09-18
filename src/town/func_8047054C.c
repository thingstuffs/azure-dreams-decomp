#include "common.h"

extern void func_80019618(s32, s32);
extern s32 func_80019928(s32, s32);
extern s32 func_8001A510(s32);

/* Dispatches the entry according to flags 0x798 and 0x799. */
s32 func_8001754C(s32 context, s32 entry_index) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_80019618(context, entry_index);
        return 1;
    }
    return func_80019928(context, entry_index);
}
