#include "common.h"

extern s8 D_8001601C[];
extern u8 D_80017774[];
extern void *D_80018034[];
extern u8 *D_8001E950[];

void *func_8001B408(s32 arg0, s32 arg1, s32 arg2)
{
    if (arg2 == 4) {
        return D_8001601C;
    } else if (arg2 == 5) {
        return D_80017774;
    } else {
        return D_80018034[D_8001E950[0][3]];
    }
}
