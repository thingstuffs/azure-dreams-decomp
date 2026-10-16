#include "common.h"

extern void townSetRecordBaseAndDataPointer();
extern void townInitializeDisplayInstances();
extern void townInitializeFourSlotObjectVariant();
void func_800B3868(u8 *owner) {
    townSetRecordBaseAndDataPointer(owner);
    townInitializeDisplayInstances(owner + 0x98, owner + 0x70, owner + 0x80);
    townInitializeFourSlotObjectVariant(owner);
}
