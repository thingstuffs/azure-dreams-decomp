#include "common.h"

extern void func_800B4494();
extern void func_800B3EEC();
extern void func_800B43E8();
void func_800B44B0(u8 *owner) {
    func_800B4494(owner);
    func_800B3EEC(owner + 0x4C, owner + 0x24, owner + 0x34);
    func_800B43E8(owner);
}
