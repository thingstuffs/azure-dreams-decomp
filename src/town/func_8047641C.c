#include "common.h"

extern void func_800182A8(void);
extern void *D_80016000;
extern s32 D_8001691C;
extern s32 *D_80019BB8;
extern s32 D_80019BBC;

void func_8047641C(void) {
    void *base;

    func_800182A8();
    base = D_80016000;
    D_80019BB8 = &D_8001691C;
    D_80019BBC = *(s32 *)((u8 *)base + 0x40) + 8;
}
