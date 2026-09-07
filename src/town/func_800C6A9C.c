#include "common.h"

typedef struct {
    s8 field0;
    u8 pad1[7];
} S_80082660;

extern s32 D_800C3A98;
extern S_80082660 D_80082660[];
extern void func_800C2E84();

void func_800C41FC(void *arg0, s32 arg1, s32 arg2) {
    void *t0;

    t0 = *(void **)((u8 *)arg0 + 0x80);
    func_800C2E84(arg0, arg2, *(s32 *)((u8 *)t0 + 8));
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].field0 = 0;
    *(void **)((u8 *)arg0 + 0x54) = &D_800C3A98;
    *(s16 *)((u8 *)arg0 + 0x6C) = 0x20;
}
