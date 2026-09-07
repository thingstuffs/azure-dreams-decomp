#include "common.h"

extern s8 D_800CFC24[];
extern void func_80035208(s8 *);

void func_8008B5D8(s32 arg0, s8 arg1) {
    s8 *data = (s8 *)D_800CFC24;

    data[3] = arg0 >> 8;
    data[2] = arg0;
    data[4] = arg0 >> 16;
    data[5] = arg0 >> 24;
    data[6] = arg1;
    func_80035208(data);
}
