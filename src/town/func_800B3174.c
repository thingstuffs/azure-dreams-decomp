#include "common.h"

extern s32 textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(s32, s32*);
extern s32 townInitializeShopDisplayRecords(s32, s32*);
extern s32 D_800D15C4;

/* Process the record and its subrecord at offset 0x48 using the shared data. */
void townProcessShopRecordAndSubrecord(s32 record_address) {
    textureBuildAHex48ByteTwoColorSwappedPatternBlocksReturnsBase(record_address, &D_800D15C4);
    townInitializeShopDisplayRecords(record_address + 0x48, &D_800D15C4);
}
