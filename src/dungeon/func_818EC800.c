/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
typedef struct { s32 w[10]; } Blk40;
typedef struct { s32 w[4]; } Blk16;
typedef struct { s32 w[2]; } Blk8;


#define M2C_BREAK() 0
#define M2C_SYNC() 0
#define SP8(offset) M2C_FIELD(scratch, u8 *, (offset))
#define SP16(offset) M2C_FIELD(scratch, u16 *, (offset))
#define SP32(offset) M2C_FIELD(scratch, s32 *, (offset))
#define SP5A (*(volatile u16 *)((s8 *)(quad_copies) + 50))
#define SP5D M2C_FIELD(quad_copies, u8 *, 53)

s32 func_800644B8();
M2C_UNK func_80064840();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_800654B0();
M2C_UNK func_80065820();
M2C_UNK func_80067EF4();
extern M2C_UNK D_8006CD10[3];
extern struct S_8003E2D8 D_80083160;

#ifdef __mips__
extern void func_80024298(void) __attribute__((noreturn));
extern void func_80024344(void) __attribute__((noreturn));
extern void func_800243B8(void) __attribute__((noreturn));
extern void func_80024544(void) __attribute__((noreturn));
extern void func_8002454C(void) __attribute__((noreturn));
extern void func_8002459C(void) __attribute__((noreturn));
extern void func_80024990(void) __attribute__((noreturn));
extern void func_800255B4(void);
extern void func_80025150(void);
extern void func_8002516C(void);
extern void func_80025194(void);
extern void func_800252C8(void);
extern void func_800252E4(void);
extern void func_8002530C(void);
extern void func_800256A8(void);
extern void func_8002576C(void);
extern void func_80025A34(void);
extern void func_80025C10(void);
extern void func_80025F64(void);
extern void func_800262F4(void);
extern void func_80026318(void);
extern void func_800263B0(void);
extern void func_8002634C(void);

static void (*const func_818EC800_table_a[])(void)
    __attribute__((section(".text.func_818EC800"))) = {
        func_800255B4,
        0,
        func_80025150,
        func_80025150,
        func_80025150,
        func_8002516C,
        func_80025150,
        func_80025150,
        func_80025150,
        func_80025194,
        func_800252C8,
        func_800252C8,
        func_800252C8,
        func_800252E4,
        func_800252C8,
        func_800252C8,
        func_800252C8,
        func_8002530C,
    };

static const u32 func_818EC800_table_b[]
    __attribute__((section(".text.func_818EC800"))) = {
        0x01000340,
        0x00540060,
        0x00000020,
        0x00200020,
        0x00200000,
        0x0020FFE0,
        0x0000FFE0,
        0xFFE0FFE0,
        0xFFE00000,
        0xFFE00020,
    };

static void (*const func_818EC800_table_c[])(void)
    __attribute__((section(".text.func_818EC800"))) = {
        func_800256A8,
        func_8002576C,
        func_80025A34,
        func_80025C10,
        func_80025F64,
        func_800262F4,
        func_80026318,
        func_800263B0,
        func_8002634C,
    };
#endif

