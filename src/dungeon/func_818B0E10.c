#include "common.h"
#include "m2c_compat.h"

extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern unsigned char D_80080000[];
__asm__(".set D_80080000, 0x80080000");
extern struct S_80083178 D_80083178;
extern struct S_80083178State D_80083CE8;
s32 func_80065420();
s32 func_80066460();
M2C_UNK func_80067F20();
extern M2C_UNK D_8002588C;
typedef struct 
{
  u8 pad0[0x8D0];
  u8 *nextPrim;
} RenderState;
typedef struct 
{
  RenderState *ctx;
  u8 pad0[0x20];
} GlobalState;
extern GlobalState D_80083160;
s32 func_818B0E10(s32 arg0, void *arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5, u8 arg6, u16 arg7)
{
  register u8 *init_page ASM_REG("$4") = D_80080000;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s32 count ASM_REG("$22") = 15;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register s32 factor_base ASM_REG("$21") = (s16) arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register s32 src_base ASM_REG("$2") = arg5;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  register s32 initial_arg4 ASM_REG("$3") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  s16 index = (s16) arg7;
  void *sp20 = (void *) 0x1F800084;
  register s32 color ASM_REG("$23") = arg6;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  register s32 mask ASM_REG("$20") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  s32 top = 0xFF000000;
  register s32 *src ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
  u8 *prim;
  register RenderState *initial_ctx ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  GlobalState *base = &D_80083160;
  register s32 mid ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  src = (s32 *) (((u8 *) src_base) + 0x3C);
  initial_ctx = *((RenderState **) (init_page + 0x3160));
  scratch = (u8 *) 0x1F800000;
  ASM_KEEP(top);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  ASM_KEEP(factor_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  *((u16 *) (scratch + 0x70)) = (u16) initial_arg4;
  *((u16 *) (scratch + 0x68)) = (u16) initial_arg4;
  *((void **) (scratch + 0x18)) = ((u8 *) initial_ctx) + 0xB0;
  do
  {
    register s32 index_value ASM_REG("$2") = index;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 pos ASM_REG("$5") = count + index_value;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 rounded = pos;
    s32 next_pos;
    s32 scale_tmp;
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 raw_color ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    RenderState *ctx;
    s32 code;
    s32 sign;
    register s32 magic ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    union {
      s64 both;
      struct { s32 hi; u32 lo; } word;
    } wide_product;
    raw_color = color << 16;
    magic = (s32) 0x80808081U;
    wide_product.both = (s64) raw_color * magic;
    ctx = base->ctx;
    prim = ctx->nextPrim;
    ctx->nextPrim = prim + 0x14;
    prim[3] = 4;
    code = 0x52;
    sign = raw_color >> 31;
    prim[7] = (u8) code;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    value = (wide_product.word.hi - -raw_color) >> 7;
    scale_tmp = value - sign;
    {
      register s32 scale ASM_REG("$4") = scale_tmp;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
      register s32 saved_scale ASM_REG("$7") = scale;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      register s32 product ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
      if (pos < 0)
      {
        rounded = pos + 15;
      }
      product = scale * (*((u8 *) (((u8 *) (&D_8002588C)) + (pos - ((rounded >> 4) << 4)))));
      value = product >> 18;
      scale = saved_scale;
      next_pos = pos + 1;
      rounded = next_pos;
      prim[5] = color;
      prim[4] = (s8) value;
      prim[6] = (s8) value;
      if (next_pos < 0)
      {
        rounded = pos + 16;
      }
      product = scale * (*((u8 *) (((u8 *) (&D_8002588C)) + (next_pos - ((rounded >> 4) << 4)))));
      prim[0xD] = color;
      value = product >> 18;
      prim[0xC] = (s8) value;
      prim[0xE] = (s8) value;
    }
    {
      u8 *coord = (u8 *) arg1;
      s32 value;
      s32 delta;
      value = *src;
      delta = value * factor_base;
      delta >>= 8;
      *((u16 *) (scratch + 0x64)) = (*((u16 *) (coord + 2))) + delta;
      value = src[1];
      delta = value * factor_base;
      delta >>= 8;
      *((u16 *) (scratch + 0x6C)) = (*((u16 *) (coord + 2))) + delta;
      value = src[0x11];
      delta = value * factor_base;
      delta >>= 8;
      *((u16 *) (scratch + 0x66)) = (*((u16 *) (coord + 6))) + delta;
      value = src[0x12];
      delta = value * factor_base;
      delta >>= 8;
      *((u16 *) (scratch + 0x6E)) = (*((u16 *) (coord + 6))) + delta;
    }
    {
      void *out1 = scratch + 0xD8;
      u8 *geom;
      geom = scratch + 0x88;
      *((s32 *) (scratch + 0xF4)) = func_80065420(scratch + 0x64, out1, sp20, geom);
      *((s32 *) (scratch + 0xF8)) = func_80065420(scratch + 0x6C, scratch + 0xDC, sp20, geom);
    }
    *((u16 *) (prim + 8)) = *((u16 *) (scratch + 0xD8));
    *((u16 *) (prim + 0xA)) = *((u16 *) (scratch + 0xDA));
    *((u16 *) (prim + 0x10)) = *((u16 *) (scratch + 0xDC));
    *((u16 *) (prim + 0x12)) = *((u16 *) (scratch + 0xDE));
    {
      register s32 sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
      sum = *((s32 *) (scratch + 0xF4));
      sum += *((s32 *) (scratch + 0xF8));
      mid = sum / 2;
    }
    ASM_KEEP_NV(mid);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    *((s32 *) (scratch + 0xB4)) = mid;
    if (((u32) mid) < 0x1E0U)
    {
      u8 *prim2;
      *((s32 *) prim) = ((*((s32 *) prim)) & top) | (((s32 *) (*((void **) (scratch + 0x18))))[mid] & mask);
      {
        register u32 entry ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u32 *table ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        u32 old_entry;
        register u32 prim_low ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        entry = *((u32 *) (scratch + 0xB4));
        table = *((u32 **) (scratch + 0x18));
        entry = (entry << 2) + ((u32) table);
        old_entry = *((u32 *) entry);
        prim_low = ((u32) prim) & mask;
        *((u32 *) entry) = (old_entry & top) | prim_low;
      }
      prim2 = base->ctx->nextPrim;
      base->ctx->nextPrim = prim2 + 0xC;
      func_80067F20(prim2, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
      *((s32 *) prim2) = ((*((s32 *) prim2)) & top) | (((s32 *) (*((void **) (scratch + 0x18))))[*((s32 *) (scratch + 0xB4))] & mask);
      *(((s32 *) (*((void **) (scratch + 0x18)))) + (*((s32 *) (scratch + 0xB4)))) = ((*(((s32 *) (*((void **) (scratch + 0x18)))) + (*((s32 *) (scratch + 0xB4))))) & top) | (((s32) prim2) & mask);
    }
    count -= 1;
    src = (s32 *) (((u8 *) src) - 4);
  }
  while (count >= 0);
  return 0;
}
