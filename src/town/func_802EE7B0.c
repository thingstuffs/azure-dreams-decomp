#include "common.h"

extern void func_804057A8(void *, s32);
extern void func_80405624(void *, void *, void *);
extern void func_8040553C(void *);
void func_804057B0(u8 *owner, s32 value) {
    func_804057A8(owner, value);
    func_80405624(owner + 0xAF8, owner + 0xAD0, owner + 0xAE0);
    func_8040553C(owner);
}
