#include "common.h"

extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern void func_8001A490(s32);
extern s32 func_8001A510(s32);

/* Selects a handler for the context entry based on two flags. */
s32 func_80017408(s32 context, s32 entry_index) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_8001A490(0x11FB);
        func_80019618(context, entry_index);
        return 1;
    }
    func_80019928(context, entry_index);
#ifdef NON_MATCHING
    return 0;
#endif
}
