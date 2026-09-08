#include "common.h"
typedef struct S_800847D0
{
  u32 flags1;
  u32 flags2;
  u32 field8;
  u32 fieldC;
  volatile u32 field10;
  volatile u32 field14;
  u32 field18;
  s16 field1C;
  s16 field1E;
  s16 field20;
  s16 field22;
  u8 pad24[2];
  s16 field26;
  u8 field28;
  u8 pad29[7];
  s8 field30;
  s8 field31;
  s8 field32;
  s8 field33;
} S_800847D0;
typedef struct S_80084858
{
  void (*field0)(void);
  s32 field4;
  s16 field8;
  s16 fieldA;
  s32 fieldC;
  s16 field10;
  s16 field12;
  s16 field14;
  s16 field16;
  s16 field18;
} S_80084858;
typedef struct S_80084864
{
  s32 v;
  u8 pad4[8];
} S_80084864;
extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;
extern S_80084864 D_80084864;
extern int *func_8003F534(void);
extern int func_80054AF0(int arg0);
extern void func_80054C58(void);
extern void func_80054CD4(void);
extern void func_80054E00(s32 arg0);
/* Initializes status from the current record or dispatches a message-specific update. */
void func_80054B08(s32 message)
{
  s32 message_type = message & 0xF000;
  switch (message_type)
  {
    case 0:
    {
      register S_800847D0 *status ASM_REG("$7");   /* MATCH pin: slus-diff */
      register u32 offset_mask ASM_REG("$6");   /* MATCH pin: slus-diff */
      u16 record_value;
      u32 first_offset;
      register u32 second_offset ASM_REG("$4");   /* MATCH pin: slus-diff */
      int *record;
      int offset_base;
      u8 first_tag;
      u8 second_tag;
      u32 flags;
      record = func_8003F534();
      offset_mask = 0xFF0000;
      ASM_KEEP(offset_mask);   /* MATCH pin: slus-diff */
      record_value = *((u16 *) record);
      status = &D_800847D0;
      status->field1C = record_value;
      offset_base = record[1];
      ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
      first_offset = record[2];
      offset_mask |= 0xFFFF;
      status->field10 = first_offset;
      second_offset = record[3];
      first_tag = (u8) (first_offset >> 24);
      first_offset = first_offset & offset_mask;
      status->field10 = first_offset;
      first_offset = first_offset - 0x20;
      first_offset = first_offset + offset_base;
      status->field31 = first_tag;
      status->field10 = first_offset;
      status->field18 = 0;
      second_tag = (u8) (second_offset >> 24);
      status->field14 = second_offset;
      second_offset = second_offset & offset_mask;
      status->field14 = second_offset;
      second_offset = second_offset + 0x20;
      status->field33 = second_tag;
      flags = D_800847D0.flags1;
      second_offset = second_offset + offset_base;
      *(u32 *) &status->field14 = second_offset;
      if (flags & 0x400)
      {
        D_800847D0.flags1 = flags | 0x4000;
        D_80084864.v = 2;
        break;
      }
      if (status->flags2 & 0x200)
      {
        break;
      }
      {
        S_80084858 *update_state = &D_80084858;
        s16 signed_value = (s16) record_value;
        int initial_value;
        update_state->field4 = 0;
        initial_value = func_80054AF0(signed_value);
        update_state->field8 = initial_value;
        update_state->fieldA = initial_value;
      }
      func_80054C58();
      func_80054CD4();
      break;
    }

    case 0x1000:
      func_80054E00(0x74);
      break;

    case 0x2000:
      func_80054E00(0xE4);
      break;

    case 0x4000:
      func_80054E00(0xF4);
      break;

  }

}
