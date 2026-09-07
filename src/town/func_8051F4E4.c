#include "common.h"

extern s32 func_800162F8(void);
extern u8 D_8001C9C7[];
extern u8 D_8001D244[];

void *func_80016CE4(void) {
    if (func_800162F8() != 0) {
        return D_8001D244;
    }
    return D_8001C9C7;
}
