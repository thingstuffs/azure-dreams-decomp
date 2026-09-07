#include "common.h"

extern void func_8003B0B8(void *, void *);
extern void *func_800373DC(s32);

extern u8 D_8052664C[];
extern u8 D_80526640[];
extern u8 D_8052B2A4[];

s32 func_80810650(void) {
    void *temp_v0;

    func_8003B0B8(D_8052664C, D_80526640);
    temp_v0 = func_800373DC(2);
    if (temp_v0 == 0) {
        return 0;
    }
    *(void **)((u8 *)temp_v0 + 0x10) = D_8052B2A4;
    return 0;
}
