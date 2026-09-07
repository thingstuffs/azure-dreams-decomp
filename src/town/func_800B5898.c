#include "common.h"

extern s32 func_8004A658(s32 a0, s32 a1);

void func_800B2FF8(s32 **arg0, s32 *arg1, s32 arg2) {
    s32 i;
    s32 count;
    s32 pos;
    u8 **ptr;
    s32 **dst;
    u8 *rec;
    s32 **p;
    s32 *rec2;

    i = 0;
    count = arg1[0];
    dst = arg0;
    pos = count * 10;
    ptr = (u8 **)((pos * 4) + arg2);

    for (; i < 10 && pos < arg1[3]; pos++) {
        i++;
        rec = *ptr;
        ptr++;
        *(*dst) = func_8004A658(rec[1], rec[0]);
        dst++;
    }
    if (i < 10) {
        for (p = (s32 **)((s32)(i * 4) + (s32)arg0); i < 10; p++) {
            i++;
            rec2 = *p;
            do {
            } while (0);
            *rec2 = 0;
        }
    }
}
