#include "common.h"

extern void (*D_80029514[])(void);

void func_80027A20(s32 *arg0) {
    if (arg0[8] != 0) {
        D_80029514[arg0[5]]();
    }
}
