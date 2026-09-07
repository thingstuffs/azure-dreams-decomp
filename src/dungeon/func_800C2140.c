#include "common.h"

extern s16 D_80083780[];
extern u16 D_800E58F8[];
extern void func_800C77D0(void *, void *, s16, s32);

void func_800C78A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 distance;
    s32 call_arg;

    call_arg = arg4;
    distance = D_80083780[1] - arg1;
    ASM_KEEP(call_arg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 193) {
        distance = D_80083780[3] - arg2;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 193) {
            u16 *buffer = D_800E58F8;

            buffer[1] = arg1;
            buffer[3] = arg2;
            buffer[5] = arg3;
            func_800C77D0((void *)arg0, buffer, (s16)call_arg, arg5);
        }
    }
}
