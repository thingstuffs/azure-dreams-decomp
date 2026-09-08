#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern void func_80019BC0(void);
extern void func_80019B54(s32 arg0, s32 arg1);

/* Run the preliminary callback for condition 0x12C4, then dispatch the argument pair. */
void func_800165F4(s32 dispatch_value, s32 dispatch_option) {
    if (func_8001ADE0(0x12C4) != 0) {
        func_80019BC0();
    }
    func_80019B54(dispatch_value, dispatch_option);
}
