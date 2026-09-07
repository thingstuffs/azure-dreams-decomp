#include "common.h"

typedef struct Scratch800D1A48
{
  u8 pad00[8];
  s32 data08;
  s32 data0C;
  s32 data10;
  s32 data14;
  u8 pad18[8];
  u8 *data20;
  u16 flags24;
  u8 pad26[0x4A];
  u16 data70;
  u16 data72;
  u8 pad74[4];
  u16 data78;
  u16 data7A;
  u8 pad7C[4];
  u16 data80;
  u16 data82;
  u8 pad84[4];
  u16 data88;
  u16 data8A;
  u8 pad8C[0x34];
  u32 dataC0;
  u8 padC4[0x2C];
  u16 dataF0;
  u16 dataF2;
  u16 dataF4;
  u16 dataF6;
  u16 dataF8;
  u16 dataFA;
  u16 dataFC;
  u16 dataFE;
  u8 pad100[8];
  u16 data108;
  u16 data10A;
} Scratch800D1A48;
extern void *func_800654B0(u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *, u16 *);
void *func_800D71A8(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, u8 *arg4)
{
  register Scratch800D1A48 *scratch;
  register s32 index ASM_REG("$22");
  register s32 arg1_reg;
  register s32 arg2_entry ASM_REG("$8");
  register s32 arg2_reg;
  register u8 *arg3_reg ASM_REG("$21");
  u8 *selected;
  register u8 *s7 ASM_REG("$23");
  register u8 *s1 ASM_REG("$17");
  register u8 *s2 ASM_REG("$18");
  register u8 *s3 ASM_REG("$19");
  register u8 *s4 ASM_REG("$20");
  s32 last;
  arg1_reg = arg1;
  ASM_KEEP_NV(arg1_reg);
  arg2_entry = arg2;
  ASM_KEEP_NV(arg2_entry);
  arg2_reg = arg2_entry;
  ASM_KEEP_NV(arg2_reg);
  arg3_reg = arg3;
  ASM_KEEP_NV(arg3_reg);
  selected = 0;
  ASM_KEEP_NV(selected);
  index = (u32) selected;
  ASM_KEEP_NV(index);
  s7 = arg4;
  scratch = (Scratch800D1A48 *) 0x1F800000;
  {
  register s32 count_load ASM_REG("$2");
  count_load = *((s16 *) (((u8 *) arg0) + 0x9E));
  if (count_load > 0)
  {
    arg1_reg = count_load;
    do
    {
      u8 *entry = *((u8 **) (((u8 *) arg0) + 0xA4));
      if (entry == 0)
      {
        index += 1;
        arg0 += 4;
      }
      else
      {
        selected = entry + 0x20;
        ASM_KEEP(selected);
        if ((*((u16 *) (((u8 *) arg3_reg) + 6))) == (*((u16 *) (((u8 *) selected) + 6))))
        {
          break;
        }
        index += 1;
        arg0 += 4;
      }
    }
    while (index < arg1_reg);
  }
  }
  if ((*((s16 *) (((u8 *) selected) + 2))) > 0)
  {
    index = 0;
    outer_loop:
    {
      register s32 offset ASM_REG("$2");
      offset = (index * 3) << 4;
      ASM_KEEP_NV(offset);
      offset += 8;
      s3 = selected + offset;
      s4 = *((u8 **) (((u8 *) s3) + 8));
      ASM_KEEP_DEP_NV(s7, s4);
      s1 = s7 + 4;
      s2 = s4 + 1;
      ASM_KEEP(s2);
      inner_loop:
      if (!(s4[0] & 0x20))
      {
        scratch->data08 = s2[7];
        scratch->data0C = s2[8];
        scratch->data10 = s2[9];
        scratch->data14 = s2[10];
        {
          s32 value;
          register u8 flag_byte ASM_REG("$2");
          flag_byte = s4[0];
          if ((flag_byte ^ scratch->flags24) & 1)
          {
            s32 base;
            value = (0 - ((((s32) (*((volatile u8 *) (((u8 *) s2) + 1)))) << 24) >> 24)) - (*((u16 *) (((u8 *) scratch) + 0x108)));
            base = *((u16 *) (((u8 *) scratch) + 0x10));
            scratch->data80 = value;
            *((volatile u16 *) (((u8 *) scratch) + 0x70)) = value;
            value -= base;
          }
          else
          {
            s32 base;
            base = *((u16 *) (((u8 *) scratch) + 0x10));
            value = ((((s32) (*((volatile u8 *) (((u8 *) s2) + 1)))) << 24) >> 24) + (*((u16 *) (((u8 *) scratch) + 0x108)));
            scratch->data80 = value;
            scratch->data70 = value;
            value += base;
          }
          scratch->data88 = value;
          scratch->data78 = value;
        }
        {
          s32 value;
          if ((arg3_reg[0] ^ (*((u16 *) (((u8 *) ((u8 *) arg2_reg)) + 0x14)))) & 1)
          {
            value = scratch->data80 - ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 2)))) << 24) >> 24);
            scratch->data80 = value;
            *((volatile u16 *) (((u8 *) scratch) + 0x70)) = value;
            value = (*((u16 *) (((u8 *) scratch) + 0x88))) - ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 2)))) << 24) >> 24);
          }
          else
          {
            value = scratch->data80 + ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 2)))) << 24) >> 24);
            scratch->data80 = value;
            scratch->data70 = value;
            value = (*((u16 *) (((u8 *) scratch) + 0x88))) + ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 2)))) << 24) >> 24);
          }
          scratch->data88 = value;
          scratch->data78 = value;
        }
        {
          s32 value;
          register u8 flag_byte ASM_REG("$2");
          flag_byte = s4[0];
          if ((flag_byte ^ scratch->flags24) & 2)
          {
            s32 base;
            value = (0 - ((((s32) (*((volatile u8 *) (((u8 *) s2) + 2)))) << 24) >> 24)) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
            base = *((u16 *) (((u8 *) scratch) + 0x14));
            scratch->data7A = value;
            *((volatile u16 *) (((u8 *) scratch) + 0x72)) = value;
            value -= base;
          }
          else
          {
            s32 base;
            base = *((u16 *) (((u8 *) scratch) + 0x14));
            value = ((((s32) (*((volatile u8 *) (((u8 *) s2) + 2)))) << 24) >> 24) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
            scratch->data7A = value;
            scratch->data72 = value;
            value += base;
          }
          scratch->data8A = value;
          scratch->data82 = value;
        }
        {
          s32 value;
          if ((arg3_reg[0] ^ (*((u16 *) (((u8 *) ((u8 *) arg2_reg)) + 0x14)))) & 2)
          {
            value = scratch->data7A - ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 3)))) << 24) >> 24);
            scratch->data7A = value;
            *((volatile u16 *) (((u8 *) scratch) + 0x72)) = value;
            value = scratch->data8A - ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 3)))) << 24) >> 24);
          }
          else
          {
            value = scratch->data7A + ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 3)))) << 24) >> 24);
            scratch->data7A = value;
            scratch->data72 = value;
            value = scratch->data8A + ((((s32) (*((volatile u8 *) (((u8 *) arg3_reg) + 3)))) << 24) >> 24);
          }
          scratch->data8A = value;
          scratch->data82 = value;
        }
        ASM_KEEP_NV(scratch);
        func_800654B0(&scratch->data70, &scratch->data78, &scratch->data80, &scratch->data88, &scratch->dataF0, &scratch->dataF4, &scratch->dataF8, &scratch->dataFC, (u16 *) (((u8 *) scratch) + 0x90), (u16 *) (((u8 *) scratch) + 0x94));
        *((u16 *) (((u8 *) s1) + 4)) = scratch->dataF0 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) s1) + 6)) = scratch->dataF2 + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) s1) + 0xC)) = scratch->dataF4 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) s1) + 0xE)) = scratch->dataF6 + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) s1) + 0x14)) = scratch->dataF8 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) s1) + 0x16)) = scratch->dataFA + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) s1) + 0x1C)) = scratch->dataFC + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        last = scratch->dataFE + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((s16 *) (((u8 *) s1) + 0x1E)) = last;
        {
          s32 a2_result;
          register s32 check_value ASM_REG("$2");
          s32 v1_result;
          register s32 a1_result;
          s32 merged;
          a2_result = 0;
          if (((u16) ((*((u16 *) (((u8 *) s1) + 4))) + 0x20)) < 0x181U)
          {
            check_value = (u16) ((*((u16 *) (((u8 *) s1) + 6))) + 0x20);
            a2_result = check_value < 0x121U;
          }
          v1_result = 0;
          if (((u16) ((*((u16 *) (((u8 *) s1) + 0xC))) + 0x20)) < 0x181U)
          {
            v1_result = ((u16) ((*((u16 *) (((u8 *) s1) + 0xE))) + 0x20)) < 0x121U;
          }
          a1_result = 0;
          check_value = (u16) ((*((u16 *) (((u8 *) s1) + 0x14))) + 0x20);
          a2_result |= v1_result;
          if (check_value < 0x181U)
          {
            check_value = (u16) ((*((u16 *) (((u8 *) s1) + 0x16))) + 0x20);
            a1_result = check_value < 0x121U;
          }
          v1_result = 0;
          merged = a2_result | a1_result;
          if (((u16) ((*((u16 *) (((u8 *) s1) + 0x1C))) + 0x20)) < 0x181U)
          {
            v1_result = ((u16) (last + 0x20)) < 0x121U;
          }
          check_value = merged | v1_result;
          if (check_value != 0)
          {
            *((s8 *) (((u8 *) s1) + (-1))) = 9;
            scratch->data10 += scratch->data08;
            if (scratch->data10 & 0x100)
            {
              scratch->data10 -= 1;
            }
            scratch->data14 += scratch->data0C;
            if (scratch->data14 & 0x100)
            {
              scratch->data14 -= 1;
            }
            scratch->data14 <<= 8;
            scratch->data0C <<= 8;
            *((s32 *) (((u8 *) s1) + 8)) = (scratch->data0C + scratch->data08) + (((*((u16 *) (((u8 *) ((u8 *) arg2_reg)) + 0x12))) + (*((u16 *) (((u8 *) s2) + 5)))) << 16);
            *((s16 *) (((u8 *) s1) + 0x10)) = (*((u16 *) (((u8 *) scratch) + 0x0C))) + (*((u16 *) (((u8 *) scratch) + 0x10)));
            {
              register u16 mode ASM_REG("$3");
              register u16 value ASM_REG("$2");
              mode = *((u16 *) (((u8 *) ((u8 *) arg2_reg)) + 0x10));
              if (mode != 0)
              {
                value = mode + ((*((u16 *) (((u8 *) s2) + 3))) & 0xFF9F);
              }
              else
              {
                value = *((u16 *) (((u8 *) s2) + 3));
              }
              *((u16 *) (((u8 *) s1) + 0x12)) = value;
            }
            *((s16 *) (((u8 *) s1) + 0x18)) = (*((u16 *) (((u8 *) scratch) + 0x14))) + (*((u16 *) (((u8 *) scratch) + 0x08)));
            {
              register s32 right_edge ASM_REG("$3");
              register s32 left_edge ASM_REG("$2");
              right_edge = *((u16 *) (((u8 *) scratch) + 0x14));
              right_edge += *((u16 *) (((u8 *) scratch) + 0x10));
              *((s16 *) (((u8 *) s1) + 0x20)) = right_edge;
              arg1_reg = *((s16 *) (((u8 *) s1) + 4));
              left_edge = *((s16 *) (((u8 *) s1) + 0x1C));
              if (left_edge < arg1_reg)
              {
                *((u8 *) (((u8 *) s1) + 0x10)) -= 1;
                *((u8 *) (((u8 *) s1) + 0x20)) -= 1;
              }
            }
            if ((*((s16 *) (((u8 *) s1) + 6))) > (*((s16 *) (((u8 *) s1) + 0x1E))))
            {
              *((u8 *) (((u8 *) s1) + 0x19)) -= 1;
              *((u8 *) (((u8 *) s1) + 0x21)) -= 1;
            }
            {
              register u16 attr ASM_REG("$3");
              register u8 flags;
              attr = *((u16 *) (((u8 *) s3) + 0x14));
              flags = s2[0];
              *((u8 *) (((u8 *) s3) + 0xF)) = flags;
              if (attr & 8)
              {
                register u8 updated ASM_REG("$2");
                if (attr & 4)
                {
                  updated = flags | 2;
                }
                else
                {
                  updated = flags & 0xFD;
                }
                *((u8 *) (((u8 *) s3) + 0xF)) = updated;
                ASM_KEEP(attr);
              }
            }
            {
              register u8 flags ASM_REG("$2");
              if ((*((u16 *) (((u8 *) s3) + 0x14))) & 0x10)
              {
                flags = (*((u8 *) (((u8 *) s3) + 0xF))) | 1;
              }
              else
              {
                flags = (*((u8 *) (((u8 *) s3) + 0xF))) & 0xFE;
              }
              *((u8 *) (((u8 *) s3) + 0xF)) = flags;
            }
            *((s32 *) (((u8 *) s1) + 0)) = *((s32 *) (((u8 *) s3) + 0xC));
            if (!((*((u16 *) (((u8 *) selected) + 4))) & 0x8000))
            {
              register u32 table_index ASM_REG("$3");
              register u8 *table_base ASM_REG("$2");
              register u32 low = 0x00FFFFFF;
              register u32 high = 0xFF000000;
              table_index = scratch->dataC0;
              table_base = scratch->data20;
              {
                register u32 *table_ptr ASM_REG("$3");
                register u32 dst_value ASM_REG("$2");
                register u32 table_value ASM_REG("$3");
                table_ptr = (u32 *) ((table_index << 2) + ((u32) table_base));
                ASM_KEEP(table_ptr);
                dst_value = *((u32 *) (((u8 *) s7) + 0));
                table_value = *table_ptr;
                dst_value &= high;
                table_value &= low;
                dst_value |= table_value;
                *((u32 *) (((u8 *) s7) + 0)) = dst_value;
              }
              table_index = scratch->dataC0;
              table_base = scratch->data20;
              {
                u32 t = ((u32) s7) & low;
                *((u32 *) ((table_index << 2) + ((u32) table_base))) = ((*((u32 *) ((table_index << 2) + ((u32) table_base)))) & high) | t;
              }
            }
            s1 += 0x28;
            ASM_KEEP(s1);
            s7 += 0x28;
          }
        }
      }
      s2 += 0xC;
      if (((s8) s4[0]) >= 0)
      {
        s4 += 0xC;
        goto inner_loop;
      }
      ASM_KEEP(s2);
      index += 1;
      if (index < (*((s16 *) (((u8 *) selected) + 2))))
      {
        goto outer_loop;
      }
    }

  }
  return s7;
}
