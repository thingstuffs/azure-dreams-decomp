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
void func_80055ADC(S_80055ADC_arg0 *a0, u32 a1)
{
  int new_var;
  register u32 idx ASM_REG("$5") = a1;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  u8 *base;
  u32 off = 0x14;
  s32 count;
  s32 i;
  u32 *out;
  u32 *first;

  LEGACY_ASM_KEEP(off);
  count = a0->count;
  LEGACY_MEMORY_BARRIER();
  i = 0;
  LEGACY_ASM_KEEP(idx);
  idx &= 0xFFFF;
  LEGACY_ASM_KEEP(idx);
  base = (u8 *)D_80084878;
  LEGACY_ASM_KEEP(base);
  idx <<= 6;
  out = (u32 *)(base + idx);
  first = out;
  for (; i < 16; i++)
  {
    new_var = 0x10;
    if (i >= count)
    {
 do { } while (0);
      *out = *first;
    }
    else
    {
      S_80055ADC_hdr *rec = (S_80055ADC_hdr *) (((u8 *) a0) + off);
      *out = (u32) (((u8 *) rec) + new_var);
      off = (off + new_var) + rec->len;
    }
    out++;
  }

}
