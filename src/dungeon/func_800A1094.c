#include "common.h"

extern s32 D_800E296C[];
extern u16 D_80013714[];
extern s8 D_800DCF4F[];
extern u16 D_80083460[];
extern s8 D_800E045C[];

extern s32 func_80035208(void *arg);
extern void func_80035348(void);

void func_800A67F4(void) {
    if (!(D_800E296C[0] & 0x200000) && !(D_80013714[0] & 8)) {
        if (D_800DCF4F[0] != 0) {
            D_800DCF4F[0] = 0;
            D_80083460[5]--;
        }
        func_80035208(&D_800E045C[0]);
        func_80035348();
    }
}
