#include "common.h"

extern u16 func_80095978(void *arg0, void *arg1);
extern void func_80095A94(void *arg0, s16 arg1, void *arg2);
extern void func_80098928(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];
extern u8 D_800FE488[];

void func_800982EC(void *arg0, void *arg1, s32 arg2) {
    void *temp_v1;

    if (D_800CFCB4[0x3B] != 0) {
        temp_v1 = *(void **)(*(void **)(D_800CFCB4 + 0x20) + 8);
        if ((*(s32 *)((u8 *)temp_v1 + 0xC) == 0) &&
            (*(s32 *)((u8 *)temp_v1 + 0x10) == 0)) {
            if (*(s32 *)((u8 *)temp_v1 + 0x14) != 0) {
                goto update;
            }
        } else {
            goto update;
        }
    } else {
update:
        func_80095A94(arg1, func_80095978(arg1, D_800FE488),
                      D_800FE488);
    }
    func_80098928(arg0, arg1, arg2);
}
