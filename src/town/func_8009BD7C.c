#include "common.h"

extern void func_80094984(void *, void *);
extern s32 func_800A8184(s16, s16);
extern u8 D_80082660[];
extern u8 D_80097EA0[];
extern u8 D_800D01C0[];

typedef struct {
    u8 unk0[4];
    void *unk4;
    u8 unk8[0x2E];
    s16 unk36;
    s16 unk38;
} TownObject;

void func_800994DC(TownObject *arg0) {
    func_80094984(D_800D01C0, arg0);
    D_80082660[8] = 0;
    arg0->unk4 = D_80097EA0;
    D_80082660[9] = 0;
    func_800A8184(arg0->unk36, arg0->unk38);
}
