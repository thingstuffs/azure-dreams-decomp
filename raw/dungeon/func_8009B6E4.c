#include "common.h"

extern s32 func_800A6D30(void);
extern s16 D_80083466[];

void func_800A0E44(void) {
    D_80083466[0] = func_800A6D30() & 0xF;
}
