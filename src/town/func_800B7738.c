#include "common.h"

extern void townSetRecordValueAndDataPointer();
extern void func_800B4CBC();
extern void townInitializeFourSlotObject();
void func_800B4E98(u8 *owner) {
    townSetRecordValueAndDataPointer(owner);
    func_800B4CBC(owner + 0x4C, owner + 0x24, owner + 0x34);
    townInitializeFourSlotObject(owner);
}
