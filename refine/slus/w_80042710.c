#include "common.h"

#ifdef __mips__
#define PIN_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#define PIN_BARRIER(v) __asm__ __volatile__("" : : "r"(v))
#define PIN_BARRIER2(a, b) __asm__ __volatile__("" : : "r"(a), "r"(b))
#else
#define PIN_KEEP(v) ((void)0)
#define PIN_BARRIER(v) ((void)0)
#define PIN_BARRIER2(a, b) ((void)0)
#endif
typedef struct
{
  u8 a;
  u8 b;
  u8 c;
} Slot1_80042710;
typedef struct
{
  s8 a;
  s8 b;
} Slot2_80042710;
typedef union
{
  u32 raw;
  struct
  {
    u8 b0;
    u8 tag;
    u8 b2;
    u8 b3;
  } f;
} Grp48_80042710;
typedef struct
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u8 f04;
  u8 f05;
  u16 f06;
  Slot1_80042710 slots1[3];
  u8 f11;
  u8 f12;
  u8 f13;
  u32 f14;
  u32 f18;
  u32 f1c;
  u16 f20;
  u16 f22;
  u16 f24;
  u8 f26;
  u8 f27;
  u8 f28;
  u16 f2a;
  Slot2_80042710 slots2[4];
  u8 name[13];
  u8 pad41[2];
  u8 f43;
  u8 f44;
  u8 f45;
  Grp48_80042710 grp48;
  void *f4c;
  u32 pad50;
  u32 f54;
} S_80042710;
extern void func_80041E70(S_80042710 *a0);
/* Copy record fields, merge flags, update the tagged group, and refresh the destination. */
void func_80042710(S_80042710 *dst_record, S_80042710 *src_record)
{
  register S_80042710 *src ASM_REG("$10") = src_record;
  register s32 index ASM_REG("$6");
  u8 field_00;
  field_00 = src->f00;
  PIN_BARRIER(field_00);
  {
    register S_80042710 *dst ASM_REG("$9") = dst_record;
    PIN_KEEP(dst);
    dst->f00 = field_00;
    dst->f01 = src->f01;
    dst->f02 = src->f02;
    dst->f03 = src->f03;
    dst->f04 = src->f04;
    dst->f05 = src->f05;
    dst->f06 = src->f06;
    index = 2;
    {
      register u8 *src_slot1 ASM_REG("$4") = (u8 *)src + 6;
      register u8 *dst_slot1 ASM_REG("$3") = (u8 *)dst + 6;
      do
      {
        dst_slot1[8] = src_slot1[8];
        dst_slot1[10] = src_slot1[10];
        src_slot1 -= 3;
        dst_slot1 -= 3;
        index--;
      }
      while (index >= 0);
    }
    dst->f11 = src->f11;
    dst->f12 = src->f12;
    dst->f13 = src->f13;
    dst->f14 = (dst->f14 | src->f14) & 0xFFEFFFFF;
    dst->f18 = src->f18;
    dst->f1c = (dst->f1c | src->f1c) & 0xEFF6FEFF;
    dst->f20 = src->f20;
    dst->f22 = src->f22;
    dst->f24 = src->f24;
    dst->f26 = src->f26;
    dst->f27 = src->f27;
    dst->f28 = src->f28;
    dst->f2a = src->f2a;
    index = 3;
    {
      register s8 *src_slot2 ASM_REG("$8") = (s8 *)src + 6;
      register s8 *dst_slot2 ASM_REG("$7") = (s8 *)dst + 6;
      register s32 slot_a ASM_REG("$2");
      register s32 slot_b;
      do
      {
        slot_a = src_slot2[44];
        slot_b = src_slot2[45];
        dst_slot2[44] = slot_a;
        dst_slot2[45] = slot_b;
        PIN_BARRIER2(slot_a, slot_b);
        src_slot2 -= 2;
        index--;
        dst_slot2 -= 2;
      }
      while (index >= 0);
    }
    index = 12;
    do
    {
      dst->name[index] = src->name[index];
      index--;
    }
    while (index >= 0);
    dst->f43 = src->f43;
    dst->f44 = src->f44;
    if (dst->grp48.f.tag == 0)
    {
      dst->grp48 = src->grp48;
    }
    if (src->grp48.f.tag == 0xF)
    {
      dst->grp48 = src->grp48;
      if (src->f4c != 0)
      {
        dst->f4c = &dst->grp48;
      }
    }
    dst->f45 = src->f45;
    {
      u32 field_54 = src->f54;
      PIN_BARRIER(field_54);
      {
        S_80042710 *refresh_dst = dst;
        PIN_KEEP(refresh_dst);
        dst->f54 = field_54;
        func_80041E70(refresh_dst);
      }
    }
  }
}