/* Draws a transformed sprite as horizontally displaced scanline quads. */
void func_818EC800(void *screen_pos, void *effect, s32 *ordering_tag, u32 draw_mode)
{
  M2C_UNK quad_copies[20];
  u16 saved_draw_mode;
  s32 callback_arg;
  s32 *copy_end;
  s32 addr_mask;
  M2C_UNK draw_arg;
  u8 *render_state;
  u8 *view_matrix;
  s32 texture_word;
  void *render_context;
  register u8 *context_dep ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  void *final_context;
  s32 base_rotation;
  s32 packet_mask;
  u8 flipped_x;
  u8 origin_x;
  u8 flipped_y;
  u8 origin_y;
  s32 clut_offset;
  s32 tpage_offset;
  s32 mirrored_x;
  s32 quad_x;
  s32 mirrored_y;
  s32 quad_y;
  s32 wave_phase;
  u8 *(*draw_callback)(void *, s32, void *, void *, u8 *);
  s32 *row_tag;
  s32 *start_tag;
  s32 *end_tag;
  u8 *restore_arg;
  u8 *packet;
  s32 draw_callback_arg;
  s32 wave_value;
  s32 edge_value;
  s32 width_minus_one;
  s32 height_minus_one;
  s32 bottom_v;
  s32 view_axis_x;
  s32 view_axis_y;
  s32 view_axis_z;
  s32 row_index;
  u16 screen_y;
  u16 projected_y;
  u16 pivot_x;
  u16 pivot_y;
  u16 draw_flags;
  u16 next_row_y;
  u8 prim_code;
  u8 right_u;
  u8 bottom_tex_v;
  s32 left_x;
  register u8 *scratch ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  void *frame;
  void *row_effect;
  register u8 *frame_data ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  void *sprite;
  void *setup_arg;
  u8 *context_addr;
  u8 *state_base;
  s32 packet_low;
  setup_arg = screen_pos;
  ASM_KEEP_MEMDEP_NV(setup_arg, context_dep, *((void **) (&D_80083160)));   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  sprite = *((void **) (((s8 *) effect) + (-0x14)));
  callback_arg = *((s32 *) (((s8 *) effect) + (-0x18)));
  render_context = *((void **) (&D_80083160));
  frame = *((void **) (((s8 *) sprite) + 8));
  scratch = (u8 *) 0x1F800000;
  ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  *((s32 *) (((s8 *) scratch) + 0xEC)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x8C)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x84)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x7C)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x74)) = 0;
  packet = *((u8 **) (((s8 *) render_context) + 0x8D0));
  *((s32 *) (((s8 *) scratch) + 0x20)) = (s32) ordering_tag;
  *((s32 *) (((s8 *) scratch) + 0xC0)) = 0;
  *((u16 *) (((s8 *) scratch) + 0xB8)) = (u16) ((*((u16 *) (((s8 *) setup_arg) + 0))) - 0xA0);
  *((u16 *) (((s8 *) scratch) + 0xBA)) = (u16) ((*((u16 *) (((s8 *) setup_arg) + 2))) - 0x78);
  ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  saved_draw_mode = (u16) draw_mode;
  draw_mode = ((u32) draw_mode) << 0x10;
  draw_arg = 0;
  if (draw_mode != 0)
  {
    func_80067EF4(packet, draw_arg, draw_arg, draw_mode);
    packet_mask = 0xFFFFFF;
    draw_arg = 0xFF000000;
    *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & packet_mask);
    start_tag = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
    setup_arg = (void *) (((s32) packet) & packet_mask);
    packet += 0xC;
    *start_tag = ((*start_tag) & 0xFF000000) | ((s32) setup_arg);
  }
  copy_end = &quad_copies[8];
  ASM_KEEP_NV(copy_end);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  addr_mask = 0xFFFFFF;
  ASM_KEEP_NV(addr_mask);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  view_matrix = (u8 *) (&D_8006CD10);
  render_state = (u8 *) (&D_80083160);
  *((s32 *) (((s8 *) view_matrix) + 0x1C)) = (s32) (*((s32 *) (((s8 *) render_state) + 0xA0)));
  func_800649A0((s32) setup_arg, draw_arg);
  render_state = (u8 *) (&D_80083160);
  view_axis_x = *((s16 *) (((s8 *) render_state) + 0xC4));
  view_axis_y = *((s16 *) (((s8 *) render_state) + 0xC6));
  view_axis_z = *((s16 *) (((s8 *) render_state) + 0xC8));
  *((s32 *) (((s8 *) scratch) + 0x30)) = view_axis_x;
  *((s32 *) (((s8 *) scratch) + 0x34)) = view_axis_y;
  *((s32 *) (((s8 *) scratch) + 0x38)) = view_axis_z;
  *((u16 *) (((s8 *) scratch) + 0x100)) = (u16) (*((u16 *) (((s8 *) sprite) + 0x16)));
  *((u16 *) (((s8 *) scratch) + 0x104)) = (s16) ((*((u16 *) (((s8 *) sprite) + 0x1A))) - (*((u16 *) (((s8 *) scratch) + 0x34))));
  base_rotation = *((u16 *) (((s8 *) sprite) + 0x18));
  *((u16 *) (((s8 *) scratch) + 0x102)) = (s16) (((((*((u16 *) (((s8 *) scratch) + 0x38))) + 0x100) & 0x1FF) - 0x100) + base_rotation);
  pivot_x = *((u16 *) (((s8 *) sprite) + 0x20));
  *((s32 *) (((s8 *) scratch) + 0xE4)) = pivot_x;
  *((u16 *) (((s8 *) scratch) + 0x108)) = pivot_x;
  pivot_y = *((u16 *) (((s8 *) sprite) + 0x22));
  *((s32 *) (((s8 *) scratch) + 0xE8)) = pivot_y;
  *((u16 *) (((s8 *) scratch) + 0x10A)) = pivot_y;
  func_80065820(0x1F800100, 0x1F8000D0);
  *((s32 *) (((s8 *) scratch) + 0x30)) = (s32) (*((u16 *) (((s8 *) sprite) + 0x1C)));
  *((s32 *) (((s8 *) scratch) + 0x34)) = (s32) (*((u16 *) (((s8 *) sprite) + 0x1E)));
  *((s32 *) (((s8 *) scratch) + 0x38)) = 0x1000;
  func_80064BC0(0x1F8000D0, 0x1F800030);
  func_80064840(view_matrix, 0x1F8000D0, 0x1F800050);
  func_80064D80(0x1F800050);
  func_80064CF0(0x1F800050);
  *((u16 *) (((s8 *) scratch) + 0x24)) = (u16) (*((u16 *) (((s8 *) sprite) + 0x14)));
  frame_data = frame + 8;
  ASM_KEEP(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  if (!((*((u8 *) (((s8 *) frame) + 0))) & 0x20))
  {
    *((s32 *) (((s8 *) scratch) + 0x08)) = (s32) (*((u8 *) (((s8 *) frame_data) + 0)));
    *((s32 *) (((s8 *) scratch) + 0x0C)) = (s32) (*((u8 *) (((s8 *) frame_data) + 1)));
    *((s32 *) (((s8 *) scratch) + 0x10)) = (s32) (*((u8 *) (((s8 *) frame_data) + 2)));
    *((s32 *) (((s8 *) scratch) + 0x14)) = (s32) (*((u8 *) (((s8 *) frame_data) + 3)));
    if (((*((u8 *) (((s8 *) frame) + 0))) ^ (*((u16 *) (((s8 *) scratch) + 0x24)))) & 1)
    {
      flipped_x = *((volatile u8 *) (((s8 *) frame_data) + (-6)));
      mirrored_x = (0 - ((s8) flipped_x)) - (*((u16 *) (((s8 *) scratch) + 0x108)));
      *((u16 *) (((s8 *) scratch) + 0x80)) = mirrored_x;
      *((u16 *) (((s8 *) scratch) + 0x70)) = mirrored_x;
      mirrored_x = mirrored_x - (*((u16 *) (((s8 *) scratch) + 0x10)));
      ASM_TAILSLOT_PIN_TIED(mirrored_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80024344();
    }
    origin_x = *((volatile u8 *) (((s8 *) frame_data) + (-6)));
    quad_x = ((s8) origin_x) - (*((u16 *) (((s8 *) scratch) + 0x108)));
    *((u16 *) (((s8 *) scratch) + 0x80)) = quad_x;
    *((u16 *) (((s8 *) scratch) + 0x70)) = quad_x;
    quad_x = quad_x + (*((u16 *) (((s8 *) scratch) + 0x10)));
    *((u16 *) (((s8 *) scratch) + 0x88)) = quad_x;
    *((u16 *) (((s8 *) scratch) + 0x78)) = quad_x;
    if (((*((u8 *) (((s8 *) frame) + 0))) ^ (*((u16 *) (((s8 *) scratch) + 0x24)))) & 2)
    {
      flipped_y = *((volatile u8 *) (((s8 *) frame_data) + (-5)));
      mirrored_y = (0 - ((s8) flipped_y)) - (*((u16 *) (((s8 *) scratch) + 0x10A)));
      *((u16 *) (((s8 *) scratch) + 0x7A)) = mirrored_y;
      *((u16 *) (((s8 *) scratch) + 0x72)) = mirrored_y;
      mirrored_y = mirrored_y - (*((u16 *) (((s8 *) scratch) + 0x14)));
      ASM_TAILSLOT_PIN_TIED(mirrored_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_800243B8();
    }
    origin_y = *((volatile u8 *) (((s8 *) frame_data) + (-5)));
    quad_y = ((s8) origin_y) - (*((u16 *) (((s8 *) scratch) + 0x10A)));
    *((u16 *) (((s8 *) scratch) + 0x7A)) = quad_y;
    *((u16 *) (((s8 *) scratch) + 0x72)) = quad_y;
    quad_y = quad_y + (*((u16 *) (((s8 *) scratch) + 0x14)));
    *((u16 *) (((s8 *) scratch) + 0x8A)) = quad_y;
    *((u16 *) (((s8 *) scratch) + 0x82)) = quad_y;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
    *((s16 *) (((s8 *) packet) + 8)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF0))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) packet) + 0xA)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF2))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) packet) + 0x10)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF4))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) packet) + 0x12)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF6))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) packet) + 0x18)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF8))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xFA))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) packet) + 0x20)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xFC))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    projected_y = *((u16 *) (((s8 *) scratch) + 0xFE));
    screen_y = *((u16 *) (((s8 *) scratch) + 0xBA));
    *((s8 *) (((s8 *) packet) + 3)) = 9;
    *((s16 *) (((s8 *) packet) + 0x22)) = (s16) (projected_y + screen_y);
    width_minus_one = (*((s32 *) (((s8 *) scratch) + 0x10))) - 1;
    edge_value = width_minus_one + (*((s32 *) (((s8 *) scratch) + 0x08)));
    *((s32 *) (((s8 *) scratch) + 0x10)) = edge_value;
    if (edge_value & 0x100)
    {
      *((s32 *) (((s8 *) scratch) + 0x10)) = edge_value - 1;
    }
    height_minus_one = (*((s32 *) (((s8 *) scratch) + 0x14))) - 1;
    bottom_v = height_minus_one + (*((s32 *) (((s8 *) scratch) + 0x0C)));
    *((s32 *) (((s8 *) scratch) + 0x14)) = bottom_v;
    if (bottom_v & 0x100)
    {
      *((s32 *) (((s8 *) scratch) + 0x14)) = bottom_v - 1;
    }
    *((s32 *) (((s8 *) scratch) + 0x14)) <<= 8;
    *((s32 *) (((s8 *) scratch) + 0x0C)) <<= 8;
    clut_offset = *((u16 *) (((s8 *) sprite) + 0x12));
    if (clut_offset != 0)
    {
      if ((*((u16 *) (((s8 *) scratch) + 0x24))) & 0x100)
      {
        *((u16 *) (((s8 *) packet) + 0xE)) = (u16) clut_offset;
        func_8002454C();
      }
      texture_word = clut_offset + (*((u16 *) (((s8 *) frame_data) + (-2))));
      ASM_TAILSLOT_PIN_TIED(texture_word);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      func_80024544();
    }
    *((u16 *) (((s8 *) packet) + 0xE)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-2))));
    *((s16 *) (((s8 *) packet) + 0xC)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x0C)))) + ((u16) (*((u16 *) (((s8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) packet) + 0x14)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x0C)))) + ((u16) (*((u16 *) (((s8 *) scratch) + 0x10)))));
    tpage_offset = *((u16 *) (((s8 *) sprite) + 0x10));
    if (tpage_offset != 0)
    {
      texture_word = tpage_offset + ((*((u16 *) (((s8 *) frame_data) + (-4)))) & 0xFF9F);
      ASM_TAILSLOT_PIN_TIED(texture_word);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      func_8002459C();
    }
    *((u16 *) (((s8 *) packet) + 0x16)) = (u16) (*((u16 *) (((s8 *) frame_data) + (-4))));
    *((s16 *) (((s8 *) packet) + 0x1C)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x14)))) | ((u16) (*((u16 *) (((s8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) packet) + 0x24)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x14)))) | ((u16) (*((u16 *) (((s8 *) scratch) + 0x10)))));
    left_x = *((s16 *) (((s8 *) packet) + 8));
    if ((*((s16 *) (((s8 *) packet) + 0x20))) < left_x)
    {
      right_u = *((u8 *) (((s8 *) packet) + 0x24));
      *((u8 *) (((s8 *) packet) + 0x24)) = (u8) (right_u + 0xFF);
      *((u8 *) (((s8 *) packet) + 0x14)) = right_u;
    }
    edge_value = *((s16 *) (((s8 *) packet) + 0xA));
    if ((*((s16 *) (((s8 *) packet) + 0x22))) < edge_value)
    {
      bottom_tex_v = *((u8 *) (((s8 *) packet) + 0x25));
      *((u8 *) (((s8 *) packet) + 0x25)) = (u8) (bottom_tex_v + 0xFF);
      *((u8 *) (((s8 *) packet) + 0x1D)) = bottom_tex_v;
    }
    prim_code = *((u8 *) (((s8 *) frame_data) + (-7)));
    *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code;
    draw_flags = *((u16 *) (((s8 *) scratch) + 0x24));
    ASM_KEEP_NV(draw_flags);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (draw_flags & 8)
    {
      if (draw_flags & 4)
      {
        *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code | 2;
      }
      else
      {
        *((u8 *) (((s8 *) sprite) + 0xF)) = prim_code & 0xFD;
      }
    }
    *((s32 *) (((s8 *) packet) + 4)) = (s32) (*((s32 *) (((s8 *) sprite) + 0xC)));
    *((Blk40 *) quad_copies) = *((Blk40 *) packet);
    {
      Blk16 *copy_dst = (Blk16 *) (&quad_copies[10]);
      Blk16 *copy_src = (Blk16 *) quad_copies;
      do
      {
        *(copy_dst++) = *(copy_src++);
      }
      while (((s32 *) copy_src) != copy_end);
      *((Blk8 *) copy_dst) = *((Blk8 *) copy_src);
    }
    row_index = 0;
    ASM_KEEP(row_index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    wave_phase = *((s16 *) (((s8 *) effect) + 0x8C));
    do
    {
      *((s8 *) (((s8 *) packet) + 0x3)) = 9;
      {
        Blk16 *packet_dst = (Blk16 *) packet;
        Blk16 *packet_src = (Blk16 *) quad_copies;
        do
        {
          *(packet_dst++) = *(packet_src++);
        }
        while (((s32 *) packet_src) != copy_end);
        *((Blk8 *) packet_dst) = *((Blk8 *) packet_src);
      }
      wave_value = func_800644B8(wave_phase);
      row_effect = effect + row_index;
      *((u16 *) (((s8 *) packet) + 0x8)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x8))) + (((s32) (wave_value * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) packet) + 0x10)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x10))) + (((s32) (func_800644B8(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
      wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
      if (wave_phase >= 0x1001)
      {
        wave_phase -= 0x1000;
      }
      *((u16 *) (((s8 *) packet) + 0x18)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x18))) + (((s32) (func_800644B8(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) packet) + 0x20)) = (u16) ((*((u16 *) (((s8 *) packet) + 0x20))) + (((s32) (func_800644B8(wave_phase) * (*((u8 *) (((s8 *) row_effect) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) packet) + 0xA)) = *((volatile u16 *) (((s8 *) quad_copies) + 50));
      *((u16 *) (((s8 *) packet) + 0x12)) = *((volatile u16 *) (((s8 *) quad_copies) + 50));
      *((s16 *) (((s8 *) packet) + 0x1A)) = (s16) ((*((volatile u16 *) (((s8 *) quad_copies) + 50))) + 1);
      *((s16 *) (((s8 *) packet) + 0x22)) = (s16) ((*((volatile u16 *) (((s8 *) quad_copies) + 50))) + 1);
      *((u8 *) (((s8 *) packet) + 0xD)) = *((u8 *) (((s8 *) quad_copies) + 53));
      *((u8 *) (((s8 *) packet) + 0x15)) = *((u8 *) (((s8 *) quad_copies) + 53));
      row_index += 1;
      *((s8 *) (((s8 *) packet) + 0x1D)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
      *((s8 *) (((s8 *) packet) + 0x25)) = (s8) ((*((u8 *) (((s8 *) quad_copies) + 53))) + 1);
      {
        s32 packet_size = (*((s32 *) packet)) & 0xFF000000;
        s32 packet_link = packet_size | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & addr_mask);
        ASM_KEEP_NV(packet_link);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        *((s32 *) packet) = packet_link;
      }
      row_tag = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
      {
        s32 row_link = ((*row_tag) & 0xFF000000) | (((s32) packet) & addr_mask);
        ASM_KEEP_NV(row_link);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        *row_tag = row_link;
      }
      *((Blk40 *) (&quad_copies[10])) = *((Blk40 *) packet);
      next_row_y = (*((volatile u16 *) (((s8 *) quad_copies) + 50))) + 1;
      *((volatile u16 *) (((s8 *) quad_copies) + 50)) = next_row_y;
      *((u8 *) (((s8 *) quad_copies) + 53)) += 1;
      wave_phase = wave_phase + (*((s16 *) (((s8 *) effect) + 0x8E)));
      packet += 0x28;
      if (wave_phase >= 0x1001)
      {
        wave_phase -= 0x1000;
      }
    }
    while (((s16) next_row_y) < (*((s16 *) (((s8 *) quad_copies) + 26))));
    ASM_USE2(sprite, frame_data);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_USE_G_NV(callback_arg);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_USE_G_NV(saved_draw_mode);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_USE(frame);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    func_80024990();
    return;
  }
  draw_callback = (u8 *(*)(void *, s32, void *, void *, u8 *)) (*((s32 *) (((s8 *) frame_data) + 0)));
  if (draw_callback != 0)
  {
    draw_callback_arg = callback_arg;
    packet = draw_callback(effect, draw_callback_arg, sprite, frame, packet);
  }
  if (((s8) (*((u8 *) (((s8 *) frame) + 0)))) >= 0)
  {
    frame_data = frame_data + 0xC;
    ASM_KEEP(frame_data);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    frame = ((u8 *) frame) + 0xC;
    ASM_TAILSLOT_PIN_TIED(frame);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    func_80024298();
    return;
  }
  restore_arg = packet;
  if ((saved_draw_mode << 0x10) != 0)
  {
    func_80067EF4(restore_arg, 0, 1);
    *((s32 *) packet) = ((*((s32 *) packet)) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & 0xFFFFFF);
    end_tag = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
    restore_arg = (u8 *) (((s32) packet) & 0xFFFFFF);
    packet += 0xC;
    *end_tag = ((*end_tag) & 0xFF000000) | ((s32) restore_arg);
  }
  ASM_CLOBBER("$17");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  ASM_CLOBBER("$18");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  ASM_CLOBBER("$22");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  func_80064A40((s32) restore_arg);
  state_base = (u8 *) (&D_80083160);
  packet_low = (s32) ((u16) ((s32) packet));
  context_addr = state_base + (packet_low & 0x10000);
  final_context = *((void **) (((s8 *) context_addr) + 0));
  *((s32 **) (((s8 *) final_context) + 0x8D0)) = packet;
}
