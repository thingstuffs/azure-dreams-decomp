#include "common.h"

typedef s32 M2C_UNK;

extern s32 D_80016530[];
extern s32 D_80019BB4;

s32 func_80017890(void) {
    s32 index = D_80019BB4;
    return D_80016530[index];
}
