#include "common.h"

extern s32 D_80019BB4[];
extern void *D_80016774[];
extern void *D_80016794[];
extern u8 D_8001BA8C[];
extern u8 D_8001BA91[];

void *func_80017D24(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 5) {
        return D_8001BA91;
    }
    if (arg2 == 4) {
        return D_8001BA8C;
    }
    if (arg2 == 1) {
        return D_80016794[D_80019BB4[0]];
    }
    return D_80016774[D_80019BB4[0]];
}
