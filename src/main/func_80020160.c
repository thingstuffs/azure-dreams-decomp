#include "common.h"

extern u8 D_80408D40[][2];
extern s32 D_80408D44[];

extern void func_8004DDBC(void *arg0, s32 arg1, s32 *arg2);

void func_80020160(u8 *arg0) {
    s32 var_s1;
    s32 var_s2;
    u8 (*table)[2];
    s32 *values;
    u8 a1;
    s32 *chk;
    s32 *q;
    s32 val;
    s32 **row;
    s32 index;

    var_s1 = 0;
    table = D_80408D40;
    values = D_80408D44;
    var_s2 = 0;
    do {
        a1 = table[*(s32 *)(arg0 + 0x24)][var_s1];
        chk = *(s32 **)(*(u8 **)(arg0 + 0x60) + a1 * 4 + 8);
        if (*chk != 0) {
            func_8004DDBC(arg0 + (a1 * 0xC + 4),
                          *(s32 *)((u8 *)D_80408D44 + 8 + var_s2), chk);
        }
        a1 = table[*(s32 *)(arg0 + 0x24)][var_s1];
        *(*(s32 **)((u8 *)*(s32 **)(var_s2 + *(s32 *)(arg0 + 0x60)) + 4)) =
            values[a1];

        do {
            row = (s32 **)(var_s2 + *(s32 *)(arg0 + 0x60));
            index = *(s32 *)(arg0 + 0x24);
        } while (0);
        a1 = table[index][var_s1];
        q = *(s32 * volatile *)((u8 *)row[2] + 4);
        val = *(volatile s32 *)&values[a1];
        if (val != 0) {
            var_s1 += 1;
        } else {
            var_s1 += 1;
        }
        *q = val;
        var_s2 += 4;
    } while (var_s1 < 2);
}
