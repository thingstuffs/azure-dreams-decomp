#include "common.h"

extern void func_800B384C();
extern void func_800B3688();
extern void func_800B3734();
void func_800B3868(u8 *owner) {
    func_800B384C(owner);
    func_800B3688(owner + 0x98, owner + 0x70, owner + 0x80);
    func_800B3734(owner);
}
