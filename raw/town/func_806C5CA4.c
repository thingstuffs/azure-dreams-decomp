#include "common.h"

extern s32 func_80018C74();
extern s32 func_80018CEC();
extern s32 func_80018D6C();

s32 func_80016CA4(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    if (func_80018D6C(0x7D1) != 0) {
        if (func_80018D6C(0x7D2) == 0) {
            if (func_80018D6C(0xFC5) != 0) {
                func_80018C74(0x7D4);
                return 1;
            }
        }
    }
    return 0;
}
