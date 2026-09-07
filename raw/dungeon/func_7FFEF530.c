#include "common.h"

extern s32 func_80065F90(s32, s32);

s32 func_8008CC90(
    s16 arg0, s16 arg1, s16 arg2, s16 arg3,
    u16 arg4, u16 arg5, u16 arg6, u16 arg7)
{
    s32 angle0;
    s32 angle1;
    s32 angle2;
    s32 answer;
    s32 edge0;
    s32 edge1;
    s32 first_arg;
    s32 result;
    s32 work;

    if (((u32)arg1 << 16) == 0) {
        if (((u32)arg0 << 16) == 0) return 1;
    }
    if (((u32)arg3 << 16) == 0) {
        if (((u32)arg2 << 16) == 0) return 1;
    }
    if (arg5 == 0) {
        if (arg4 == 0) return 1;
    }
    if (arg7 == 0) {
        if (arg6 == 0) {
            answer = 1;
            goto out;
        }
        first_arg = (s32)((u32)arg1 << 16);
    } else {
        first_arg = (s32)((u32)arg1 << 16);
    }

    angle0 = func_80065F90(first_arg >> 16, (s16)arg0) & 0xFFF;
    angle2 = func_80065F90((s16)arg3, (s16)arg2) & 0xFFF;
    angle1 = func_80065F90((s16)arg5, (s16)arg4) & 0xFFF;
    result = func_80065F90((s16)arg7, (s16)arg6) & 0xFFF;
    result = (result - angle0) & 0xFFF;
    angle1 = (angle1 - angle0) & 0xFFF;
    angle2 = (angle2 - angle0) & 0xFFF;
    work = angle1 - angle2;
    edge0 = work & 0xFFF;
    work = result - angle1;
    edge1 = work & 0xFFF;
    work = 0x1000;
    result = work - result;

    if (angle2 < 0x801 && edge0 < 0x801) {
        if (edge1 >= 0x801) { answer = 0; goto out; }
        result = result < 0x801;
        if (result != 0) { answer = 1; goto out; }
    }
    answer = 0;
out:
    return answer;
}
