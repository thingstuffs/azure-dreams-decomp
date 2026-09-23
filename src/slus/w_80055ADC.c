#include "common.h"

#include "common.h"


typedef struct S_80055ADC_hdr
{
  u32 unk0;
  u32 len;
  u8 pad08[8];
} S_80055ADC_hdr;
typedef struct S_80055ADC_arg0
{
  u8 pad00[0x10];
  s32 count;
  u8 records[1];
} S_80055ADC_arg0;
extern u32 D_80084878[];
// Fills a 16-entry table with record payload pointers, repeating the first pointer for unused slots.
void func_80055ADC(S_80055ADC_arg0 *recordBlock, u32 tableIndex)
{
  int recordHeaderSize;
  s32 tableByteOffset = tableIndex;
  u8 *tableBase;
  u32 recordOffset = 0x14;
  s32 recordCount;
  s32 slotIndex;
  u32 *outputSlot;
  u32 *firstSlot;

  recordCount = (*(s32 *)((u8 *)recordBlock + 0x10));
  slotIndex = 0;
  tableByteOffset &= 0xFFFF;
  tableBase = (u8 *)D_80084878;
  tableByteOffset <<= 6;
  outputSlot = (u32 *)(tableBase + tableByteOffset);
  firstSlot = outputSlot;
  for (; slotIndex < 16; slotIndex++)
  {
    recordHeaderSize = 0x10;
    if (slotIndex >= recordCount)
    {
      tableBase = *firstSlot;
      *outputSlot = tableBase;
    }
    else
    {
      S_80055ADC_hdr *recordHeader = (S_80055ADC_hdr *) (((u8 *) recordBlock) + recordOffset);
      *outputSlot = (u32) (((u8 *) recordHeader) + recordHeaderSize);
      recordOffset = (recordOffset + recordHeaderSize) + recordHeader->len;
    }
    outputSlot++;
  }
}
