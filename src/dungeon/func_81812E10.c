#include "common.h"

extern void (*D_80029524[])(void);
extern void func_80027A20(s32 *);
extern s32 D_80027A88[];

void func_80027E10(s32 *arg0) {
    D_80029524[arg0[5]]();
    arg0[0]--;
    if (arg0[0] < 0) {
        arg0[0] = 0;
        arg0[-4] = (s32)D_80027A88;
    }
    func_80027A20(arg0);
}
