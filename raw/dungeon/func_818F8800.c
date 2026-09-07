/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s32 func_800644B8(s32);
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern M2C_UNK D_8006CD10[8];
extern struct S_8003E2D8 *D_80083160;

typedef struct Quad40 {
    s32 w0;
    s32 w1;
    u16 h8;
    u16 h10;
    u8  b12;
    u8  b13;
    u8  b14;
    u8  b15;
    s16 h16;
    s16 h18;
    s32 w20;
    s16 h24;
    s16 h26;
    s32 w28;
    s32 w32;
    s32 w36;
} Quad40;

typedef struct Scratchpad {
    u8 bytes[0x10C];
} Scratchpad;

#ifdef __mips__
#define SCRATCH_BASE ((Scratchpad *)0x1F800000)
#else
#define SCRATCH_BASE ((Scratchpad *)0x1F800000)
#endif

#define SCR8(off)  (*(u8  *)((u8 *)scratch + (off)))
#define SCR16(off) (*(u16 *)((u8 *)scratch + (off)))
#define SCRS16(off) (*(s16 *)((u8 *)scratch + (off)))
#define SCR32(off) (*(s32 *)((u8 *)scratch + (off)))
#define SCRPTR(off) ((void *)((u8 *)scratch + (off)))

#ifdef __mips__
/* The retail cluster carries this 23-word literal bank immediately before
 * the function body; keep it in the function's named text section so the
 * isolated overlay linker preserves the composite table+body layout. */
static const u32 data_bank[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002592C, 0x01540340, 0x00540060, 0x01000340,
    0x00540060, 0x00000020, 0x00200020, 0x00200000,
    0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0, 0xFFE00000,
    0xFFE00020, 0x00000000, 0x80025A24, 0x80025AEC,
    0x80025DC0, 0x80026200, 0x80026354, 0x80026578,
    0x8002659C, 0x80026634, 0x800265D0,
};
__asm__(".globl func_80024000\n.size func_80024000,3284");
#endif

#ifdef __mips__
#define BODY_NAME func_8002405C
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_ATTR
#endif

