#include "common.h"

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

extern DungeonSlot *D_800E3DF0[];

// Returns the slot index for a matching type-0x13 record, or -1 if none matches.
s32 func_800A4298(DungeonSlot *targetSlot) {
    s32 recordIndex;
    s32 requiredRecordType;
    DungeonSlot **slotTable;
    u8 *recordSlotByte;
    s32 slotIndex;

    recordIndex = 0;
    requiredRecordType = 0x13;
    slotTable = D_800E3DF0;
    recordSlotByte = (u8 *) 0x8001024B;
    do {
        if (recordSlotByte[-2] == requiredRecordType) {
            slotIndex = recordSlotByte[0] & 0x1F;
            if (slotTable[slotIndex] == targetSlot) {
                return slotIndex;
            }
        }
        recordIndex++;
        recordSlotByte += 4;
    } while (recordIndex < 0x14);
    return -1;
}
