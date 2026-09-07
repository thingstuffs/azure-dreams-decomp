#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(var) ((void)0)
#define LEGACY_MEMORY_BARRIER() ((void)0)
#else
#define LEGACY_ASM_KEEP(var) __asm__ __volatile__("" : : "r"(var))
#define LEGACY_MEMORY_BARRIER() __asm__ __volatile__("" : : : "memory")
#endif

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
  register u32 tableByteOffset ASM_REG("$5") = tableIndex;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
  u8 *tableBase;
  u32 recordOffset = 0x14;
  s32 recordCount;
  s32 slotIndex;
  u32 *outputSlot;
  u32 *firstSlot;

  LEGACY_ASM_KEEP(recordOffset);
  recordCount = recordBlock->count;
  LEGACY_MEMORY_BARRIER();
  slotIndex = 0;
  LEGACY_ASM_KEEP(tableByteOffset);
  tableByteOffset &= 0xFFFF;
  LEGACY_ASM_KEEP(tableByteOffset);
  tableBase = (u8 *)D_80084878;
  LEGACY_ASM_KEEP(tableBase);
  tableByteOffset <<= 6;
  outputSlot = (u32 *)(tableBase + tableByteOffset);
  firstSlot = outputSlot;
  for (; slotIndex < 16; slotIndex++)
  {
    recordHeaderSize = 0x10;
    if (slotIndex >= recordCount)
    {
      do { } while (0);
      *outputSlot = *firstSlot;
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