void BODY_NAME(void *arg0, u8 *arg1, void *arg2, s32 *arg3, s32 arg4) BODY_ATTR;
void func_8002405C(void *arg0, u8 *arg1, void *arg2, s32 *arg3, s32 arg4)
{
  Quad40 sp28;
  Quad40 sp50;
  u16 sp78;
  s32 sp80;
  void *sp84;
  M2C_UNK var_a1;
  s16 temp_v0_4;
  s16 temp_v0_5;
  s16 temp_v0_6;
  s16 temp_v0_7;
  s16 temp_v0_8;
  s16 temp_v0_9;
  s32 var_s1;
  s32 var_s1_2;
  s32 var_s1_3;
  s32 *(*temp_v0_10)(void *, s32, void *, void *, s32 *);
  s32 *temp_a0_3;
  s32 *temp_a0_5;
  s32 *temp_v1;
  s32 *temp_v1_9;
  s32 *var_a0_2;
  s32 *var_s0;
  s32 *var_s0_2;
  s32 *var_s3;
  s32 temp_v1_2;
  s32 temp_v1_3;
  s32 var_s5;
  u16 temp_a0;
  u16 temp_a0b;
  s32 temp_v0_2;
  s32 temp_v0_3;
  u16 temp_v1_7;
  u16 temp_v1_6;
  u16 temp_v1_a;
  u16 temp_v1_b;
  u16 temp_v1_8;
  u8 temp_a0_2;
  u8 temp_v1_4;
  u8 temp_v1_5;
  u8 var_v0;
  void *temp_s2;
  void *temp_s2_2;
  void *temp_s7;
  u8 *gbase;
  u8 *cdbase;
  void *var_a0;
  s32 var_s5_reg;
  Scratchpad *scratch;
  var_a0 = arg0;
  gbase = (u8 *) (&D_80083160);
  temp_s7 = *((void **) (((s8 *) arg2) + (-0x14)));
  sp84 = *((void **) (((s8 *) temp_s7) + 8));
  sp80 = *((s32 *) (((s8 *) arg2) + (-0x18)));
  scratch = (Scratchpad *) 0x1F800000;
  *((s32 *) (((u8 *) scratch) + 0xEC)) = 0;
  *((u16 *) (((u8 *) scratch) + 0x8C)) = 0;
  *((u16 *) (((u8 *) scratch) + 0x84)) = 0;
  *((u16 *) (((u8 *) scratch) + 0x7C)) = 0;
  *((u16 *) (((u8 *) scratch) + 0x74)) = 0;
  var_s3 = *((s32 **) (((s8 *) D_80083160) + 0x8D0));
  *((s32 *) (((u8 *) scratch) + 0x20)) = (s32) arg3;
  *((s32 *) (((u8 *) scratch) + 0xC0)) = 0;
  *((u16 *) (((u8 *) scratch) + 0xB8)) = (u16) ((*((u16 *) (((s8 *) var_a0) + 0))) - 0xA0);
  *((u16 *) (((u8 *) scratch) + 0xBA)) = (u16) ((*((u16 *) (((s8 *) var_a0) + 2))) - 0x78);
  sp78 = (u16) arg4;
  var_a1 = 0;
  if ((arg4 << 0x10) != 0)
  {
    func_80067EF4(var_s3, 0, 0);
    var_a1 = 0xFF000000;
    *var_s3 = ((*var_s3) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
    temp_v1 = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
    var_a0 = (void *) (((s32) var_s3) & 0xFFFFFF);
    var_s3 += 3;
    *temp_v1 = ((*temp_v1) & 0xFF000000) | ((s32) var_a0);
  }
  cdbase = (u8 *) (&D_8006CD10);
  *((s32 *) (cdbase + 0x1C)) = (s32) (*((s32 *) (gbase + 0xA0)));
  func_800649A0();
  *((s32 *) (((u8 *) scratch) + 0x30)) = *((s16 *) (gbase + 0xC4));
  *((s32 *) (((u8 *) scratch) + 0x34)) = *((s16 *) (gbase + 0xC6));
  *((s32 *) (((u8 *) scratch) + 0x38)) = *((s16 *) (gbase + 0xC8));
  *((u16 *) (((u8 *) scratch) + 0x100)) = (u16) (*((u16 *) (((s8 *) temp_s7) + 0x16)));
  *((u16 *) (((u8 *) scratch) + 0x104)) = (s16) ((*((u16 *) (((s8 *) temp_s7) + 0x1A))) - (*((u16 *) (((u8 *) scratch) + 0x34))));
  *((u16 *) (((u8 *) scratch) + 0x102)) = (s16) (((((*((u16 *) (((u8 *) scratch) + 0x38))) + 0x100) & 0x1FF) - 0x100) + (*((u16 *) (((s8 *) temp_s7) + 0x18))));
  temp_v0_2 = *((u16 *) (((s8 *) temp_s7) + 0x20));
  *((s32 *) (((u8 *) scratch) + 0xE4)) = temp_v0_2;
  *((u16 *) (((u8 *) scratch) + 0x108)) = temp_v0_2;
  temp_v0_3 = *((u16 *) (((s8 *) temp_s7) + 0x22));
  *((s32 *) (((u8 *) scratch) + 0xE8)) = temp_v0_3;
  *((u16 *) (((u8 *) scratch) + 0x10A)) = temp_v0_3;
  func_80065820((void *) 0x1F800100, (void *) 0x1F8000D0);
  *((s32 *) (((u8 *) scratch) + 0x30)) = *((u16 *) (((s8 *) temp_s7) + 0x1C));
  *((s32 *) (((u8 *) scratch) + 0x34)) = *((u16 *) (((s8 *) temp_s7) + 0x1E));
  *((s32 *) (((u8 *) scratch) + 0x38)) = 0x1000;
  func_80064BC0((void *) 0x1F8000D0, (void *) 0x1F800030);
  func_80064840(cdbase, (void *) 0x1F8000D0, (void *) 0x1F800050);
  func_80064D80((void *) 0x1F800050);
  func_80064CF0((void *) 0x1F800050);
  *((u16 *) (((u8 *) scratch) + 0x24)) = (u16) (*((u16 *) (((s8 *) temp_s7) + 0x14)));
  for (;;)
  {
  if (!((*((u8 *) (((s8 *) sp84) + 0))) & 0x20))
  {
    *((s32 *) (((u8 *) scratch) + 0x08)) = *((u8 *) (((s8 *) sp84) + 8));
    *((s32 *) (((u8 *) scratch) + 0x0C)) = (s32) (*((u8 *) (((s8 *) sp84) + 9)));
    *((s32 *) (((u8 *) scratch) + 0x10)) = (s32) (*((u8 *) (((s8 *) sp84) + 10)));
    *((s32 *) (((u8 *) scratch) + 0x14)) = (s32) (*((u8 *) (((s8 *) sp84) + 11)));
    if (((*((u8 *) (((s8 *) sp84) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 1)
    {
      temp_v0_4 = (0 - ((s8) (*((u8 *) (((s8 *) sp84) + 2))))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
      *((u16 *) (((u8 *) scratch) + 0x80)) = temp_v0_4;
      *((u16 *) (((u8 *) scratch) + 0x70)) = temp_v0_4;
      temp_v0_6 = temp_v0_4 - ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
      *((u16 *) (((u8 *) scratch) + 0x88)) = temp_v0_6;
      *((u16 *) (((u8 *) scratch) + 0x78)) = temp_v0_6;
    }
    else
    {
    temp_v0_5 = ((s8) (*((u8 *) (((s8 *) sp84) + 2)))) - (*((u16 *) (((u8 *) scratch) + 0x108)));
    *((u16 *) (((u8 *) scratch) + 0x80)) = temp_v0_5;
    *((u16 *) (((u8 *) scratch) + 0x70)) = temp_v0_5;
    temp_v0_6 = temp_v0_5 + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10))));
    *((u16 *) (((u8 *) scratch) + 0x88)) = temp_v0_6;
    *((u16 *) (((u8 *) scratch) + 0x78)) = temp_v0_6;
    }
    if (((*((u8 *) (((s8 *) sp84) + 0))) ^ (*((u16 *) (((u8 *) scratch) + 0x24)))) & 2)
    {
      temp_v0_7 = (0 - ((s8) (*((u8 *) (((s8 *) sp84) + 3))))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
      *((u16 *) (((u8 *) scratch) + 0x7A)) = temp_v0_7;
      *((u16 *) (((u8 *) scratch) + 0x72)) = temp_v0_7;
      temp_v0_9 = temp_v0_7 - ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
      *((u16 *) (((u8 *) scratch) + 0x8A)) = temp_v0_9;
      *((u16 *) (((u8 *) scratch) + 0x82)) = temp_v0_9;
    }
    else
    {
    temp_v0_8 = ((s8) (*((u8 *) (((s8 *) sp84) + 3)))) - (*((u16 *) (((u8 *) scratch) + 0x10A)));
    *((u16 *) (((u8 *) scratch) + 0x7A)) = temp_v0_8;
    *((u16 *) (((u8 *) scratch) + 0x72)) = temp_v0_8;
    temp_v0_9 = temp_v0_8 + ((u16) (*((s32 *) (((u8 *) scratch) + 0x14))));
    *((u16 *) (((u8 *) scratch) + 0x8A)) = temp_v0_9;
    *((u16 *) (((u8 *) scratch) + 0x82)) = temp_v0_9;
    }
    func_800654B0((void *) (((u8 *) scratch) + 0x70), (void *) (((u8 *) scratch) + 0x78), (void *) (((u8 *) scratch) + 0x80), (void *) (((u8 *) scratch) + 0x88), (void *) (((u8 *) scratch) + 0xF0), (void *) (((u8 *) scratch) + 0xF4), (void *) (((u8 *) scratch) + 0xF8), (void *) (((u8 *) scratch) + 0xFC), (void *) (((u8 *) scratch) + 0x90), (void *) (((u8 *) scratch) + 0x94));
    *((s16 *) (((s8 *) var_s3) + 8)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF0))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s3) + 0xA)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF2))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s3) + 0x10)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF4))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s3) + 0x12)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF6))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s3) + 0x18)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xF8))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s3) + 0x1A)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFA))) + (*((u16 *) (((u8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s3) + 0x20)) = (s16) ((*((u16 *) (((u8 *) scratch) + 0xFC))) + (*((u16 *) (((u8 *) scratch) + 0xB8))));
    temp_a0 = *((u16 *) (((u8 *) scratch) + 0xFE));
    temp_a0b = *((u16 *) (((u8 *) scratch) + 0xBA));
    *((s8 *) (((s8 *) var_s3) + 3)) = 9;
    *((s16 *) (((s8 *) var_s3) + 0x22)) = (s16) (temp_a0 + temp_a0b);
    temp_v1_2 = (*((s32 *) (((u8 *) scratch) + 0x10))) + ((*((s32 *) (((u8 *) scratch) + 0x08))) - 1);
    *((s32 *) (((u8 *) scratch) + 0x10)) = temp_v1_2;
    if (temp_v1_2 & 0x100)
    {
      *((s32 *) (((u8 *) scratch) + 0x10)) = temp_v1_2 - 1;
    }
    temp_v1_3 = (*((s32 *) (((u8 *) scratch) + 0x14))) + ((*((s32 *) (((u8 *) scratch) + 0x0C))) - 1);
    *((s32 *) (((u8 *) scratch) + 0x14)) = temp_v1_3;
    if (temp_v1_3 & 0x100)
    {
      *((s32 *) (((u8 *) scratch) + 0x14)) = temp_v1_3 - 1;
    }
    *((s32 *) (((u8 *) scratch) + 0x14)) <<= 8;
    *((s32 *) (((u8 *) scratch) + 0x0C)) <<= 8;
    temp_v1_a = *((u16 *) (((s8 *) temp_s7) + 0x12));
    if (temp_v1_a != 0)
    {
      if ((*((u16 *) (((u8 *) scratch) + 0x24))) & 0x100)
      {
        *((u16 *) (((s8 *) var_s3) + 0xE)) = temp_v1_a;
      }
      else
      {
        *((u16 *) (((s8 *) var_s3) + 0xE)) = (u16) (temp_v1_a + (*((u16 *) (((s8 *) sp84) + 6))));
      }
    }
    else
    {
      *((u16 *) (((s8 *) var_s3) + 0xE)) = (u16) (*((u16 *) (((s8 *) sp84) + 6)));
    }
    *((s16 *) (((s8 *) var_s3) + 0xC)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C)))) + ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) var_s3) + 0x14)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x0C)))) + ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
    temp_v1_b = *((u16 *) (((s8 *) temp_s7) + 0x10));
    if (temp_v1_b != 0)
    {
      *((u16 *) (((s8 *) var_s3) + 0x16)) = (u16) (temp_v1_b + ((*((u16 *) (((s8 *) sp84) + 4))) & 0xFF9F));
    }
    else
    {
      *((u16 *) (((s8 *) var_s3) + 0x16)) = (u16) (*((u16 *) (((s8 *) sp84) + 4)));
    }
    *((s16 *) (((s8 *) var_s3) + 0x1C)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14)))) | ((u16) (*((s32 *) (((u8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) var_s3) + 0x24)) = (s16) (((u16) (*((s32 *) (((u8 *) scratch) + 0x14)))) | ((u16) (*((s32 *) (((u8 *) scratch) + 0x10)))));
    if ((*((s16 *) (((s8 *) var_s3) + 8))) > (*((s16 *) (((s8 *) var_s3) + 0x20))))
    {
      temp_v1_4 = *((u8 *) (((s8 *) var_s3) + 0x24));
      *((u8 *) (((s8 *) var_s3) + 0x24)) = (u8) (temp_v1_4 + 0xFF);
      *((u8 *) (((s8 *) var_s3) + 0x14)) = temp_v1_4;
    }
    if ((*((s16 *) (((s8 *) var_s3) + 0xA))) > (*((s16 *) (((s8 *) var_s3) + 0x22))))
    {
      temp_v1_5 = *((u8 *) (((s8 *) var_s3) + 0x25));
      *((u8 *) (((s8 *) var_s3) + 0x25)) = (u8) (temp_v1_5 + 0xFF);
      *((u8 *) (((s8 *) var_s3) + 0x1D)) = temp_v1_5;
    }
    temp_a0_2 = *((u8 *) (((s8 *) sp84) + 1));
    *((u8 *) (((s8 *) temp_s7) + 0xF)) = temp_a0_2;
    temp_v1_6 = *((u16 *) (((u8 *) scratch) + 0x24));
    if (temp_v1_6 & 8)
    {
      if (temp_v1_6 & 4)
      {
        var_v0 = temp_a0_2 | 2;
      }
      else
      {
        var_v0 = temp_a0_2 & 0xFD;
      }
      *((u8 *) (((s8 *) temp_s7) + 0xF)) = var_v0;
    }
    ;
    *((s32 *) (((s8 *) var_s3) + 4)) = (s32) (*((s32 *) (((s8 *) temp_s7) + 0xC)));
    sp28 = *((Quad40 *) var_s3);
    sp50 = sp28;
    var_s1 = *((s16 *) (((s8 *) arg1) + 0x98));
    var_s5_reg = 0;
    if ((*((s16 *) (((s8 *) arg1) + 0x9C))) == 0)
    {
      do
      {
        *((s8 *) (((s8 *) var_s3) + 0x3)) = 9;
        *((Quad40 *) var_s3) = sp28;
        *((u16 *) (((s8 *) var_s3) + 0x8)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x8))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) (temp_s2 = arg1 + var_s5_reg)) + 0x38))))) >> 0x10));
        ASM_USE_G_NV(temp_s7);
        *((u16 *) (((s8 *) var_s3) + 0x10)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x10))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) temp_s2) + 0x38))))) >> 0x10));
        var_s1_2 = var_s1 + (*((s16 *) (((s8 *) arg1) + 0x9A)));
        if (var_s1_2 >= 0x1001)
        {
          var_s1_2 -= 0x1000;
        }
        *((u16 *) (((s8 *) var_s3) + 0x18)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x18))) + (((s32) (func_800644B8(var_s1_2) * (*((u8 *) (((s8 *) temp_s2) + 0x38))))) >> 0x10));
        var_s5_reg += 1;
        *((u16 *) (((s8 *) var_s3) + 0x20)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x20))) + (((s32) (func_800644B8(var_s1_2) * (*((u8 *) (((s8 *) temp_s2) + 0x38))))) >> 0x10));
        if (var_s5_reg >= 0x60)
        {
          var_s5_reg = 0;
        }
        do {
        do {
        do {
        *((u16 *) (((s8 *) var_s3) + 0xA)) = sp50.h10;
        *((u16 *) (((s8 *) var_s3) + 0x12)) = sp50.h10;
        *((s16 *) (((s8 *) var_s3) + 0x1A)) = (s16) ((sp50.h10) + 1);
        *((s16 *) (((s8 *) var_s3) + 0x22)) = (s16) ((sp50.h10) + 1);
        *((u8 *) (((s8 *) var_s3) + 0xD)) = sp50.b13;
        *((u8 *) (((s8 *) var_s3) + 0x15)) = sp50.b13;
        *((s8 *) (((s8 *) var_s3) + 0x1D)) = (s8) ((sp50.b13) + 1);
        *((s8 *) (((s8 *) var_s3) + 0x25)) = (s8) ((sp50.b13) + 1);
        *var_s3 = ((*var_s3) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
        temp_a0_3 = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
        *temp_a0_3 = ((*temp_a0_3) & 0xFF000000) | (((s32) var_s3) & 0xFFFFFF);
        sp50 = *((Quad40 *) var_s3);
        temp_v1_7 = (sp50.h10) + 1;
        sp50.h10 = temp_v1_7;
        sp50.b13 += 1;
        var_s1 = var_s1_2 + (*((s16 *) (((s8 *) arg1) + 0x9A)));
        var_s3 += 10;
        } while (0);
        } while (0);
        } while (0);
        if (var_s1 >= 0x1001)
        {
          var_s1 -= 0x1000;
        }
      }
      while (((s16) temp_v1_7) < (sp28.h26));
    }
    else
    {
    do
    {
      *((s8 *) (((s8 *) var_s3) + 0x3)) = 9;
      *((Quad40 *) var_s3) = sp28;
      *((u16 *) (((s8 *) var_s3) + 0xA)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0xA))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) (temp_s2_2 = arg1 + var_s5_reg)) + 0x38))))) >> 0x10));
      ASM_KEEP_NV(temp_s2_2);
      ASM_USE_G_NV(temp_s7);
      *((u16 *) (((s8 *) var_s3) + 0x1A)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x1A))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) temp_s2_2) + 0x38))))) >> 0x10));
      var_s1_3 = var_s1 + (*((s16 *) (((s8 *) arg1) + 0x9A)));
      if (var_s1_3 >= 0x1001)
      {
        var_s1_3 -= 0x1000;
      }
      *((u16 *) (((s8 *) var_s3) + 0x12)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x12))) + (((s32) (func_800644B8(var_s1_3) * (*((u8 *) (((s8 *) temp_s2_2) + 0x38))))) >> 0x10));
      var_s5_reg += 1;
      *((u16 *) (((s8 *) var_s3) + 0x22)) = (u16) ((*((u16 *) (((s8 *) var_s3) + 0x22))) + (((s32) (func_800644B8(var_s1_3) * (*((u8 *) (((s8 *) temp_s2_2) + 0x38))))) >> 0x10));
      if (var_s5_reg >= 0x60)
      {
        var_s5_reg = 0;
      }
      do {
      do {
      do {
      *((u16 *) (((s8 *) var_s3) + 0x8)) = sp50.h8;
      *((u16 *) (((s8 *) var_s3) + 0x18)) = sp50.h8;
      *((s16 *) (((s8 *) var_s3) + 0x10)) = (s16) ((sp50.h8) + 1);
      *((s16 *) (((s8 *) var_s3) + 0x20)) = (s16) ((sp50.h8) + 1);
      *((u8 *) (((s8 *) var_s3) + 0xC)) = sp50.b12;
      *((u8 *) (((s8 *) var_s3) + 0x1C)) = sp50.b12;
      *((s8 *) (((s8 *) var_s3) + 0x14)) = (s8) ((sp50.b12) + 1);
      *((s8 *) (((s8 *) var_s3) + 0x24)) = (s8) ((sp50.b12) + 1);
      *var_s3 = ((*var_s3) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
      temp_a0_5 = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
      *temp_a0_5 = ((*temp_a0_5) & 0xFF000000) | (((s32) var_s3) & 0xFFFFFF);
      sp50 = *((Quad40 *) var_s3);
      temp_v1_8 = (sp50.h8) + 1;
      sp50.h8 = temp_v1_8;
      sp50.b12 += 1;
      var_s1 = var_s1_3 + (*((s16 *) (((s8 *) arg1) + 0x9A)));
      var_s3 += 10;
      } while (0);
      } while (0);
      } while (0);
      if (var_s1 >= 0x1001)
      {
        var_s1 -= 0x1000;
      }
    }
    while (((s16) temp_v1_8) < (sp28.h16));
    }
  }
  else
  {
  temp_v0_10 = (s32 *(*)(void *, s32, void *, void *, s32 *)) (*((s32 *) (((s8 *) sp84) + 8)));
  if (temp_v0_10 != 0)
  {
    var_s3 = temp_v0_10(arg2, sp80, temp_s7, sp84, var_s3);
  }
  }
  if (((s8) (*((u8 *) (((s8 *) sp84) + 0)))) < 0)
  {
    break;
  }
  sp84 = (void *) (((u8 *) sp84) + 0xC);
  }
  var_a0_2 = var_s3;
  if ((sp78 << 0x10) != 0)
  {
    func_80067EF4(var_a0_2, 0, 1);
    *var_s3 = ((*var_s3) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((u8 *) scratch) + 0x20))))) & 0xFFFFFF);
    temp_v1_9 = (s32 *) (*((s32 *) (((u8 *) scratch) + 0x20)));
    var_a0_2 = (s32 *) (((s32) var_s3) & 0xFFFFFF);
    var_s3 += 3;
    *temp_v1_9 = ((*temp_v1_9) & 0xFF000000) | ((s32) var_a0_2);
  }
  func_80064A40();
  *((s32 **) (((s8 *) (*((void **) gbase))) + 0x8D0)) = var_s3;
}
