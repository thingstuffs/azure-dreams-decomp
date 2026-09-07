#include "common.h"

extern s32 func_800478B8();
extern s32 D_800814A0[3];

void func_80024AA4(void *arg0, void *arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = *(void **)arg0;
    *(u16 *)((u8 *)temp_v1 + 0x52) =
        (u16)(*(u16 *)((u8 *)temp_v1 + 0x52) | 0x8000);
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) =
            (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
