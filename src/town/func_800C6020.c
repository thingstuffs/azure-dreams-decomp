#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, s32 arg2);
extern s32 D_800C34CC;

void func_800C3780(void *arg0, s32 arg1, s32 arg2) {
    struct {
        char pad[0x50];
        void *unk50;
        char pad2[0x7C - 0x54];
        s32 *unk7C;
    } *s0 = arg0;

    func_800C2E84(arg0, arg2, *s0->unk7C);
    s0->unk50 = &D_800C34CC;
}
