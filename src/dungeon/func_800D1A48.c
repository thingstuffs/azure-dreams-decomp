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
/* Build visible textured quads for the matching sprite and link them into the ordering table. */
void *func_800D71A8(u8 *sprite_list, s32 count_hint, s32 render_state_addr, u8 *placement, u8 *packet_buf)
{
  register Scratch800D1A48 *scratch;
  register s32 index ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register s32 count_or_x;
  s32 state_addr;
  register s32 render_state;
  register u8 *sprite_placement ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  u8 *sprite;
  u8 *packet;
  u8 *packet_data;
  u8 *quad_data;
  u8 *part;
  register u8 *quad ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  s32 bottom_y;
  count_or_x = count_hint;
  state_addr = render_state_addr;
  ASM_KEEP_NV(state_addr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  render_state = state_addr;
  ASM_KEEP_NV(render_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  sprite_placement = placement;
  ASM_KEEP_NV(sprite_placement);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  sprite = 0;
  index = (u32) sprite;
  packet = packet_buf;
  scratch = (Scratch800D1A48 *) 0x1F800000;
  {
    s32 sprite_count;
    sprite_count = *((s16 *) (((u8 *) sprite_list) + 0x9E));
    if (sprite_count > 0)
    {
      count_or_x = sprite_count;
      do
      {
        u8 *sprite_entry = *((u8 **) (((u8 *) sprite_list) + 0xA4));
        if (sprite_entry == 0)
        {
          index += 1;
          sprite_list += 4;
        }
        else
        {
          sprite = sprite_entry + 0x20;
          if ((*((u16 *) (((u8 *) sprite_placement) + 6))) == (*((u16 *) (((u8 *) sprite) + 6))))
          {
            break;
          }
          index += 1;
          sprite_list += 4;
        }
      }
      while (index < count_or_x);
    }
  }
  if ((*((s16 *) (((u8 *) sprite) + 2))) > 0)
  {
    index = 0;
    next_part:
    {
      s32 part_offset;
      part_offset = (index * 3) << 4;
      part_offset += 8;
      part = sprite + part_offset;
      quad = *((u8 **) (((u8 *) part) + 8));
      packet_data = packet + 4;
      quad_data = quad + 1;
      next_quad:
      if (!(quad[0] & 0x20))
      {
        scratch->data08 = quad_data[7];
        scratch->data0C = quad_data[8];
        scratch->data10 = quad_data[9];
        scratch->data14 = quad_data[10];
        {
          s32 x;
          u8 quad_flags;
          quad_flags = quad[0];
          if ((quad_flags ^ scratch->flags24) & 1)
          {
            s32 width;
            x = (0 - ((((s32) (*((volatile u8 *) (((u8 *) quad_data) + 1)))) << 24) >> 24)) - (*((u16 *) (((u8 *) scratch) + 0x108)));
            width = *((u16 *) (((u8 *) scratch) + 0x10));
            scratch->data80 = x;
            *((volatile u16 *) (((u8 *) scratch) + 0x70)) = x;
            x -= width;
          }
          else
          {
            s32 width;
            width = *((u16 *) (((u8 *) scratch) + 0x10));
            x = ((((s32) (*((volatile u8 *) (((u8 *) quad_data) + 1)))) << 24) >> 24) + (*((u16 *) (((u8 *) scratch) + 0x108)));
            scratch->data80 = x;
            scratch->data70 = x;
            x += width;
          }
          scratch->data88 = x;
          scratch->data78 = x;
        }
        {
          s32 x;
          if ((sprite_placement[0] ^ (*((u16 *) (((u8 *) ((u8 *) render_state)) + 0x14)))) & 1)
          {
            x = scratch->data80 - ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 2)))) << 24) >> 24);
            scratch->data80 = x;
            *((volatile u16 *) (((u8 *) scratch) + 0x70)) = x;
            x = (*((u16 *) (((u8 *) scratch) + 0x88))) - ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 2)))) << 24) >> 24);
          }
          else
          {
            x = scratch->data80 + ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 2)))) << 24) >> 24);
            scratch->data80 = x;
            scratch->data70 = x;
            x = (*((u16 *) (((u8 *) scratch) + 0x88))) + ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 2)))) << 24) >> 24);
          }
          scratch->data88 = x;
          scratch->data78 = x;
        }
        {
          s32 y;
          u8 quad_flags;
          quad_flags = quad[0];
          if ((quad_flags ^ scratch->flags24) & 2)
          {
            s32 height;
            y = (0 - ((((s32) (*((volatile u8 *) (((u8 *) quad_data) + 2)))) << 24) >> 24)) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
            height = *((u16 *) (((u8 *) scratch) + 0x14));
            scratch->data7A = y;
            *((volatile u16 *) (((u8 *) scratch) + 0x72)) = y;
            y -= height;
          }
          else
          {
            s32 height;
            height = *((u16 *) (((u8 *) scratch) + 0x14));
            y = ((((s32) (*((volatile u8 *) (((u8 *) quad_data) + 2)))) << 24) >> 24) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
            scratch->data7A = y;
            scratch->data72 = y;
            y += height;
          }
          scratch->data8A = y;
          scratch->data82 = y;
        }
        {
          s32 y;
          if ((sprite_placement[0] ^ (*((u16 *) (((u8 *) ((u8 *) render_state)) + 0x14)))) & 2)
          {
            y = scratch->data7A - ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 3)))) << 24) >> 24);
            scratch->data7A = y;
            *((volatile u16 *) (((u8 *) scratch) + 0x72)) = y;
            y = scratch->data8A - ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 3)))) << 24) >> 24);
          }
          else
          {
            y = scratch->data7A + ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 3)))) << 24) >> 24);
            scratch->data7A = y;
            scratch->data72 = y;
            y = scratch->data8A + ((((s32) (*((volatile u8 *) (((u8 *) sprite_placement) + 3)))) << 24) >> 24);
          }
          scratch->data8A = y;
          scratch->data82 = y;
        }
        ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800654B0(&scratch->data70, &scratch->data78, &scratch->data80, &scratch->data88, &scratch->dataF0, &scratch->dataF4, &scratch->dataF8, &scratch->dataFC, (u16 *) (((u8 *) scratch) + 0x90), (u16 *) (((u8 *) scratch) + 0x94));
        *((u16 *) (((u8 *) packet_data) + 4)) = scratch->dataF0 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) packet_data) + 6)) = scratch->dataF2 + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) packet_data) + 0xC)) = scratch->dataF4 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) packet_data) + 0xE)) = scratch->dataF6 + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) packet_data) + 0x14)) = scratch->dataF8 + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        *((u16 *) (((u8 *) packet_data) + 0x16)) = scratch->dataFA + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((u16 *) (((u8 *) packet_data) + 0x1C)) = scratch->dataFC + (*((u16 *) (((u8 *) scratch) + 0xB8)));
        bottom_y = scratch->dataFE + (*((u16 *) (((u8 *) scratch) + 0xBA)));
        *((s16 *) (((u8 *) packet_data) + 0x1E)) = bottom_y;
        {
          s32 pair_visible;
          s32 clip_test;
          s32 corner_visible;
          register s32 third_visible;
          s32 any_visible;
          pair_visible = 0;
          if (((u16) ((*((u16 *) (((u8 *) packet_data) + 4))) + 0x20)) < 0x181U)
          {
            clip_test = (u16) ((*((u16 *) (((u8 *) packet_data) + 6))) + 0x20);
            pair_visible = clip_test < 0x121U;
          }
          corner_visible = 0;
          if (((u16) ((*((u16 *) (((u8 *) packet_data) + 0xC))) + 0x20)) < 0x181U)
          {
            corner_visible = ((u16) ((*((u16 *) (((u8 *) packet_data) + 0xE))) + 0x20)) < 0x121U;
          }
          third_visible = 0;
          clip_test = (u16) ((*((u16 *) (((u8 *) packet_data) + 0x14))) + 0x20);
          pair_visible |= corner_visible;
          if (clip_test < 0x181U)
          {
            clip_test = (u16) ((*((u16 *) (((u8 *) packet_data) + 0x16))) + 0x20);
            third_visible = clip_test < 0x121U;
          }
          corner_visible = 0;
          any_visible = pair_visible | third_visible;
          if (((u16) ((*((u16 *) (((u8 *) packet_data) + 0x1C))) + 0x20)) < 0x181U)
          {
            corner_visible = ((u16) (bottom_y + 0x20)) < 0x121U;
          }
          clip_test = any_visible | corner_visible;
          if (clip_test != 0)
          {
            *((s8 *) (((u8 *) packet_data) + (-1))) = 9;
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
            *((s32 *) (((u8 *) packet_data) + 8)) = (scratch->data0C + scratch->data08) + (((*((u16 *) (((u8 *) ((u8 *) render_state)) + 0x12))) + (*((u16 *) (((u8 *) quad_data) + 5)))) << 16);
            *((s16 *) (((u8 *) packet_data) + 0x10)) = (*((u16 *) (((u8 *) scratch) + 0x0C))) + (*((u16 *) (((u8 *) scratch) + 0x10)));
            {
              u16 blend_mode;
              u16 tpage;
              blend_mode = *((u16 *) (((u8 *) ((u8 *) render_state)) + 0x10));
              if (blend_mode != 0)
              {
                tpage = blend_mode + ((*((u16 *) (((u8 *) quad_data) + 3))) & 0xFF9F);
              }
              else
              {
                tpage = *((u16 *) (((u8 *) quad_data) + 3));
              }
              *((u16 *) (((u8 *) packet_data) + 0x12)) = tpage;
            }
            *((s16 *) (((u8 *) packet_data) + 0x18)) = (*((u16 *) (((u8 *) scratch) + 0x14))) + (*((u16 *) (((u8 *) scratch) + 0x08)));
            {
              s32 bottom_right_uv;
              s32 right_x;
              s32 count_or_x;
              bottom_right_uv = *((u16 *) (((u8 *) scratch) + 0x14));
              bottom_right_uv += *((u16 *) (((u8 *) scratch) + 0x10));
              *((s16 *) (((u8 *) packet_data) + 0x20)) = bottom_right_uv;
              count_or_x = *((s16 *) (((u8 *) packet_data) + 4));
              right_x = *((s16 *) (((u8 *) packet_data) + 0x1C));
              if (right_x < count_or_x)
              {
                *((u8 *) (((u8 *) packet_data) + 0x10)) -= 1;
                *((u8 *) (((u8 *) packet_data) + 0x20)) -= 1;
              }
            }
            if ((*((s16 *) (((u8 *) packet_data) + 6))) > (*((s16 *) (((u8 *) packet_data) + 0x1E))))
            {
              *((u8 *) (((u8 *) packet_data) + 0x19)) -= 1;
              *((u8 *) (((u8 *) packet_data) + 0x21)) -= 1;
            }
            {
              u16 part_flags;
              register u8 flags;
              do {
                  part_flags = *((u16 *) (((u8 *) part) + 0x14));
              } while (0);
              flags = quad_data[0];
              *((u8 *) (((u8 *) part) + 0xF)) = flags;
              if (part_flags & 8)
              {
                u8 draw_flags;
                if (part_flags & 4)
                {
                  draw_flags = flags | 2;
                }
                else
                {
                  draw_flags = flags & 0xFD;
                }
                *((u8 *) (((u8 *) part) + 0xF)) = draw_flags;
              }
            }
            {
              u8 flags;
              if ((*((u16 *) (((u8 *) part) + 0x14))) & 0x10)
              {
                flags = (*((u8 *) (((u8 *) part) + 0xF))) | 1;
              }
              else
              {
                flags = (*((u8 *) (((u8 *) part) + 0xF))) & 0xFE;
              }
              *((u8 *) (((u8 *) part) + 0xF)) = flags;
            }
            *((s32 *) (((u8 *) packet_data) + 0)) = *((s32 *) (((u8 *) part) + 0xC));
            if (!((*((u16 *) (((u8 *) sprite) + 4))) & 0x8000))
            {
              u32 depth;
              u8 *ordering_table;
              register u32 addr_mask = 0x00FFFFFF;
              register u32 length_mask = 0xFF000000;
              depth = scratch->dataC0;
              ordering_table = scratch->data20;
              {
                u32 *ot_entry;
                u32 packet_tag;
                u32 ot_tag;
                ot_entry = (u32 *) ((depth << 2) + ((u32) ordering_table));
                do {
                    packet_tag = *((u32 *) (((u8 *) packet) + 0));
                } while (0);
                ot_tag = *ot_entry;
                packet_tag &= length_mask;
                ot_tag &= addr_mask;
                packet_tag |= ot_tag;
                *((u32 *) (((u8 *) packet) + 0)) = packet_tag;
              }
              depth = scratch->dataC0;
              ordering_table = scratch->data20;
              {
                u32 packet_addr = ((u32) packet) & addr_mask;
                *((u32 *) ((depth << 2) + ((u32) ordering_table))) = ((*((u32 *) ((depth << 2) + ((u32) ordering_table)))) & length_mask) | packet_addr;
              }
            }
            packet_data += 0x28;
            packet += 0x28;
          }
        }
      }
      quad_data += 0xC;
      if (((s8) quad[0]) >= 0)
      {
        quad += 0xC;
        goto next_quad;
      }
      index += 1;
      if (index < (*((s16 *) (((u8 *) sprite) + 2))))
      {
        goto next_part;
      }
    }

  }
  return packet;
}
