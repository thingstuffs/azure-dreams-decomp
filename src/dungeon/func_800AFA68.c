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

s32 func_800B51C8(void *arg0, void *arg1, void * volatile arg2)
{
  u8 sp28[0x20];
  register u8 *transform_dst ASM_REG("$4") = sp28;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 var_s5 = 0;
  register u8 *mat ASM_REG("$22") = (u8 *) 0x1F8000D0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register u8 *mat_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  u8 *vec = (u8 *) 0x1F800050;
  u8 *viewport = (u8 *) 0x1F800090;
  u8 *viewport2 = (u8 *) 0x1F800094;
  u8 *transform_dst_b;
  u8 *dst_a;
  register u8 *mat_arg_a ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  u32 page_color;
  register u8 *init_global ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *d6_store_base1 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *d6_store_base2 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *scratch ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  volatile u16 sp48;
  volatile u16 sp4A;
  volatile u16 sp4C;
  register u16 init_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  register u16 init_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  register u16 init_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  s32 sp50[3];
  register u8 *var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 temp_a2;
  s32 temp_v0_10;
  u16 arg_x;
  u16 arg_y;
  register void *a2p ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  u16 ang_a;
  u16 rot_a;
  register u16 rot_b ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  u8 bx_a;
  u8 by_a;
  u8 bx_b;
  u8 by_b;
  s32 sx_a;
  s32 sy_a;
  s32 sx_b;
  register s32 sy_b ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 temp_a1;
  s32 sp2v;
  s32 ld010;
  s32 ld008;
  s32 ld014;
  s32 temp_v0_12;
  s32 temp_v1_10;
  s32 temp_v1_11;
  s32 decremented_component;
  s32 temp_v1_6;
  s32 var_a0;
  s32 var_a1;
  s32 var_a1_2;
  s32 var_a2;
  s32 var_v1;
  s32 var_v1_2;
  s32 var_a0b;
  s32 var_acc1;
  s32 var_acc1b;
  s32 var_a1_2b;
  s32 var_v1_3;
  s32 var_v1_4;
  u16 temp_a0;
  u16 t70;
  u16 raw48;
  s32 sum24_b;
  register s32 acc14 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 d6_val2;
  u8 *mat_arg_c;
  u16 raw_w2;
  u16 ld0ba;
  s32 shw2;
  u16 t78;
  u16 first_v0;
  u16 first_v1;
  u16 temp_v0;
  u32 temp_v0_11;
  u32 temp_v0_6;
  u32 temp_v0_7;
  u32 temp_v1_7;
  u8 temp_v0_2;
  u8 temp_v0_3;
  u8 temp_v1_2;
  u8 temp_v1_3;
  void *temp_a3;
  void *temp_s0;
  void *temp_s0_3;
  void *temp_s0_4;
  void *temp_s2;
  void *temp_s2_2;
  void *temp_s3;
  void *temp_v1;
  void *global_root;
  ASM_KEEP_MEM_NV(viewport2, *((void **) (((s8 *) (&D_80083160)) + 0)));   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  scratch = (u8 *) 0x1F800000;
  global_root = *((void **) (((s8 *) (&D_80083160)) + 0));
  init_global = ((u8 *) (&D_80083178)) - 0x18;
  ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
  init_v1 = *((u16 *) (((s8 *) init_global) + 0xC4));
  init_a1 = *((u16 *) (((s8 *) init_global) + 0xC6));
  init_a2 = *((u16 *) (((s8 *) init_global) + 0xC8));
  temp_a3 = *((void **) (((s8 *) global_root) + 0x8D0));
  *((u8 **) (scratch + 0x020)) = global_root + 0xB0;
  *((u16 *) (scratch + 0x08c)) = 0;
  *((u16 *) (scratch + 0x084)) = 0;
  *((u16 *) (scratch + 0x07c)) = 0;
  *((u16 *) (scratch + 0x074)) = 0;
  sp48 = init_v1;
  sp4A = init_a1;
  sp4C = init_a2;
  *((u8 **) (scratch + 0x018)) = temp_a3;
  func_80064AE0(transform_dst, init_a1, init_a2, temp_a3);
  loop_1:
  var_v0 = (u8 *) (&D_800E3648);

  temp_v1 = (void *) ((var_s5 * 4) + ((s32) var_v0));
  if ((((!((*((u8 *) (((s8 *) temp_v1) + 3))) & 0x80)) || (D_800E296C[0] & 8)) && ((*((u8 *) (((s8 *) temp_v1) + 1))) != 0)) && ((*((u8 *) (((s8 *) temp_v1) + 0))) != 0))
  {
    var_v0 = &D_800E39C8;
    temp_s0 = (var_s5 * 0x18) + var_v0;
    if ((*((u16 *) (((s8 *) temp_s0) + 0x14))) & 0x40)
    {
      func_800478B8(temp_s0);
    }
    *((u16 *) (scratch + 0x000)) = (s16) (((*((u8 *) (((s8 *) temp_s0) + 6))) << 6) + 0x20);
    *((u16 *) (scratch + 0x002)) = (u16) (((*((u8 *) (((s8 *) temp_s0) + 7))) << 6) + 0x20);
    temp_v0 = *((u16 *) (((s8 *) temp_s0) + 0x12));
    *((u16 *) (scratch + 0x004)) = temp_v0;
    temp_s3 = *((void **) (((s8 *) temp_s0) + 8));
    *((u16 *) (((s8 *) temp_s0) + 0x10)) = temp_v0;
    if (temp_s3 != 0)
    {
      if ((*((u16 *) (((s8 *) temp_s0) + 0x14))) & 0x100)
      {
        transform_dst = scratch + 0x100;
        mat_arg = mat;
        temp_a2 = *((s16 *) (scratch + 0x000));
        first_v1 = *((u16 *) (scratch + 0x002));
        *((s32 *) (scratch + 0x030)) = (s32) 0x2000;
        *((s32 *) (scratch + 0x034)) = (s32) 0x2000;
        *((s32 *) (scratch + 0x038)) = (s32) 0x2000;
        first_v0 = *((u16 *) (scratch + 0x004));
        temp_s2 = temp_s3 + 4;
        *((u16 *) (scratch + 0x100)) = 0;
        *((u16 *) (scratch + 0x102)) = 0U;
        *((u16 *) (scratch + 0x104)) = 0;
        *((s32 *) (scratch + 0x0e4)) = (s32) temp_a2;
        *((s32 *) (scratch + 0x0e8)) = (s32) ((s16) first_v1);
        *((s32 *) (scratch + 0x0ec)) = (s32) ((s16) first_v0);
        func_80065820(transform_dst, mat_arg, temp_a2);
        func_80064840(&sp28, mat, vec);
        func_80064BC0(vec, scratch + 0x30);
        func_80064D80((M2C_UNK *) vec);
        func_80064CF0((M2C_UNK *) vec);
        loop_arm_a:
        if (!((*((u8 *) (((s8 *) temp_s3) + 0))) & 0x20))
        {
          temp_v0_2 = *((u8 *) (((s8 *) temp_s2) + 4));
          *((s32 *) (scratch + 0x008)) = (s32) temp_v0_2;
          temp_v1_2 = *((u8 *) (((s8 *) temp_s2) + 6));
          *((s32 *) (scratch + 0x010)) = (s32) temp_v1_2;
          if ((temp_v0_2 + temp_v1_2) >= 0x100)
          {
            *((s32 *) (scratch + 0x010)) = temp_v1_2 - 1;
          }
          temp_v0_3 = *((u8 *) (((s8 *) temp_s2) + 5));
          *((s32 *) (scratch + 0x00c)) = (s32) temp_v0_3;
          temp_v1_3 = *((u8 *) (((s8 *) temp_s2) + 7));
          *((s32 *) (scratch + 0x014)) = (s32) temp_v1_3;
          if ((temp_v0_3 + temp_v1_3) >= 0x100)
          {
            *((s32 *) (scratch + 0x014)) = temp_v1_3 - 1;
          }
          {
            register void *c1_a0 ASM_REG("$4") = scratch + 0x70;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register void *c1_a1 ASM_REG("$5") = scratch + 0x78;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register void *c1_a2 ASM_REG("$6") = scratch + 0x80;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register void *c1_a3 ASM_REG("$7") = scratch + 0x88;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            bx_a = *((u8 *) (((s8 *) temp_s2) + (-2)));
            ASM_USE_NV(bx_a);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            sx_a = (s8) bx_a;
            temp_s0_3 = *((u8 **) (scratch + 0x018));
            *((u16 *) (scratch + 0x080)) = sx_a;
            *((u16 *) (scratch + 0x070)) = sx_a;
            sx_a += (u16) (*((u16 *) (scratch + 0x010)));
            *((u16 *) (scratch + 0x088)) = sx_a;
            *((u16 *) (scratch + 0x078)) = sx_a;
            by_a = *((u8 *) (((s8 *) temp_s2) + (-1)));
            *((u8 **) (scratch + 0x018)) = temp_s0_3 + 0x28;
            temp_v0_6 = func_80065590(c1_a0, c1_a1, c1_a2, c1_a3, temp_s0_3 + 8, temp_s0_3 + 0x10, temp_s0_3 + 0x18, temp_s0_3 + 0x20, (GeomTailArgs){viewport, viewport2}, (sy_a = (s8) by_a, *((u16 *) (scratch + 0x07a)) = sy_a, *((u16 *) (scratch + 0x072)) = sy_a, sy_a += (u16) (*((u16 *) (scratch + 0x014))), *((u16 *) (scratch + 0x08a)) = sy_a, *((u16 *) (scratch + 0x082)) = sy_a, *((GeomSideEffects *) 0)));
            *((s32 *) (scratch + 0x0c0)) = temp_v0_6;
          }
          if (temp_v0_6 < 0x1E0U)
          {
            var_a1 = 0;
            if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 8))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0xA))) + 0x20);
              var_a1 = visibility_y < 0x121U;
            }
            var_v1 = 0;
            if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0x12))) + 0x20);
              var_v1 = visibility_y < 0x121U;
            }
            var_a0 = 0;
            var_acc1 = var_a1 | var_v1;
            if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0x1A))) + 0x20);
              var_a0 = visibility_y < 0x121U;
            }
            var_v1_2 = 0;
            var_a0b = var_acc1 | var_a0;
            if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U)
            {
              u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0x22))) + 0x20);
              var_v1_2 = visibility_y < 0x121U;
            }
            if ((var_a0b | var_v1_2) != 0)
            {
              ld010 = *((s32 *) (scratch + 0x010));
              ld008 = *((s32 *) (scratch + 0x008));
              ld014 = *((s32 *) (scratch + 0x014));
              temp_a1 = *((s32 *) (scratch + 0x00c));
              *((s32 *) (scratch + 0x010)) = ld010 + ld008;
              *((s32 *) (scratch + 0x014)) = ld014 + temp_a1;
              *((s32 *) (scratch + 0x00c)) <<= 8;
              *((s32 *) (scratch + 0x014)) <<= 8;
              *((u16 *) (((s8 *) temp_s0_3) + 0xE)) = (u16) (*((u16 *) (((s8 *) temp_s2) + 2)));
              *((s16 *) (((s8 *) temp_s0_3) + 0xC)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) temp_s0_3) + 0x14)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              *((u16 *) (((s8 *) temp_s0_3) + 0x16)) = (u16) (*((u16 *) (((s8 *) temp_s2) + 0)));
              *((s16 *) (((s8 *) temp_s0_3) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) temp_s0_3) + 0x24)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              a2p = arg2;
              *((s32 *) (((s8 *) temp_s0_3) + 4)) = (s32) (*((s32 *) (((s8 *) a2p) + 0xC)));
              func_800666F4(temp_s0_3, temp_a1);
              *((u8 *) (((s8 *) temp_s0_3) + 7)) = (u8) ((*((u8 *) (((s8 *) temp_s0_3) + 7))) | 2);
              func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), temp_s0_3);
            }
          }
        }

        temp_s2 = (void *) (((u8 *) temp_s2) + 12);
        if (((s8) (*((u8 *) (((s8 *) temp_s3) + 0)))) >= 0)
        {
          temp_s3 = (void *) (((u8 *) temp_s3) + 12);
          goto loop_arm_a;
        }
        goto block_61;
      }
      *((s32 *) (scratch + 0x0e4)) = 0;
      *((s32 *) (scratch + 0x0e8)) = 0;
      *((s32 *) (scratch + 0x0ec)) = 0;
      temp_v0_7 = func_80065420(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
      *((s32 *) (scratch + 0x0c0)) = temp_v0_7;
      ASM_KEEP_MEMDEP_NV(temp_v0_7, page_color, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
      temp_v1_7 = temp_v0_7;
      ASM_KEEP_MEM_NV(temp_v1_7, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      temp_v0_10 = temp_v0_7 * 4;
      d6_store_base1 = (u8 *) 0x80070000;
      ASM_KEEP_NV(d6_store_base1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      d6_store_base1 -= 13008;
      ASM_USE_NV(d6_store_base1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
      *((s32 *) (((s8 *) d6_store_base1) + 0x1C)) = temp_v0_10;
      temp_v1_7 -= 4;
      *((s32 *) (scratch + 0x0c0)) = temp_v1_7;
      if (temp_v1_7 < 0x1E0U)
      {
        register u8 *post_global ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        mat_arg_a = mat;
        dst_a = scratch + 0x100;
        ASM_USE_NV(dst_a);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        *((u16 *) (scratch + 0x0b8)) = (u16) ((*((u16 *) (scratch + 0x0b8))) - 0xA0);
        raw48 = sp48;
        *((u16 *) (scratch + 0x0ba)) = (u16) ((*((u16 *) (scratch + 0x0ba))) - 0x78);
        a2p = arg2;
        *((u16 *) (scratch + 0x100)) = (s16) ((*((u16 *) (((s8 *) a2p) + 0x16))) + (((s32) (raw48 << 0x10)) >> 0x11));
        ang_a = *((u16 *) (((s8 *) a2p) + 0x1A));
        post_global = (u8 *) 0x80080000;
        ASM_KEEP_NV(post_global);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        post_global += 12640;
        ASM_USE_NV(post_global);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        rot_a = sp4A;
        *((u16 *) (scratch + 0x104)) = (s16) ((*((u16 *) (((s8 *) post_global) + 0xB8))) + (ang_a - rot_a));
        temp_s2_2 = temp_s3 + 4;
        a2p = arg2;
        *((u16 *) (scratch + 0x102)) = (u16) (*((u16 *) (((s8 *) a2p) + 0x18)));
        func_80065820(dst_a, mat_arg_a, rot_a);
        func_80064840(&D_8006CD30, mat, vec);
        func_80064D80((M2C_UNK *) vec);
        func_80064CF0((M2C_UNK *) vec);
        loop_arm_b:
        if (!((*((u8 *) (((s8 *) temp_s3) + 0))) & 0x20))
        {
          *((s32 *) (scratch + 0x008)) = (s32) (*((u8 *) (((s8 *) temp_s2_2) + 4)));
          *((s32 *) (scratch + 0x00c)) = (s32) (*((u8 *) (((s8 *) temp_s2_2) + 5)));
          *((s32 *) (scratch + 0x010)) = (s32) (*((u8 *) (((s8 *) temp_s2_2) + 6)));
          *((s32 *) (scratch + 0x014)) = (s32) (*((u8 *) (((s8 *) temp_s2_2) + 7)));
          bx_b = *((volatile u8 *) (((s8 *) temp_s2_2) + (-2)));
          sx_b = (s8) bx_b;
          *((u16 *) (scratch + 0x080)) = sx_b;
          *((u16 *) (scratch + 0x070)) = sx_b;
          sx_b += (u16) (*((u16 *) (scratch + 0x010)));
          *((u16 *) (scratch + 0x088)) = sx_b;
          *((u16 *) (scratch + 0x078)) = sx_b;
          by_b = *((u8 *) (((s8 *) temp_s2_2) + (-1)));
          func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, (GeomTailArgs){viewport, viewport2}, (sy_b = (s8) by_b, *((u16 *) (scratch + 0x07a)) = sy_b, *((u16 *) (scratch + 0x072)) = sy_b, sy_b += (u16) (*((u16 *) (scratch + 0x014))), *((u16 *) (scratch + 0x08a)) = sy_b, *((u16 *) (scratch + 0x082)) = sy_b, *((GeomSideEffects *) 0)));
          temp_s0_3 = *((u8 **) (scratch + 0x018));
          *((u8 **) (scratch + 0x018)) = temp_s0_3 + 0x28;
          *((u16 *) (((s8 *) temp_s0_3) + 8)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f0)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0xA)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f2)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0x10)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f4)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0x12)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f6)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0x18)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f8)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0x1A)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fa)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          var_a2 = 0;
          *((u16 *) (((s8 *) temp_s0_3) + 0x20)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fc)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
          temp_a0 = (u16) (((s32) (*((u16 *) (scratch + 0x0fe)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
          *((u16 *) (((s8 *) temp_s0_3) + 0x22)) = temp_a0;
          if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 8))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0xA))) + 0x20);
            var_a2 = visibility_y < 0x121U;
          }
          var_v1_3 = 0;
          if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0x12))) + 0x20);
            var_v1_3 = visibility_y < 0x121U;
          }
          var_a1_2 = 0;
          var_a2 |= var_v1_3;
          if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) temp_s0_3) + 0x1A))) + 0x20);
            var_a1_2 = visibility_y < 0x121U;
          }
          var_v1_4 = 0;
          var_a1_2b = var_a2 | var_a1_2;
          if (((u32) (((*((u16 *) (((s8 *) temp_s0_3) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U)
          {
            u16 visibility_y = (u16) (temp_a0 + 0x20);
            var_v1_4 = visibility_y < 0x121U;
          }
          if ((var_a1_2b | var_v1_4) != 0)
          {
            *((s8 *) (((s8 *) temp_s0_3) + 3)) = 9;
            decremented_component = ((s32) (*((s32 *) (scratch + 0x010)))) - 1;
            temp_v1_10 = decremented_component + ((s32) (*((s32 *) (scratch + 0x008))));
            *((s32 *) (scratch + 0x010)) = temp_v1_10;
            if (temp_v1_10 & 0x100)
            {
              *((s32 *) (scratch + 0x010)) = temp_v1_10 - 1;
            }
            decremented_component = ((s32) (*((s32 *) (scratch + 0x014)))) - 1;
            temp_v1_11 = decremented_component + ((s32) (*((s32 *) (scratch + 0x00c))));
            *((s32 *) (scratch + 0x014)) = temp_v1_11;
            if (temp_v1_11 & 0x100)
            {
              *((s32 *) (scratch + 0x014)) = temp_v1_11 - 1;
            }
            *((s32 *) (scratch + 0x00c)) <<= 8;
            *((s32 *) (scratch + 0x014)) <<= 8;
            *((s16 *) (((s8 *) temp_s0_3) + 0xC)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
            *((u16 *) (((s8 *) temp_s0_3) + 0xE)) = (u16) (*((u16 *) (((s8 *) temp_s2_2) + 2)));
            *((s16 *) (((s8 *) temp_s0_3) + 0x14)) = (s16) (((u16) (*((u16 *) (scratch + 0x00c)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
            *((u16 *) (((s8 *) temp_s0_3) + 0x16)) = (u16) (*((u16 *) (((s8 *) temp_s2_2) + 0)));
            *((s16 *) (((s8 *) temp_s0_3) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
            sum24_b = ((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010))));
            *((s16 *) (((s8 *) temp_s0_3) + 0x24)) = (s16) sum24_b;
            if (((s16) (*((u16 *) (((s8 *) temp_s0_3) + 8)))) > ((s16) (*((u16 *) (((s8 *) temp_s0_3) + 0x20)))))
            {
              *((u8 *) (((s8 *) temp_s0_3) + 0x14)) = (u8) ((*((u8 *) (((s8 *) temp_s0_3) + 0x14))) - 1);
              *((u8 *) (((s8 *) temp_s0_3) + 0x24)) = (u8) ((*((u8 *) (((s8 *) temp_s0_3) + 0x24))) - 1);
            }
            if (((s16) (*((u16 *) (((s8 *) temp_s0_3) + 0xA)))) > ((s16) (*((u16 *) (((s8 *) temp_s0_3) + 0x22)))))
            {
              *((u8 *) (((s8 *) temp_s0_3) + 0x1D)) = (u8) ((*((u8 *) (((s8 *) temp_s0_3) + 0x1D))) - 1);
              *((u8 *) (((s8 *) temp_s0_3) + 0x25)) = (u8) ((*((u8 *) (((s8 *) temp_s0_3) + 0x25))) - 1);
            }
            a2p = arg2;
            *((s32 *) (((s8 *) temp_s0_3) + 4)) = (s32) (*((s32 *) (((s8 *) a2p) + 0xC)));
            *((u8 *) (((s8 *) temp_s0_3) + 7)) = 0x2CU;
            if ((D_800E296C[0] & 8) && (D_800E3648_entries[var_s5].b3 & 0x80))
            {
              *((u8 *) (((s8 *) temp_s0_3) + 7)) = 0x2EU;
            }
            func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), temp_s0_3, var_a2);
            if (!((*((u8 *) (((s8 *) temp_s0_3) + 7))) & 2))
            {
              register u8 *post_global2 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
              func_80064D80(&sp28);
              func_80064CF0(&sp28);
              arg_x = *((u16 *) (scratch + 0x000));
              arg_y = *((u16 *) (scratch + 0x002));
              temp_a0 = *((u16 *) (scratch + 0x004));
              ASM_USE2_NV(arg_x, temp_a0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
              temp_v0_10 = (s16) temp_a0;
              temp_v0_10 -= 4;
              sp50[2] = temp_v0_10;
              *((u16 *) (scratch + 0x004)) = func_800BCB04(arg_x, arg_y, (s16) temp_v0_10);
              temp_v0_11 = func_80065420(scratch, scratch + 0xB8, viewport, viewport2);
              *((s32 *) (scratch + 0x0c0)) = temp_v0_11;
              ASM_KEEP_MEMDEP_NV(temp_v0_11, page_color, *((s32 *) (scratch + 0x0c0)));   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
              temp_v0_10 = temp_v0_11 * 4;
              d6_store_base2 = (u8 *) 0x80070000;
              ASM_KEEP_NV(d6_store_base2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
              d6_store_base2 -= 13008;
              ASM_USE_NV(d6_store_base2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
              *((s32 *) (((s8 *) d6_store_base2) + 0x1C)) = temp_v0_10;
              *((s32 *) (scratch + 0x0c0)) -= 3;
              ld0ba = *((u16 *) (scratch + 0x0ba));
              *((u16 *) (scratch + 0x0b8)) = (u16) ((*((u16 *) (scratch + 0x0b8))) - 0xA0);
              raw_w2 = *((u16 *) (scratch + 0x004));
              shw2 = ((s32) raw_w2) << 0x10;
              *((u16 *) (scratch + 0x0ba)) = (u16) (ld0ba - 0x78);
              temp_v0_12 = ((sp50[2] - (shw2 >> 0x10)) << 5) + 0x1000;
              sp50[2] = temp_v0_12;
              if (temp_v0_12 < 0)
              {
                sp50[2] = 0;
              }
              transform_dst_b = scratch + 0x100;
              ASM_USE_NV(transform_dst_b);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
              mat_arg_c = mat;
              ASM_KEEP_NV(mat_arg_c);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
              post_global2 = (u8 *) (&D_80083160);
              sp2v = sp50[2];
              *((u16 *) (scratch + 0x102)) = 0U;
              rot_b = sp4A;
              sp50[0] = sp2v;
              sp2v += (s32) (((u32) sp2v) >> 0x1F);
              sp2v >>= 1;
              sp50[1] = sp2v;
              {
                u16 v100 = (u16) (0 - sp48);
                u16 v104 = (u16) ((*((u16 *) (((s8 *) post_global2) + 0xB8))) - rot_b);
                ASM_USE2_NV(post_global2, v104);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                *((u16 *) (scratch + 0x100)) = (s16) v100;
                *((u16 *) (scratch + 0x104)) = (s16) v104;
              }
              func_80065820(transform_dst_b, mat_arg_c, rot_b);
              func_80064840(&D_8006CD30, mat, vec);
              func_80064BC0(vec, sp50);
              func_80064D80((M2C_UNK *) vec);
              func_80064CF0((M2C_UNK *) vec);
              {
                register void *call_a0 ASM_REG("$4") = scratch + 0x70;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *call_a1 ASM_REG("$5") = scratch + 0x78;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *call_a2 ASM_REG("$6") = scratch + 0x80;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                register void *call_a3 ASM_REG("$7") = scratch + 0x88;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                u16 call_y;
                u16 call_x;
                temp_s0_4 = *((u8 **) (scratch + 0x018));
                func_800654B0(call_a0, call_a1, call_a2, call_a3, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, (GeomTailArgs){viewport, viewport2}, (call_x = *((u16 *) (scratch + 0x070)), *((u8 **) (scratch + 0x018)) = ((u8 *) temp_s0_4) + 0x28, call_y = *((u16 *) (scratch + 0x078)), call_x += 6, *((u16 *) (scratch + 0x070)) = call_x, call_y += 6, *((u16 *) (scratch + 0x078)) = call_y, *((GeomSideEffects *) 0)));
              }
              *((u16 *) (((s8 *) temp_s0_4) + 8)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f0)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0xA)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f2)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x10)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f4)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x12)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f6)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x18)) = (u16) (((s32) (*((u16 *) (scratch + 0x0f8)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x1A)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fa)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x20)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fc)))) + ((s32) (*((u16 *) (scratch + 0x0b8)))));
              *((u16 *) (((s8 *) temp_s0_4) + 0x22)) = (u16) (((s32) (*((u16 *) (scratch + 0x0fe)))) + ((s32) (*((u16 *) (scratch + 0x0ba)))));
              *((s8 *) (((s8 *) temp_s0_4) + 3)) = 9;
              *((s32 *) (((s8 *) temp_s0_4) + 0xC)) = (((s32) (*((s32 *) (scratch + 0x00c)))) + ((s32) (*((s32 *) (scratch + 0x008))))) + 0x7FC00000;
              acc14 = (s32) (*((s32 *) (scratch + 0x00c)));
              acc14 += ((s32) (*((s32 *) (scratch + 0x010))));
              *((s32 *) (((s8 *) temp_s0_4) + 0x14)) = acc14 + ((*((s16 *) (((s8 *) temp_s2_2) + 0))) << 0x10);
              *((s16 *) (((s8 *) temp_s0_4) + 0x1C)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x008)))));
              *((s16 *) (((s8 *) temp_s0_4) + 0x24)) = (s16) (((u16) (*((u16 *) (scratch + 0x014)))) + ((u16) (*((u16 *) (scratch + 0x010)))));
              if (((s16) (*((u16 *) (((s8 *) temp_s0_4) + 8)))) > ((s16) (*((u16 *) (((s8 *) temp_s0_4) + 0x20)))))
              {
                *((u8 *) (((s8 *) temp_s0_4) + 0x14)) = (u8) ((*((u8 *) (((s8 *) temp_s0_4) + 0x14))) - 1);
                *((u8 *) (((s8 *) temp_s0_4) + 0x24)) = (u8) ((*((u8 *) (((s8 *) temp_s0_4) + 0x24))) - 1);
              }
              if (((s16) (*((u16 *) (((s8 *) temp_s0_4) + 0xA)))) > ((s16) (*((u16 *) (((s8 *) temp_s0_4) + 0x22)))))
              {
                *((u8 *) (((s8 *) temp_s0_4) + 0x1D)) = (u8) ((*((u8 *) (((s8 *) temp_s0_4) + 0x1D))) - 1);
                *((u8 *) (((s8 *) temp_s0_4) + 0x25)) = (u8) ((*((u8 *) (((s8 *) temp_s0_4) + 0x25))) - 1);
              }
              a2p = arg2;
              *((s32 *) (((s8 *) temp_s0_4) + 4)) = (s32) (*((s32 *) (((s8 *) a2p) + 0xC)));
              *((u8 *) (((s8 *) temp_s0_4) + 7)) = 0x2CU;
              func_8006658C(((u8 *) (*((u8 **) (scratch + 0x020)))) + (((s32) (*((s32 *) (scratch + 0x0c0)))) * 4), temp_s0_4);
            }
          }
        }

        temp_s2_2 = (void *) (((u8 *) temp_s2_2) + 12);
        if (((s8) (*((u8 *) (((s8 *) temp_s3) + 0)))) >= 0)
        {
          temp_s3 = (void *) (((u8 *) temp_s3) + 12);
          goto loop_arm_b;
        }
        block_61:
        func_80064D80(&sp28);

        func_80064CF0(&sp28);
        goto block_62;
      }
      goto block_62;
    }
    goto block_62;
  }
  block_62:
  var_s5 += 1;

  if (var_s5 >= 0x20)
  {
    register u8 *final_global ASM_REG("$8") = (u8 *) (&D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(final_global);
    *((void **) (((s8 *) (*((void **) (((s8 *) final_global) + 0)))) + 0x8D0)) = (void *) (*((u8 **) (scratch + 0x018)));
    return 0;
  }
  goto loop_1;
}
