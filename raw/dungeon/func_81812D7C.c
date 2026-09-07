#include "common.h"

extern void (*D_8002951C[])(void);
extern void func_80026CF0(s32, s32);
extern void func_80026D0C(s32, s32);
extern void func_80027A20(s32 *);
extern s32 D_80027A88[];

void func_80027D7C(s32 *arg0) {
    D_8002951C[arg0[5]]();
    arg0[0]++;
    if (arg0[1] < arg0[0]) {
        func_80026CF0(arg0[34], arg0[19]);
        func_80026D0C(arg0[34], arg0[2]);
        arg0[-4] = (u32)D_80027A88;
    }
    func_80027A20(arg0);
}
