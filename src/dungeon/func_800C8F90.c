#include "common.h"

extern s32 func_800CE4E8();
extern s32 func_800CE738();
extern s32 D_800E296C;

s32 func_800CE6F0(void *arg0) {
    void *temp_v0;

    if (D_800E296C & 0xC0000000) {
        return 1;
    }
    temp_v0 = *(void **)((u8 *)arg0 - 0x14);
    func_800CE4E8(
        *(u8 *)((u8 *)temp_v0 + 0x24),
        *(u8 *)((u8 *)temp_v0 + 0x25),
        *(s16 *)((u8 *)arg0 + 0x88),
        arg0,
        1);
    return func_800CE738() != 0;
}
