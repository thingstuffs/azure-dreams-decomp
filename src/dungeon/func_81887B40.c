#include "common.h"
typedef struct 
{
  u8 *value;
  u8 pad[8];
} Global83160;
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
  u16 pad;
} TableEntry;
extern s16 D_8002632A;
extern u8 D_80026478[];
extern Global83160 D_80083160;
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
/* Build and enqueue interpolated, depth-sorted shaded lines for a linked list. */
s32 func_80025340(void *first_owner, void *first_vertices, void *first_line)
{
  register TableEntry *point_table = (TableEntry *) D_80026478;
  {
    u8 *render_data = D_80083160.value;
    void *owner = first_owner;
    void *vertex_data = first_vertices;
    void *line_data = first_line;
    register u8 **render_state ASM_REG("$22") = (u8 **) &D_80083160; /* MATCH: keep render_state in s6 across the loop, preserving retail register allocation. */
    register u8 *scratch ASM_REG("$17") = (u8 *) 0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *line_packet ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *packet;
    u32 red_blue;
    u32 green;
    void *next_node;
    s32 avg_depth;
    s16 blend;
    s32 point_index;
    s32 color_word;
    ASM_KEEP(render_state);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    *(u8 **)(scratch + 0x18) = *(u8 **)(render_data + 0x8D0);
    *(u8 **)(scratch + 0x20) = render_data + 0xB0;
    for (;;)
    {
      line_packet = *(u8 **)(scratch + 0x18);
      *(u8 **)(scratch + 0x18) = line_packet + 0x14;
      blend = *(s16 *)((u8 *) line_data + 6);
      if (blend >= 0)
      {
        *(u16 *)(scratch + 0) = *(u16 *)((u8 *) vertex_data + 0xE);
        *(u16 *)(scratch + 2) = *(u16 *)((u8 *) vertex_data + 0x12);
        *(u16 *)(scratch + 4) = *(u16 *)((u8 *) vertex_data + 0x16);
        *(s32 *)(scratch + 0xC0) = func_80065420(scratch, line_packet + 8, scratch + 0x90, scratch + 0x94);
        *(u16 *)(scratch + 0) =
            (*(u16 *)((u8 *) vertex_data + 0xE)) + ((((*(s16 *)((u8 *) vertex_data + 2)) - (*(s16 *)((u8 *) vertex_data + 0xE))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
        *(u16 *)(scratch + 2) =
            (*(u16 *)((u8 *) vertex_data + 0x12)) + ((((*(s16 *)((u8 *) vertex_data + 6)) - (*(s16 *)((u8 *) vertex_data + 0x12))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
        *(u16 *)(scratch + 4) =
            (*(u16 *)((u8 *) vertex_data + 0x16)) + ((((*(s16 *)((u8 *) vertex_data + 0xA)) - (*(s16 *)((u8 *) vertex_data + 0x16))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
        point_index = (*(s16 *)((u8 *) owner + 0x22)) + 0x10;
        if (D_8002632A < point_index)
        {
          s32 table_index;
          u16 coord;
          point_table[point_index].x = *(u16 *)(scratch + 0);
          table_index = *(s16 *)((u8 *) owner + 0x22);
          coord = *(u16 *)(scratch + 2);
          table_index += 0x10;
          point_table[table_index].y = coord;
          table_index = *(s16 *)((u8 *) owner + 0x22);
          coord = *(u16 *)(scratch + 4);
          table_index += 0x10;
          point_table[table_index].z = coord;
        }
      }
      else
      {
        *(u16 *)(scratch + 0) = (*(u16 *)((u8 *) vertex_data + 2)) - ((((*(s16 *)((u8 *) vertex_data + 0xE)) - (*(s16 *)((u8 *) vertex_data + 2))) * blend) >> 8);
        *(u16 *)(scratch + 2) =
            (*(u16 *)((u8 *) vertex_data + 6)) - ((((*(s16 *)((u8 *) vertex_data + 0x12)) - (*(s16 *)((u8 *) vertex_data + 6))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
        *(u16 *)(scratch + 4) =
            (*(u16 *)((u8 *) vertex_data + 0xA)) - ((((*(s16 *)((u8 *) vertex_data + 0x16)) - (*(s16 *)((u8 *) vertex_data + 0xA))) * (*(s16 *)((u8 *) line_data + 6))) >> 8);
        *(s32 *)(scratch + 0xC0) = func_80065420(scratch, line_packet + 8, scratch + 0x90, scratch + 0x94);
        *(u16 *)(scratch + 0) = *(u16 *)((u8 *) vertex_data + 2);
        *(u16 *)(scratch + 2) = *(u16 *)((u8 *) vertex_data + 6);
        *(u16 *)(scratch + 4) = *(u16 *)((u8 *) vertex_data + 0xA);
      }
      avg_depth = ((*(s32 *)(scratch + 0xC0)) + func_80065420(scratch, line_packet + 0x10, scratch + 0x90, scratch + 0x94)) >> 1;
      *(s32 *)(scratch + 0xC0) = avg_depth;
      if (((u32) avg_depth) < 0x1E0U)
      {
        packet = line_packet;
        *(u8 *)(packet + 3) = (color_word = *(s32 *)((u8 *) line_data + 0xC), 4);
        *(s32 *)(packet + 4) = color_word;
        red_blue = *(u8 *)(packet + 4);
        *(volatile u8 *)(packet + 7) = 0x52;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        green = *(u8 *)(packet + 5);
        red_blue >>= 1;
        *(u8 *)(packet + 0xC) = red_blue;
        red_blue = *(u8 *)(packet + 6);
        green >>= 1;
        *(volatile u8 *)(packet + 0xD) = green;
        red_blue >>= 1;
        *(u8 *)(packet + 0xE) = red_blue;
        func_8006658C((*(u8 **)(scratch + 0x20)) + ((*(s32 *)(scratch + 0xC0)) * 4), packet);
        vertex_data = *(u8 **)(scratch + 0x18);
        *(u8 **)(scratch + 0x18) = ((u8 *) vertex_data) + 0xC;
        func_80067F20(vertex_data, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
        func_8006658C((*(u8 **)(scratch + 0x20)) + ((*(s32 *)(scratch + 0xC0)) * 4), vertex_data);
      }
      next_node = *(void **)((u8 *) owner + (-8));
      if (next_node != 0)
      {
        owner = ((u8 *) next_node) + 0x20;
        vertex_data = *(void **)((u8 *) next_node + 8);
        line_data = *(void **)((u8 *) next_node + 0xC);
        continue;
      }
      break;
    }
    *(u8 **)(*render_state + 0x8D0) = *(u8 **)(scratch + 0x18);
    return 0;
  }
}
