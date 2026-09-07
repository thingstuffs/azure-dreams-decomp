#include "common.h"

#include "common.h"

extern void func_80048660(u8 *, s32);
extern void func_80048870(u8 *, s32, s32);

void func_800488F0(u8 *arg0, s32 *arg1, s32 arg2)
{
    u8 *cur;
    s32 *arg1p;
    s32 *back;
    s32 flag2;
    s32 flag1;

    cur = arg0;
    arg1p = arg1;
    back = (s32 *)cur;
    flag2 = arg2 & 2;
    flag1 = arg2 & 1;
    while (1) {
        if ((*cur & 0x60) == 0) {
            back = (s32 *)((s8 *)back - 4);
            if (flag2 != 0) {
                func_80048660(cur, *arg1p);
            }
            if (flag1 != 0) {
                func_80048870(cur, *arg1p, *back);
            }
        }
        if ((*cur & 0x80) != 0) {
            cur += 0xC;
            break;
        }
        cur += 0xC;
    }
}
