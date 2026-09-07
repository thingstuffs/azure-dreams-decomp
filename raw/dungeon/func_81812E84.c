#include "common.h"

extern void (*D_8002952C[])(void);
extern void func_80027454(void *, s32, s32, s32);
extern void func_80027A20(s32 *);
extern s32 D_80027D7C[];

void func_80027E84(s32 *arg0) {
    D_8002952C[arg0[5]]();
    arg0[0]--;
    if (arg0[0] < 0) {
        arg0[0] = 0;
        func_80027454((u8 *)arg0 + 0x38, arg0[5], (arg0[2] / 72) * 72, arg0[10]);
        arg0[-4] = (u32)D_80027D7C;
    }
    func_80027A20(arg0);
}
