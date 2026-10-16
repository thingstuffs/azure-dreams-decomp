#include "common.h"

/* Already-matched callee (defined elsewhere): returns &D_800FC000[a0]. */
extern void *getSpriteResourceSlotBuffer(int a0);

extern void queueEntityResourceDescriptorPair(void *a0, void *a1, unsigned short a2);

extern void *D_80080A90;

/* Passes the indexed slot, global pointer, and low 16 bits of value to queueEntityResourceDescriptorPair. */
void queueSpriteResourceSlotReads(int slot_index, int value)
{
    queueEntityResourceDescriptorPair(getSpriteResourceSlotBuffer(slot_index), D_80080A90, (unsigned short)value);
}
