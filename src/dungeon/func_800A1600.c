#include "common.h"

typedef struct {
    u8 pad[0x1FC];
    s32 unk1FC;
} S_800A1600_D80083160;

extern S_800A1600_D80083160 D_80083160;
extern s32 D_800DD87C[];

void func_800A6D60(s32 arg0) {
    S_800A1600_D80083160 *base = &D_80083160;
    s32 temp = arg0 << 16;

    if (temp != 0) {
        D_800DD87C[0] = base->unk1FC;
        return;
    }
    base->unk1FC = D_800DD87C[0];
}
