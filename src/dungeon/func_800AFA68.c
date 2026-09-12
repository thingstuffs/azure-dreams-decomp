#ifdef PERMUTER_PARSER
#define GEOM_SIDE_EFFECTS() (*(GeomSideEffects *)0)
#else
#define GEOM_SIDE_EFFECTS() (GeomSideEffects){}
#endif
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define SCR_S8(off)  (*(s8  *)(scratch + (off)))
#define SCR_U8(off)  (*(u8  *)(scratch + (off)))
#define SCR_S16(off) (*(s16 *)(scratch + (off)))
#define SCR_U16(off) (*(u16 *)(scratch + (off)))
#define SCR_S32(off) (*(s32 *)(scratch + (off)))
#define SCR_PTR(off) (*(u8 **)(scratch + (off)))

void func_800478B8();                      /* extern */
M2C_UNK func_80064840(); /* extern */
M2C_UNK func_80064AE0(); /* extern */
M2C_UNK func_80064BC0();              /* extern */
M2C_UNK func_80064CF0();                   /* extern */
M2C_UNK func_80064D80();                   /* extern */
u32 func_80065420(); /* extern */
typedef struct GeomTailArgs {
    void *arg9;
    void *arg10;
} GeomTailArgs;
typedef struct GeomSideEffects {
} GeomSideEffects;
u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, GeomTailArgs, GeomSideEffects);
M2C_UNK func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, GeomTailArgs, GeomSideEffects);

M2C_UNK func_80065820();        /* extern */
M2C_UNK func_8006658C();         /* extern */
M2C_UNK func_800666F4();                 /* extern */
u16 func_800BCB04();                   /* extern */
extern M2C_UNK D_8006CD30[8];
extern struct S_8003E2D8 D_80083160;
extern s32 D_800E296C[3];
extern u8 D_800E3648[128];
typedef struct DebugEntry {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} DebugEntry;
extern DebugEntry D_800E3648_entries[32] __asm__("D_800E3648");
extern u8 D_800E39C8[1024];

