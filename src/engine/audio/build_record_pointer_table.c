#include "common.h"
#include "engine/audio.h"




typedef struct S_80055ADC_hdr
{
    u32 unk0;
    u32 len;
    u8 pad08[8];
}
S_80055ADC_hdr;
typedef struct S_80055ADC_arg0
{
    u8 pad00[0x10];
    s32 count;
    u8 records[1];
}
S_80055ADC_arg0;
extern void *audio_selection_record_pointers[][16];
// Fills a 16-entry table with record payload pointers, repeating the first pointer for unused slots.
void build_record_pointer_table(S_80055ADC_arg0 *recordBlock, u32 tableIndex)
{
    int recordHeaderSize;
    s32 tableByteOffset = tableIndex;
    u8 *tableBase;
    u32 recordOffset = 0x14;
    s32 recordCount;
    s32 slotIndex;
    void **outputSlot;
    void **firstSlot;

    recordCount = (recordBlock->count);
    slotIndex = 0;
    tableByteOffset &= 0xFFFF;
    tableBase = (u8 *)audio_selection_record_pointers;
    tableByteOffset <<= 4;
    outputSlot = (void **)tableBase + tableByteOffset;
    firstSlot = outputSlot;
    for (; slotIndex < 16; slotIndex++) {
        recordHeaderSize = 0x10;
        if (slotIndex >= recordCount) {
            tableBase = *firstSlot;
            *outputSlot = tableBase;
        }
        else {
            S_80055ADC_hdr *recordHeader = (S_80055ADC_hdr *) (((u8 *) recordBlock) + recordOffset);
            *outputSlot = ((u8 *) recordHeader) + recordHeaderSize;
            recordOffset = (recordOffset + recordHeaderSize) + recordHeader->len;
        }
        outputSlot++;
    }
}
