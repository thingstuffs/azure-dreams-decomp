#include "common.h"

extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern s32 func_8001A510(s32);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

/* Dispatches the entry according to flags 0x798 and 0x799. */
void func_8001754C(s32 context, s32 entry_index) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_80019618(context, entry_index);
#ifndef NON_MATCHING
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result = 1;
#endif
        return;
    }
    func_80019928(context, entry_index);
}