/* Render active dungeon sprite parts and their ground shadows into the ordering table. */
s32 func_800B51C8(void *unused_0, void *unused_1, void * volatile render_params)
{
  u8 saved_matrix[0x20];
  register u8 *transform_dst ASM_REG("$4") = saved_matrix;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 entry_index = 0;
  register u8 *rotation_matrix ASM_REG("$22") = (u8 *) 0x1F8000D0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register u8 *world_matrix_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  u8 *view_matrix = (u8 *) 0x1F800050;
  u8 *depth_cue = (u8 *) 0x1F800090;
  u8 *transform_flags = (u8 *) 0x1F800094;
  u8 *shadow_rotation;
  u8 *sprite_rotation;
  register u8 *sprite_matrix_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  u32 depth_dependency;
  register u8 *camera_state ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *depth_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *shadow_depth_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *scratch ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  volatile u16 camera_pitch;
  volatile u16 camera_yaw;
  volatile u16 camera_roll;
  register u16 initial_pitch ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 initial_yaw;
  s32 shadow_scale[3];
  u8 *entry_table;
  s32 world_x;
  s32 depth_or_height;
  u16 world_pos_x;
  u16 world_pos_y;
  register void *params ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  u16 sprite_yaw;
  u16 view_yaw;
  register u16 shadow_yaw ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  u8 world_x_byte;
  u8 world_y_byte;
  u8 sprite_x_byte;
  u8 sprite_y_byte;
  s32 world_corner_x;
  s32 world_corner_y;
  s32 sprite_corner_x;
  register s32 sprite_corner_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 texture_v;
  s32 scale_component;
  s32 texture_width;
  s32 texture_u;
  s32 texture_height;
  s32 height_scale;
  s32 texture_right;
  s32 texture_bottom;
  s32 texture_extent;
  s32 world_third_visible;
  s32 world_first_visible;
  s32 sprite_third_visible;
  s32 sprite_pair_visible;
  s32 world_second_visible;
  s32 world_fourth_visible;
  s32 world_triple_visible;
  s32 world_pair_visible;
  s32 sprite_triple_visible;
  s32 sprite_second_visible;
  s32 sprite_fourth_visible;
  u16 corner_y_or_height;
  u16 pitch_bits;
  s32 bottom_right_uv;
  register s32 top_right_uv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  u8 *shadow_matrix_arg;
  u16 ground_height;
  u16 projected_y;
  s32 ground_height_shifted;
  u16 world_z;
  u16 world_y;
  u16 entry_height;
  u32 shadow_depth;
  u32 quad_depth;
  u32 sprite_depth;
  u32 sort_depth;
  u8 texture_u_byte;
  u8 texture_v_byte;
  u8 texture_width_byte;
  u8 texture_height_byte;
  void *primitive_buffer;
  void *sprite_entry;
  void *quad;
  void *shadow_quad;
  void *world_part;
  void *sprite_part;
  void *part_header;
  void *entry_flags;
  void *render_state;
  ASM_KEEP_MEM_NV(transform_flags, *((void **) (((s8 *) (&D_80083160)) + 0)));   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  scratch = (u8 *) 0x1F800000;
  render_state = *((void **) (((s8 *) (&D_80083160)) + 0));
  camera_state = ((u8 *) (&D_80083178)) - 0x18;
  ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
  initial_pitch = *((u16 *) (((s8 *) camera_state) + 0xC4));
  initial_yaw = *((u16 *) (((s8 *) camera_state) + 0xC6));
  world_x = *((u16 *) (((s8 *) camera_state) + 0xC8));
  primitive_buffer = *((void **) (((s8 *) render_state) + 0x8D0));
  *((u8 **) (scratch + 0x020)) = render_state + 0xB0;
  *((u16 *) (scratch + 0x08c)) = 0;
  *((u16 *) (scratch + 0x084)) = 0;
  *((u16 *) (scratch + 0x07c)) = 0;
  *((u16 *) (scratch + 0x074)) = 0;
  camera_pitch = initial_pitch;
  camera_yaw = initial_yaw;
  camera_roll = world_x;
  *((u8 **) (scratch + 0x018)) = primitive_buffer;
  func_80064AE0(transform_dst, initial_yaw, world_x, primitive_buffer);
  next_entry:
  entry_table = (u8 *) (&D_800E3648);

  entry_flags = (void *) ((entry_index * 4) + ((s32) entry_table));
  if ((((!((*((u8 *) (((s8 *) entry_flags) + 3))) & 0x80)) || (D_800E296C[0] & 8)) && ((*((u8 *) (((s8 *) entry_flags) + 1))) != 0)) && ((*((u8 *) (((s8 *) entry_flags) + 0))) != 0))
  {
    u8 *entry_table;
    entry_table = &D_800E39C8;
    sprite_entry = (entry_index * 0x18) + entry_table;
    if ((*((u16 *) (((s8 *) sprite_entry) + 0x14))) & 0x40)
    {
      func_800478B8(sprite_entry);
    }
    *((u16 *) (scratch + 0x000)) = (s16) (((*((u8 *) (((s8 *) sprite_entry) + 6))) << 6) + 0x20);
    *((u16 *) (scratch + 0x002)) = (u16) (((*((u8 *) (((s8 *) sprite_entry) + 7))) << 6) + 0x20);
    entry_height = *((u16 *) (((s8 *) sprite_entry) + 0x12));
    *((u16 *) (scratch + 0x004)) = entry_height;
    part_header = *((void **) (((s8 *) sprite_entry) + 8));
    *((u16 *) (((s8 *) sprite_entry) + 0x10)) = entry_height;
    if (part_header != 0)
    {
      if ((*((u16 *) (((s8 *) sprite_entry) + 0x14))) & 0x100)
      {
        transform_dst = scratch + 0x100;
        world_matrix_arg = rotation_matrix;
        world_x = *((s16 *) (scratch + 0x000));
        world_y = *((u16 *) (scratch + 0x002));
        *((s32 *) (scratch + 0x030)) = (s32) 0x2000;
        *((s32 *) (scratch + 0x034)) = (s32) 0x2000;
        *((s32 *) (scratch + 0x038)) = (s32) 0x2000;
        world_z = *((u16 *) (scratch + 0x004));
        world_part = part_header + 4;
        *((u16 *) (scratch + 0x100)) = 0;
        *((u16 *) (scratch + 0x102)) = 0U;
        *((u16 *) (scratch + 0x104)) = 0;
        *((s32 *) (scratch + 0x0e4)) = (s32) world_x;
        *((s32 *) (scratch + 0x0e8)) = (s32) ((s16) world_y);
        *((s32 *) (scratch + 0x0ec)) = (s32) ((s16) world_z);
        func_80065820(transform_dst, world_matrix_arg, world_x);
        func_80064840(&saved_matrix, rotation_matrix, view_matrix);
        func_80064BC0(view_matrix, scratch + 0x30);
        func_80064D80((M2C_UNK *) view_matrix);
        func_80064CF0((M2C_UNK *) view_matrix);
        next_world_part:
        if (!((*((u8 *) (((s8 *) part_header) + 0))) & 0x20))
        {
          texture_u_byte = *((u8 *) (((s8 *) world_part) + 4));
          *((s32 *) (scratch + 0x008)) = (s32) texture_u_byte;
          texture_width_byte = *((u8 *) (((s8 *) world_part) + 6));
          *((s32 *) (scratch + 0x010)) = (s32) texture_width_byte;
          if ((texture_u_byte + texture_width_byte) >= 0x100)
          {
            *((s32 *) (scratch + 0x010)) = texture_width_byte - 1;
          }
          texture_v_byte = *((u8 *) (((s8 *) world_part) + 5));
          *((s32 *) (scratch + 0x00c)) = (s32) texture_v_byte;
          texture_height_byte = *((u8 *) (((s8 *) world_part) + 7));
          *((s32 *) (scratch + 0x014)) = (s32) texture_height_byte;
          if ((texture_v_byte + texture_height_byte) >= 0x100)
          {
            *((s32 *) (scratch + 0x014)) = texture_height_byte - 1;
          }
          {
            register void *world_top_left ASM_REG("$4") = scratch + 0x70;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register void *world_top_right ASM_REG("$5") = scratch + 0x78;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register void *world_bottom_left ASM_REG("$6") = scratch + 0x80;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register void *world_bottom_right ASM_REG("$7") = scratch + 0x88;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            world_x_byte = *((u8 *) (((s8 *) world_part) + (-2)));
            ASM_USE_NV(world_x_byte);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            world_corner_x = (s8) world_x_byte;
            quad = *((u8 **) (scratch + 0x018));
            *((u16 *) (scratch + 0x080)) = world_corner_x;
            *((u16 *) (scratch + 0x070)) = world_corner_x;
            world_corner_x += (u16) (*((u16 *) (scratch + 0x010)));
            *((u16 *) (scratch + 0x088)) = world_corner_x;
            *((u16 *) (scratch + 0x078)) = world_corner_x;
            world_y_byte = *((u8 *) (((s8 *) world_part) + (-1)));
            *((u8 **) (scratch + 0x018)) = quad + 0x28;
            quad_depth = func_80065590(world_top_left, world_top_right, world_bottom_left, world_bottom_right, quad + 8, quad + 0x10, quad + 0x18, quad + 0x20, (GeomTailArgs){depth_cue, transform_flags}, (world_corner_y = (s8) world_y_byte, *((u16 *) (scratch + 0x07a)) = world_corner_y, *((u16 *) (scratch + 0x072)) = world_corner_y, world_corner_y += (u16) (*((u16 *) (scratch + 0x014))), *((u16 *) (scratch + 0x08a)) = world_corner_y, *((u16 *) (scratch + 0x082)) = world_corner_y, *((GeomSideEffects *) 0)));
            *((s32 *) (scratch + 0x0c0)) = quad_depth;
          }
          if (quad_depth < 0x1E0U)
          {
            world_first_visible = 0;
            if (((u32) (((*((u16 *) (((s8 *) quad) + 8))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0xA))) + 0x20);
              world_first_visible = visibility_y < 0x121U;
            }
            world_second_visible = 0;
            if (((u32) (((*((u16 *) (((s8 *) quad) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x12))) + 0x20);
              world_second_visible = visibility_y < 0x121U;
            }
            world_third_visible = 0;
            world_pair_visible = world_first_visible | world_second_visible;
            if (((u32) (((*((u16 *) (((s8 *) quad) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x1A))) + 0x20);
              world_third_visible = visibility_y < 0x121U;
            }
            world_fourth_visible = 0;
            world_triple_visible = world_pair_visible | world_third_visible;
            if (((u32) (((*((u16 *) (((s8 *) quad) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x22))) + 0x20);
              world_fourth_visible = visibility_y < 0x121U;
            }
            if ((world_triple_visible | world_fourth_visible) != 0)
            {
              texture_width = *((s32 *) (scratch + 0x010));
              texture_u = *((s32 *) (scratch + 0x008));
              texture_height = *((s32 *) (scratch + 0x014));
              texture_v = *((s32 *) (scratch + 0x00c));
              *((s32 *) (scratch + 0x010)) = texture_width + texture_u;
              *((s32 *) (scratch + 0x014)) = texture_height + texture_v;
              *((s32 *) (scratch + 0x00c)) <<= 8;
              *((s32 *) (scratch + 0x014)) <<= 8;
              *((u16 *) (((s8 *) quad) + 0xE)) = (u16) (*((u16 *) (((s8 *) world_part) + 2)));
              *((s16 *) (((s8 *) quad) + 0xC)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) quad) + 0x14)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              *((u16 *) (((s8 *) quad) + 0x16)) = (u16) (*((u16 *) (((s8 *) world_part) + 0)));
              *((s16 *) (((s8 *) quad) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) quad) + 0x24)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              params = render_params;
              *((s32 *) (((s8 *) quad) + 4)) = (s32) (*((s32 *) (((s8 *) params) + 0xC)));
              func_800666F4(quad, texture_v);
              *((u8 *) (((s8 *) quad) + 7)) = (u8) ((*((u8 *) (((s8 *) quad) + 7))) | 2);
              func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), quad);
            }
          }
        }

        world_part = (void *) (((u8 *) world_part) + 12);
        if (((s8) (*((u8 *) (((s8 *) part_header) + 0)))) >= 0)
        {
          part_header = (void *) (((u8 *) part_header) + 12);
          goto next_world_part;
        }
        goto restore_matrix;
      }
      *((s32 *) (scratch + 0x0e4)) = 0;
      *((s32 *) (scratch + 0x0e8)) = 0;
      *((s32 *) (scratch + 0x0ec)) = 0;
      sprite_depth = func_80065420(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
      *((s32 *) (scratch + 0x0c0)) = sprite_depth;
      ASM_KEEP_MEMDEP_NV(sprite_depth, depth_dependency, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
      sort_depth = sprite_depth;
      ASM_KEEP_MEM_NV(sort_depth, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      depth_or_height = sprite_depth * 4;
      depth_base = (u8 *) 0x80070000;
      ASM_KEEP_NV(depth_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      depth_base -= 13008;
      ASM_USE_NV(depth_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      *((s32 *) (((s8 *) depth_base) + 0x1C)) = depth_or_height;
      sort_depth -= 4;
      *((s32 *) (scratch + 0x0c0)) = sort_depth;
      if (sort_depth < 0x1E0U)
      {
        register u8 *sprite_camera ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        sprite_matrix_arg = rotation_matrix;
        sprite_rotation = scratch + 0x100;
        ASM_USE_NV(sprite_rotation);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        *((u16 *) (scratch + 0x0b8)) = (u16) ((*((u16 *) (scratch + 0x0b8))) - 0xA0);
        pitch_bits = camera_pitch;
        *((u16 *) (scratch + 0x0ba)) = (u16) ((*((u16 *) (scratch + 0x0ba))) - 0x78);
        params = render_params;
        *((u16 *) (scratch + 0x100)) = (s16) ((*((u16 *) (((s8 *) params) + 0x16))) + (((s32) (pitch_bits << 0x10)) >> 0x11));
        sprite_yaw = *((u16 *) (((s8 *) params) + 0x1A));
        sprite_camera = (u8 *) 0x80080000;
        ASM_KEEP_NV(sprite_camera);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        sprite_camera += 12640;
        ASM_USE_NV(sprite_camera);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        view_yaw = camera_yaw;
        *((u16 *) (scratch + 0x104)) = (s16) ((*((u16 *) (((s8 *) sprite_camera) + 0xB8))) + (sprite_yaw - view_yaw));
        sprite_part = part_header + 4;
        params = render_params;
        *((u16 *) (scratch + 0x102)) = (u16) (*((u16 *) (((s8 *) params) + 0x18)));
        func_80065820(sprite_rotation, sprite_matrix_arg, view_yaw);
        func_80064840(&D_8006CD30, rotation_matrix, view_matrix);
        func_80064D80((M2C_UNK *) view_matrix);
        func_80064CF0((M2C_UNK *) view_matrix);
        next_sprite_part:
        if (!((*((u8 *) (((s8 *) part_header) + 0))) & 0x20))
        {
          *((s32 *) (scratch + 0x008)) = (s32) (*((u8 *) (((s8 *) sprite_part) + 4)));
          *((s32 *) (scratch + 0x00c)) = (s32) (*((u8 *) (((s8 *) sprite_part) + 5)));
          *((s32 *) (scratch + 0x010)) = (s32) (*((u8 *) (((s8 *) sprite_part) + 6)));
          *((s32 *) (scratch + 0x014)) = (s32) (*((u8 *) (((s8 *) sprite_part) + 7)));
          sprite_x_byte = *((volatile u8 *) (((s8 *) sprite_part) + (-2)));
          sprite_corner_x = (s8) sprite_x_byte;
          *((u16 *) (scratch + 0x080)) = sprite_corner_x;
          *((u16 *) (scratch + 0x070)) = sprite_corner_x;
          sprite_corner_x += (u16) (*((u16 *) (scratch + 0x010)));
          *((u16 *) (scratch + 0x088)) = sprite_corner_x;
          *((u16 *) (scratch + 0x078)) = sprite_corner_x;
          sprite_y_byte = *((u8 *) (((s8 *) sprite_part) + (-1)));
          func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, (GeomTailArgs){depth_cue, transform_flags}, (sprite_corner_y = (s8) sprite_y_byte, *((u16 *) (scratch + 0x07a)) = sprite_corner_y, *((u16 *) (scratch + 0x072)) = sprite_corner_y, sprite_corner_y += (u16) (*((u16 *) (scratch + 0x014))), *((u16 *) (scratch + 0x08a)) = sprite_corner_y, *((u16 *) (scratch + 0x082)) = sprite_corner_y, *((GeomSideEffects *) 0)));
          quad = *((u8 **) (scratch + 0x018));
          *((u8 **) (scratch + 0x018)) = quad + 0x28;
          *((u16 *) (((s8 *) quad) + 8)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f0)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) quad) + 0xA)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f2)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) quad) + 0x10)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f4)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) quad) + 0x12)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f6)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) quad) + 0x18)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f8)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) quad) + 0x1A)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fa)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          sprite_pair_visible = 0;
          *((u16 *) (((s8 *) quad) + 0x20)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fc)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          corner_y_or_height = (u16) (((s32) (*((u16 *) (scratch + 0x0fe)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) quad) + 0x22)) = corner_y_or_height;
          if (((u32) (((*((u16 *) (((s8 *) quad) + 8))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0xA))) + 0x20);
            sprite_pair_visible = visibility_y < 0x121U;
          }
          sprite_second_visible = 0;
          if (((u32) (((*((u16 *) (((s8 *) quad) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x12))) + 0x20);
            sprite_second_visible = visibility_y < 0x121U;
          }
          sprite_third_visible = 0;
          sprite_pair_visible |= sprite_second_visible;
          if (((u32) (((*((u16 *) (((s8 *) quad) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x1A))) + 0x20);
            sprite_third_visible = visibility_y < 0x121U;
          }
          sprite_fourth_visible = 0;
          sprite_triple_visible = sprite_pair_visible | sprite_third_visible;
          if (((u32) (((*((u16 *) (((s8 *) quad) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) (corner_y_or_height + 0x20);
            sprite_fourth_visible = visibility_y < 0x121U;
          }
          if ((sprite_triple_visible | sprite_fourth_visible) != 0)
          {
            *((s8 *) (((s8 *) quad) + 3)) = 9;
            texture_extent = ((s32) (*((s32 *) (scratch + 0x010)))) - 1;
            texture_right = texture_extent + ((s32) (*((s32 *) (scratch + 0x008))));
            *((s32 *) (scratch + 0x010)) = texture_right;
            if (texture_right & 0x100)
            {
              *((s32 *) (scratch + 0x010)) = texture_right - 1;
            }
            texture_extent = ((s32) (*((s32 *) (scratch + 0x014)))) - 1;
            texture_bottom = texture_extent + ((s32) (*((s32 *) (scratch + 0x00c))));
            *((s32 *) (scratch + 0x014)) = texture_bottom;
            if (texture_bottom & 0x100)
            {
              *((s32 *) (scratch + 0x014)) = texture_bottom - 1;
            }
            *((s32 *) (scratch + 0x00c)) <<= 8;
            *((s32 *) (scratch + 0x014)) <<= 8;
            *((s16 *) (((s8 *) quad) + 0xC)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
            *((u16 *) (((s8 *) quad) + 0xE)) = (u16) (*((u16 *) (((s8 *) sprite_part) + 2)));
            *((s16 *) (((s8 *) quad) + 0x14)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
            *((u16 *) (((s8 *) quad) + 0x16)) = (u16) (*((u16 *) (((s8 *) sprite_part) + 0)));
            *((s16 *) (((s8 *) quad) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
            bottom_right_uv = ((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010))));
            *((s16 *) (((s8 *) quad) + 0x24)) = (s16) bottom_right_uv;
            if (((s16) (*((u16 *) (((s8 *) quad) + 8)))) > ((s16) (*((u16 *) (((s8 *) quad) + 0x20)))))
            {
              *((u8 *) (((s8 *) quad) + 0x14)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x14))) - 1);
              *((u8 *) (((s8 *) quad) + 0x24)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x24))) - 1);
            }
            if (((s16) (*((u16 *) (((s8 *) quad) + 0xA)))) > ((s16) (*((u16 *) (((s8 *) quad) + 0x22)))))
            {
              *((u8 *) (((s8 *) quad) + 0x1D)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x1D))) - 1);
              *((u8 *) (((s8 *) quad) + 0x25)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x25))) - 1);
            }
            params = render_params;
            *((s32 *) (((s8 *) quad) + 4)) = (s32) (*((s32 *) (((s8 *) params) + 0xC)));
            *((u8 *) (((s8 *) quad) + 7)) = 0x2CU;
            if ((D_800E296C[0] & 8) && (D_800E3648_entries[entry_index].b3 & 0x80))
            {
              *((u8 *) (((s8 *) quad) + 7)) = 0x2EU;
            }
            func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), quad, sprite_pair_visible);
            if (!((*((u8 *) (((s8 *) quad) + 7))) & 2))
            {
              register u8 *shadow_camera ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
              func_80064D80(&saved_matrix);
              func_80064CF0(&saved_matrix);
              world_pos_x = *((u16 *) (scratch + 0x000));
              world_pos_y = *((u16 *) (scratch + 0x002));
              corner_y_or_height = *((u16 *) (scratch + 0x004));
              ASM_USE2_NV(world_pos_x, corner_y_or_height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
              depth_or_height = (s16) corner_y_or_height;
              depth_or_height -= 4;
              shadow_scale[2] = depth_or_height;
              *((u16 *) (scratch + 0x004)) = func_800BCB04(world_pos_x, world_pos_y, (s16) depth_or_height);
              shadow_depth = func_80065420(scratch, scratch + 0xB8, depth_cue, transform_flags);
              *((s32 *) (scratch + 0x0c0)) = shadow_depth;
              ASM_KEEP_MEMDEP_NV(shadow_depth, depth_dependency, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
              depth_or_height = shadow_depth * 4;
              shadow_depth_base = (u8 *) 0x80070000;
              ASM_KEEP_NV(shadow_depth_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
              shadow_depth_base -= 13008;
              ASM_USE_NV(shadow_depth_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
              *((s32 *) (((s8 *) shadow_depth_base) + 0x1C)) = depth_or_height;
              *((s32 *) (scratch + 0x0c0)) -= 3;
              projected_y = *((u16 *) (scratch + 0x0ba));
              *((u16 *) (scratch + 0x0b8)) = (u16) ((*((u16 *) (scratch + 0x0b8))) - 0xA0);
              ground_height = *((u16 *) (scratch + 0x004));
              ground_height_shifted = ((s32) ground_height) << 0x10;
              *((u16 *) (scratch + 0x0ba)) = (u16) (projected_y - 0x78);
              height_scale = ((shadow_scale[2] - (ground_height_shifted >> 0x10)) << 5) + 0x1000;
              shadow_scale[2] = height_scale;
              if (height_scale < 0)
              {
                shadow_scale[2] = 0;
              }
              shadow_rotation = scratch + 0x100;
              ASM_USE_NV(shadow_rotation);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
              shadow_matrix_arg = rotation_matrix;
              ASM_KEEP_NV(shadow_matrix_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
              shadow_camera = (u8 *) (&D_80083160);
              scale_component = shadow_scale[2];
              *((u16 *) (scratch + 0x102)) = 0U;
              shadow_yaw = camera_yaw;
              shadow_scale[0] = scale_component;
              scale_component += (s32) (((u32) scale_component) >> 0x1F);
              scale_component >>= 1;
              shadow_scale[1] = scale_component;
              {
                u16 shadow_pitch = (u16) (0 - camera_pitch);
                u16 shadow_roll = (u16) ((*((u16 *) (((s8 *) shadow_camera) + 0xB8))) - shadow_yaw);
                ASM_USE2_NV(shadow_camera, shadow_roll);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                *((u16 *) (scratch + 0x100)) = (s16) shadow_pitch;
                *((u16 *) (scratch + 0x104)) = (s16) shadow_roll;
              }
              func_80065820(shadow_rotation, shadow_matrix_arg, shadow_yaw);
              func_80064840(&D_8006CD30, rotation_matrix, view_matrix);
              func_80064BC0(view_matrix, shadow_scale);
              func_80064D80((M2C_UNK *) view_matrix);
              func_80064CF0((M2C_UNK *) view_matrix);
              {
                register void *shadow_top_left ASM_REG("$4") = scratch + 0x70;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *shadow_top_right ASM_REG("$5") = scratch + 0x78;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *shadow_bottom_left ASM_REG("$6") = scratch + 0x80;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                register void *shadow_bottom_right ASM_REG("$7") = scratch + 0x88;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                u16 right_x;
                u16 left_x;
                shadow_quad = *((u8 **) (scratch + 0x018));
                func_800654B0(shadow_top_left, shadow_top_right, shadow_bottom_left, shadow_bottom_right, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, (GeomTailArgs){depth_cue, transform_flags}, (left_x = *((u16 *) (scratch + 0x070)), *((u8 **) (scratch + 0x018)) = ((u8 *) shadow_quad) + 0x28, right_x = *((u16 *) (scratch + 0x078)), left_x += 6, *((u16 *) (scratch + 0x070)) = left_x, right_x += 6, *((u16 *) (scratch + 0x078)) = right_x, *((GeomSideEffects *) 0)));
              }
              *((u16 *) (((s8 *) shadow_quad) + 8)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f0)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) shadow_quad) + 0xA)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f2)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x10)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f4)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x12)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f6)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x18)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f8)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x1A)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fa)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x20)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fc)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) shadow_quad) + 0x22)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fe)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((s8 *) (((s8 *) shadow_quad) + 3)) = 9;
              *((s32 *) (((s8 *) shadow_quad) + 0xC)) = (((s32) (*((s32 *) (scratch + 0x00c)))) + ((s32) (*((s32 *) (scratch + 0x008))))) + 0x7FC00000;
              top_right_uv = (s32) (*((s32 *) (scratch + 0x00c)));
              top_right_uv += ((s32) (*((s32 *) (scratch + 0x010))));
              *((s32 *) (((s8 *) shadow_quad) + 0x14)) = top_right_uv + ((*((s16 *) (((s8 *) sprite_part) + 0))) << 0x10);
              *((s16 *) (((s8 *) shadow_quad) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) shadow_quad) + 0x24)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              if (((s16) (*((u16 *) (((s8 *) shadow_quad) + 8)))) > ((s16) (*((u16 *) (((s8 *) shadow_quad) + 0x20)))))
              {
                *((u8 *) (((s8 *) shadow_quad) + 0x14)) = (u8) ((*((u8 *) (((s8 *) shadow_quad) + 0x14))) - 1);
                *((u8 *) (((s8 *) shadow_quad) + 0x24)) = (u8) ((*((u8 *) (((s8 *) shadow_quad) + 0x24))) - 1);
              }
              if (((s16) (*((u16 *) (((s8 *) shadow_quad) + 0xA)))) > ((s16) (*((u16 *) (((s8 *) shadow_quad) + 0x22)))))
              {
                *((u8 *) (((s8 *) shadow_quad) + 0x1D)) = (u8) ((*((u8 *) (((s8 *) shadow_quad) + 0x1D))) - 1);
                *((u8 *) (((s8 *) shadow_quad) + 0x25)) = (u8) ((*((u8 *) (((s8 *) shadow_quad) + 0x25))) - 1);
              }
              params = render_params;
              *((s32 *) (((s8 *) shadow_quad) + 4)) = (s32) (*((s32 *) (((s8 *) params) + 0xC)));
              *((u8 *) (((s8 *) shadow_quad) + 7)) = 0x2CU;
              func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), shadow_quad);
            }
          }
        }

        sprite_part = (void *) (((u8 *) sprite_part) + 12);
        if (((s8) (*((u8 *) (((s8 *) part_header) + 0)))) >= 0)
        {
          part_header = (void *) (((u8 *) part_header) + 12);
          goto next_sprite_part;
        }
        restore_matrix:
        func_80064D80(&saved_matrix);

        func_80064CF0(&saved_matrix);
        goto advance_entry;
      }
      goto advance_entry;
    }
    goto advance_entry;
  }
  advance_entry:
  entry_index += 1;

  if (entry_index >= 0x20)
  {
    register u8 *final_state ASM_REG("$8") = (u8 *) (&D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(final_state);
    *((void **) (((s8 *) (*((void **) (((s8 *) final_state) + 0)))) + 0x8D0)) = (void *) (*((u8 **) (scratch + 0x018)));
    return 0;
  }
  goto next_entry;
}
