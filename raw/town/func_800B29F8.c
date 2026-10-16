#include "common.h"

extern void func_800B0134();
extern void func_800AFF00();
extern void func_800B0024();
void func_800B0158(u8 *owner) {
    func_800B0134(owner);
    func_800AFF00(owner + 0x98, owner + 0x70, owner + 0x80);
    func_800B0024(owner);
}
