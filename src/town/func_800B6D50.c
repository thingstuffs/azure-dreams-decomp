#include "common.h"

extern void townSetRecordBaseAndDataPointerAlt();
extern void townInitializeEntityDisplayParts();
extern void townInitializeObjectDataBlocksAndEntries();
void func_800B44B0(u8 *owner) {
    townSetRecordBaseAndDataPointerAlt(owner);
    townInitializeEntityDisplayParts(owner + 0x4C, owner + 0x24, owner + 0x34);
    townInitializeObjectDataBlocksAndEntries(owner);
}
