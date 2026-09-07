#include "common.h"

extern s32 D_80100DB8[];
extern s32 D_80100DE0[];

extern void func_800A4B40(s32 *arg0);
extern void func_800A5178(s32 *arg0);
extern void func_800A4A4C(void);

void func_800A4928(void) {
    s32 *temp_s0 = D_80100DB8;

    func_800A4B40(D_80100DE0);
    func_800A5178(temp_s0);
    func_800A4A4C();
}
