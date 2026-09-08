#include "common.h"
typedef struct S_80083968
{
  u8 unk00;
  u8 pad1[3];
  s32 unk04;
  u8 unk08[16];
} S_80083968;
extern S_80083968 D_80083968[32];
extern u8 D_800814D1;
extern void func_8003E758(void);
typedef struct
{
  u8 b[16];
} S_8003E39C_blk16;
/* Waits for queue space, fills an entry, and advances the write index. */
S_80083968 *func_8003E39C(s16 entry_type, s32 entry_value, s32 payload)
{
  u8 write_index;
  s32 sentinel;
  u8 *queue_index;
  u8 *wait_index;
  register S_80083968 *entries ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  queue_index = (u8 *) (&D_800814D1);
  if (((D_800814D1 + 1) & 0x1F) == queue_index[-1])
  {
    wait_index = queue_index;
    do
    {
      func_8003E758();
    }
    while (((D_800814D1 + 1) & 0x1F) == wait_index[-1]);
  }

  {
    register u32 table_page ASM_REG("$2") = 0x80080000;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(table_page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    entries = (S_80083968 *)(table_page + 0x3968);
  }
  sentinel = 0xFF;
  write_index = D_800814D1;
  entries[write_index].unk00 = (u8) entry_type;
  entries[write_index].unk04 = entry_value;
  entries[write_index].unk08[15] = 0;
  if ((entry_type & 0xFF) == sentinel)
  {
    register S_80083968 *slot ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(entries);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    slot = &entries[write_index];
    *((s32 *) slot->unk08) = payload;
  }
  else if (payload == 1)
  {
    entries[write_index].unk08[15] = sentinel;
  }
  else
  {
    register u8 *slot_data ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(entries);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    slot_data = (u8 *) entries + 8;
    if (payload != 0)
    {
      slot_data = (u8 *) (write_index * 24 + (u32) slot_data);
      *((S_8003E39C_blk16 *) slot_data) = *((S_8003E39C_blk16 *) payload);
    }
  }
  {
    register s32 slot_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    slot_offset = write_index * 24;
    D_800814D1 = (D_800814D1 + 1) & 0x1F;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    return (S_80083968 *) ((u8 *) D_80083968 + slot_offset);
  }
}
