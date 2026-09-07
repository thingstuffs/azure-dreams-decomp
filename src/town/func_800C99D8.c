#include "common.h"

typedef struct {
    s8 pad0[0x54];
    void *unk54;
    u8 pad58[8];
    s32 unk60;
} Obj;

typedef struct {
    u8 pad0[0x14];
    u16 unk14;
} Arg2;

extern void func_800C2E84();
extern u8 D_80082660[];
extern u8 D_800C3C28[];
extern u8 D_800D5CD0[];

void func_800C7138(Obj *arg0, s32 unused, Arg2 *arg2) {
    if (arg2->unk14 & 0x6000) {
        func_800C2E84(arg0, arg2, D_800D5CD0);
        D_80082660[arg0->unk60 * 8] = 0;
        arg0->unk54 = D_800C3C28;
    }
}
