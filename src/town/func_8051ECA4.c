#include "common.h"

extern s32 func_80017710(s32 *arg0, s32 arg1);
extern s32 D_80018D78[];

s32 func_8051ECA4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *base = D_80018D78;
    s32 index = func_80017710(base, arg2);
    
    return *(s32 *)((s8 *)base + (index * 8) + 4);
}
