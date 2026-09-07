#include "common.h"

extern u32 func_800352FC(void);
extern void func_800A4F84(void);

void func_800A4F4C(void *arg0) {
    if (func_800352FC() != 0) {
        *(void **)((u8 *)arg0 + 0x24) = func_800A4F84;
    }
}
