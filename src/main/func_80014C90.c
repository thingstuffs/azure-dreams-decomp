#include "common.h"

extern void func_8004F52C(s32);
extern void func_80026FB4(s32);
extern void func_800A6104(void);
extern s32 D_800814A0;

typedef struct {
    /* 0x00 */ s8 pad0[0x1E];
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s8 pad28[0x18];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} Struct80014C90;

void func_80027C90(Struct80014C90 *arg0) {
    Struct80014C90 *temp_s0 = (Struct80014C90 *)((s8 *)arg0 + 0x20);

    func_8004F52C(temp_s0->unk20);
    func_80026FB4(temp_s0->unk24);
    if (arg0->unk20 == 2) {
        func_800A6104();
    }
    arg0->unk1E |= 0x8000;
    D_800814A0 |= 0x8000;
}
