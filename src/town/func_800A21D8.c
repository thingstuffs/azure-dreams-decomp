#include "common.h"

extern s32 func_8009F830(void);
extern void func_8009F8EC(s32);

s32 func_8009F938(void) {
    s32 value;

    value = func_8009F830();
    if (value == 0) {
        return -1;
    }
    func_8009F8EC(value);
}
