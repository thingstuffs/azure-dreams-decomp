#include "common.h"

extern s32 func_8001B0C8(void);
extern s32 func_80019BC0();
extern s32 func_80019B54();

/* Run the preliminary callback at a count of ten or more, then dispatch the argument pair. */
void func_80016820(s32 dispatch_value, s32 dispatch_option) {
    if (func_8001B0C8() >= 10) {
        func_80019BC0();
    }
    func_80019B54(dispatch_value, dispatch_option);
}
