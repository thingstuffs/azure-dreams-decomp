#include "common.h"

extern void func_80095C80(void *arg1);
extern void func_80095094(void *arg1);
extern s16 func_80095978(void *arg1, void *arg2);
extern void func_80095A94(void *arg1, s16 arg2, void *arg3);
extern void func_80094378(void *arg0, void *arg1, s32 arg2);
extern void func_800930C4(void);
extern void func_800946FC(void *arg0, void *arg1, s32 arg2);
extern s32 func_8009FF50(void);

extern u8 D_800CFCEF[];
extern u8 D_800FE488[];

void func_80092FF0(void *arg0, void *arg1, s32 arg2) {
    s16 v0;
    u16 tmp;

    func_80095C80(arg1);
    func_80095094(arg1);
    if (func_8009FF50() == 0) {
        v0 = func_80095978(arg1, D_800FE488);
        if (v0 - *(s16 *)((u8 *)arg1 + 0xA) >= 4) {
            if (D_800CFCEF[0] == 0) {
                func_80094378(arg0, arg1, arg2);
                func_800930C4();
                return;
            }
        } else {
            if (D_800CFCEF[0] == 0) {
                func_80095A94(arg1, v0, D_800FE488);
            }
        }
    }

    tmp = *(u16 *)((u8 *)arg0 + 0xA) - 1;
    *(u16 *)((u8 *)arg0 + 0xA) = tmp;
    if ((s16)tmp < 0) {
        func_800946FC(arg0, arg1, arg2);
    }
}
