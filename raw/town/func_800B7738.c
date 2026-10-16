#include "common.h"

extern void func_800B4E7C();
extern void func_800B4CBC();
extern void func_800B4D64();
void func_800B4E98(u8 *owner) {
    func_800B4E7C(owner);
    func_800B4CBC(owner + 0x4C, owner + 0x24, owner + 0x34);
    func_800B4D64(owner);
}
