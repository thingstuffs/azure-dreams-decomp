#include "common.h"

extern void townInitializeItemMenuRequestState();
extern void townInitializeItemMenuLinkedBlocks();
extern void townInitializeItemMenuObjectSlots();
void func_800B0158(u8 *owner) {
    townInitializeItemMenuRequestState(owner);
    townInitializeItemMenuLinkedBlocks(owner + 0x98, owner + 0x70, owner + 0x80);
    townInitializeItemMenuObjectSlots(owner);
}
