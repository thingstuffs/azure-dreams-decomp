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
#define SP5A (*(volatile u16 *)((s8 *)(sp28) + 50))
#define SP5D M2C_FIELD(sp28, u8 *, 53)

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

void func_818EC800(void *arg0, void *arg1, s32 *arg2, u32 arg3)
{
  s32 saved_reg_s4;
  s32 unkspB4;
  s32 sp42;
  s32 spB4;
  M2C_UNK sp28[20];
  u16 sp78;
  s32 sp80;
  s32 *sp84;
  s32 sp88;
  s32 *var_a2_2;
  s32 *var_a2_3;
  s32 *var_a3;
  s32 *var_a3_2;
  s32 *var_a3_4;
  M2C_UNK var_a1;
  u8 *pg;
  u8 *p6c;
  s32 tail_v0;
  void *var_pg0;
  register u8 *pgcolor ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
  void *var_pg1;
  s32 temp_base18;
  s32 himask;
  u8 bt1;
  u8 bt2;
  u8 bt3;
  u8 bt4;
  s32 temp_f12;
  s32 temp_f10;
  s32 temp_v0_3;
  s32 temp_v0_4;
  s32 temp_v0_5;
  s32 temp_v0_6;
  s32 temp_v0_7;
  s32 temp_v0_8;
  s32 var_s1;
  u8 *(*temp_v0_9)(void *, s32, void *, void *, u8 *);
  s32 *temp_a0_3;
  s32 *temp_v1;
  s32 *temp_v1_8;
  u8 *var_a0_2;
  s32 *var_a2;
  s32 *var_a2_4;
  s32 *var_a3_3;
  u8 *var_s4;
  s32 temp_a0_4;
  s32 temp_a1;
  s32 temp_a1_2;
  s32 temp_v1_2;
  s32 temp_dec1;
  s32 temp_dec2;
  s32 temp_v1_3;
  s32 copy_w0;
  s32 copy_w1;
  s32 copy_w2;
  s32 copy_w3;
  s32 temp_axis0;
  s32 temp_axis1;
  s32 temp_axis2;
  s32 var_s6;
  u16 temp_a0;
  u16 temp_fe;
  u16 temp_v0;
  u16 temp_v0_2;
  u16 temp_v1_6;
  u16 temp_v1_7;
  u8 temp_a0_2;
  u8 temp_v1_4;
  u8 temp_v1_5;
  u8 var_v0;
  s32 cmp8;
  register u8 *scratch ASM_REG("$19");   /* MATCH pin: retail immediate-load split depends on it */
  void *temp_fp;
  void *temp_s2;
  register u8 *temp_s5 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
  void *temp_s7;
  void *var_a0;
  u8 *pgt;
  u8 *pgb;
  s32 hz;
  var_a0 = arg0;
  ASM_KEEP_MEMDEP_NV(var_a0, pgcolor, *((void **) (&D_80083160)));   /* MATCH pin: load-bearing for the whole function shape */
  (*((s8 *) 0x530C)) + saved_reg_s4;
  0;
  0;
  unkspB4 = 0;
  temp_s7 = *((void **) (((s8 *) arg1) + (-0x14)));
  sp80 = *((s32 *) (((s8 *) arg1) + (-0x18)));
  var_pg0 = *((void **) (&D_80083160));
  temp_fp = *((void **) (((s8 *) temp_s7) + 8));
  scratch = (u8 *) 0x1F800000;
  ASM_KEEP(scratch);   /* MATCH pin: retail immediate-load split depends on it */
  *((s32 *) (((s8 *) scratch) + 0xEC)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x8C)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x84)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x7C)) = 0;
  *((u16 *) (((s8 *) scratch) + 0x74)) = 0;
  var_s4 = *((u8 **) (((s8 *) var_pg0) + 0x8D0));
  *((s32 *) (((s8 *) scratch) + 0x20)) = (s32) arg2;
  *((s32 *) (((s8 *) scratch) + 0xC0)) = 0;
  *((u16 *) (((s8 *) scratch) + 0xB8)) = (u16) ((*((u16 *) (((s8 *) var_a0) + 0))) - 0xA0);
  *((u16 *) (((s8 *) scratch) + 0xBA)) = (u16) ((*((u16 *) (((s8 *) var_a0) + 2))) - 0x78);
  ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
  sp78 = (u16) arg3;
  arg3 = ((u32) arg3) << 0x10;
  var_a1 = 0;
  if (arg3 != 0)
  {
    func_80067EF4(var_s4, var_a1, var_a1, arg3);
    himask = 0xFFFFFF;
    var_a1 = 0xFF000000;
    *((s32 *) var_s4) = ((*((s32 *) var_s4)) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & himask);
    temp_v1 = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
    var_a0 = (void *) (((s32) var_s4) & himask);
    var_s4 += 0xC;
    *temp_v1 = ((*temp_v1) & 0xFF000000) | ((s32) var_a0);
  }
  sp84 = &sp28[8];
  ASM_KEEP_NV(sp84);   /* MATCH pin: retail schedule: same instructions, different order without it */
  sp88 = 0xFFFFFF;
  ASM_KEEP_NV(sp88);   /* MATCH pin: retail immediate-load split depends on it */
  p6c = (u8 *) (&D_8006CD10);
  pg = (u8 *) (&D_80083160);
  *((s32 *) (((s8 *) p6c) + 0x1C)) = (s32) (*((s32 *) (((s8 *) pg) + 0xA0)));
  func_800649A0((s32) var_a0, var_a1);
  pg = (u8 *) (&D_80083160);
  temp_axis0 = *((s16 *) (((s8 *) pg) + 0xC4));
  temp_axis1 = *((s16 *) (((s8 *) pg) + 0xC6));
  temp_axis2 = *((s16 *) (((s8 *) pg) + 0xC8));
  *((s32 *) (((s8 *) scratch) + 0x30)) = temp_axis0;
  *((s32 *) (((s8 *) scratch) + 0x34)) = temp_axis1;
  *((s32 *) (((s8 *) scratch) + 0x38)) = temp_axis2;
  *((u16 *) (((s8 *) scratch) + 0x100)) = (u16) (*((u16 *) (((s8 *) temp_s7) + 0x16)));
  *((u16 *) (((s8 *) scratch) + 0x104)) = (s16) ((*((u16 *) (((s8 *) temp_s7) + 0x1A))) - (*((u16 *) (((s8 *) scratch) + 0x34))));
  temp_base18 = *((u16 *) (((s8 *) temp_s7) + 0x18));
  *((u16 *) (((s8 *) scratch) + 0x102)) = (s16) (((((*((u16 *) (((s8 *) scratch) + 0x38))) + 0x100) & 0x1FF) - 0x100) + temp_base18);
  temp_v0 = *((u16 *) (((s8 *) temp_s7) + 0x20));
  *((s32 *) (((s8 *) scratch) + 0xE4)) = temp_v0;
  *((u16 *) (((s8 *) scratch) + 0x108)) = temp_v0;
  temp_v0_2 = *((u16 *) (((s8 *) temp_s7) + 0x22));
  *((s32 *) (((s8 *) scratch) + 0xE8)) = temp_v0_2;
  *((u16 *) (((s8 *) scratch) + 0x10A)) = temp_v0_2;
  func_80065820(0x1F800100, 0x1F8000D0);
  *((s32 *) (((s8 *) scratch) + 0x30)) = (s32) (*((u16 *) (((s8 *) temp_s7) + 0x1C)));
  *((s32 *) (((s8 *) scratch) + 0x34)) = (s32) (*((u16 *) (((s8 *) temp_s7) + 0x1E)));
  *((s32 *) (((s8 *) scratch) + 0x38)) = 0x1000;
  func_80064BC0(0x1F8000D0, 0x1F800030);
  func_80064840(p6c, 0x1F8000D0, 0x1F800050);
  func_80064D80(0x1F800050);
  func_80064CF0(0x1F800050);
  *((u16 *) (((s8 *) scratch) + 0x24)) = (u16) (*((u16 *) (((s8 *) temp_s7) + 0x14)));
  temp_s5 = temp_fp + 8;
  ASM_KEEP(temp_s5);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  if (!((*((u8 *) (((s8 *) temp_fp) + 0))) & 0x20))
  {
    *((s32 *) (((s8 *) scratch) + 0x08)) = (s32) (*((u8 *) (((s8 *) temp_s5) + 0)));
    *((s32 *) (((s8 *) scratch) + 0x0C)) = (s32) (*((u8 *) (((s8 *) temp_s5) + 1)));
    *((s32 *) (((s8 *) scratch) + 0x10)) = (s32) (*((u8 *) (((s8 *) temp_s5) + 2)));
    *((s32 *) (((s8 *) scratch) + 0x14)) = (s32) (*((u8 *) (((s8 *) temp_s5) + 3)));
    if (((*((u8 *) (((s8 *) temp_fp) + 0))) ^ (*((u16 *) (((s8 *) scratch) + 0x24)))) & 1)
    {
      bt1 = *((volatile u8 *) (((s8 *) temp_s5) + (-6)));
      temp_v0_3 = (0 - ((s8) bt1)) - (*((u16 *) (((s8 *) scratch) + 0x108)));
      *((u16 *) (((s8 *) scratch) + 0x80)) = temp_v0_3;
      *((u16 *) (((s8 *) scratch) + 0x70)) = temp_v0_3;
      temp_v0_3 = temp_v0_3 - (*((u16 *) (((s8 *) scratch) + 0x10)));
      ASM_TAILSLOT_PIN_TIED(temp_v0_3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
      func_80024344();
    }
    bt2 = *((volatile u8 *) (((s8 *) temp_s5) + (-6)));
    temp_v0_4 = ((s8) bt2) - (*((u16 *) (((s8 *) scratch) + 0x108)));
    *((u16 *) (((s8 *) scratch) + 0x80)) = temp_v0_4;
    *((u16 *) (((s8 *) scratch) + 0x70)) = temp_v0_4;
    temp_v0_4 = temp_v0_4 + (*((u16 *) (((s8 *) scratch) + 0x10)));
    *((u16 *) (((s8 *) scratch) + 0x88)) = temp_v0_4;
    *((u16 *) (((s8 *) scratch) + 0x78)) = temp_v0_4;
    if (((*((u8 *) (((s8 *) temp_fp) + 0))) ^ (*((u16 *) (((s8 *) scratch) + 0x24)))) & 2)
    {
      bt3 = *((volatile u8 *) (((s8 *) temp_s5) + (-5)));
      temp_v0_6 = (0 - ((s8) bt3)) - (*((u16 *) (((s8 *) scratch) + 0x10A)));
      *((u16 *) (((s8 *) scratch) + 0x7A)) = temp_v0_6;
      *((u16 *) (((s8 *) scratch) + 0x72)) = temp_v0_6;
      temp_v0_6 = temp_v0_6 - (*((u16 *) (((s8 *) scratch) + 0x14)));
      ASM_TAILSLOT_PIN_TIED(temp_v0_6);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
      func_800243B8();
    }
    bt4 = *((volatile u8 *) (((s8 *) temp_s5) + (-5)));
    temp_v0_7 = ((s8) bt4) - (*((u16 *) (((s8 *) scratch) + 0x10A)));
    *((u16 *) (((s8 *) scratch) + 0x7A)) = temp_v0_7;
    *((u16 *) (((s8 *) scratch) + 0x72)) = temp_v0_7;
    temp_v0_7 = temp_v0_7 + (*((u16 *) (((s8 *) scratch) + 0x14)));
    *((u16 *) (((s8 *) scratch) + 0x8A)) = temp_v0_7;
    *((u16 *) (((s8 *) scratch) + 0x82)) = temp_v0_7;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_800654B0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88, scratch + 0xF0, scratch + 0xF4, scratch + 0xF8, scratch + 0xFC, scratch + 0x90, scratch + 0x94);
    *((s16 *) (((s8 *) var_s4) + 8)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF0))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s4) + 0xA)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF2))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s4) + 0x10)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF4))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s4) + 0x12)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF6))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s4) + 0x18)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xF8))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    *((s16 *) (((s8 *) var_s4) + 0x1A)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xFA))) + (*((u16 *) (((s8 *) scratch) + 0xBA))));
    *((s16 *) (((s8 *) var_s4) + 0x20)) = (s16) ((*((u16 *) (((s8 *) scratch) + 0xFC))) + (*((u16 *) (((s8 *) scratch) + 0xB8))));
    temp_fe = *((u16 *) (((s8 *) scratch) + 0xFE));
    temp_a0 = *((u16 *) (((s8 *) scratch) + 0xBA));
    *((s8 *) (((s8 *) var_s4) + 3)) = 9;
    *((s16 *) (((s8 *) var_s4) + 0x22)) = (s16) (temp_fe + temp_a0);
    temp_dec1 = (*((s32 *) (((s8 *) scratch) + 0x10))) - 1;
    temp_v1_2 = temp_dec1 + (*((s32 *) (((s8 *) scratch) + 0x08)));
    *((s32 *) (((s8 *) scratch) + 0x10)) = temp_v1_2;
    if (temp_v1_2 & 0x100)
    {
      *((s32 *) (((s8 *) scratch) + 0x10)) = temp_v1_2 - 1;
    }
    temp_dec2 = (*((s32 *) (((s8 *) scratch) + 0x14))) - 1;
    temp_v1_3 = temp_dec2 + (*((s32 *) (((s8 *) scratch) + 0x0C)));
    *((s32 *) (((s8 *) scratch) + 0x14)) = temp_v1_3;
    if (temp_v1_3 & 0x100)
    {
      *((s32 *) (((s8 *) scratch) + 0x14)) = temp_v1_3 - 1;
    }
    *((s32 *) (((s8 *) scratch) + 0x14)) <<= 8;
    *((s32 *) (((s8 *) scratch) + 0x0C)) <<= 8;
    temp_f12 = *((u16 *) (((s8 *) temp_s7) + 0x12));
    if (temp_f12 != 0)
    {
      if ((*((u16 *) (((s8 *) scratch) + 0x24))) & 0x100)
      {
        *((u16 *) (((s8 *) var_s4) + 0xE)) = (u16) temp_f12;
        func_8002454C();
      }
      tail_v0 = temp_f12 + (*((u16 *) (((s8 *) temp_s5) + (-2))));
      ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail delay-slot fill depends on it */
      func_80024544();
    }
    *((u16 *) (((s8 *) var_s4) + 0xE)) = (u16) (*((u16 *) (((s8 *) temp_s5) + (-2))));
    *((s16 *) (((s8 *) var_s4) + 0xC)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x0C)))) + ((u16) (*((u16 *) (((s8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) var_s4) + 0x14)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x0C)))) + ((u16) (*((u16 *) (((s8 *) scratch) + 0x10)))));
    temp_f10 = *((u16 *) (((s8 *) temp_s7) + 0x10));
    if (temp_f10 != 0)
    {
      tail_v0 = temp_f10 + ((*((u16 *) (((s8 *) temp_s5) + (-4)))) & 0xFF9F);
      ASM_TAILSLOT_PIN_TIED(tail_v0);   /* MATCH pin: retail delay-slot fill depends on it */
      func_8002459C();
    }
    *((u16 *) (((s8 *) var_s4) + 0x16)) = (u16) (*((u16 *) (((s8 *) temp_s5) + (-4))));
    *((s16 *) (((s8 *) var_s4) + 0x1C)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x14)))) | ((u16) (*((u16 *) (((s8 *) scratch) + 0x08)))));
    *((s16 *) (((s8 *) var_s4) + 0x24)) = (s16) (((u16) (*((u16 *) (((s8 *) scratch) + 0x14)))) | ((u16) (*((u16 *) (((s8 *) scratch) + 0x10)))));
    cmp8 = *((s16 *) (((s8 *) var_s4) + 8));
    if ((*((s16 *) (((s8 *) var_s4) + 0x20))) < cmp8)
    {
      temp_v1_4 = *((u8 *) (((s8 *) var_s4) + 0x24));
      *((u8 *) (((s8 *) var_s4) + 0x24)) = (u8) (temp_v1_4 + 0xFF);
      *((u8 *) (((s8 *) var_s4) + 0x14)) = temp_v1_4;
    }
    temp_v1_2 = *((s16 *) (((s8 *) var_s4) + 0xA));
    if ((*((s16 *) (((s8 *) var_s4) + 0x22))) < temp_v1_2)
    {
      temp_v1_5 = *((u8 *) (((s8 *) var_s4) + 0x25));
      *((u8 *) (((s8 *) var_s4) + 0x25)) = (u8) (temp_v1_5 + 0xFF);
      *((u8 *) (((s8 *) var_s4) + 0x1D)) = temp_v1_5;
    }
    temp_a0_2 = *((u8 *) (((s8 *) temp_s5) + (-7)));
    *((u8 *) (((s8 *) temp_s7) + 0xF)) = temp_a0_2;
    temp_v1_6 = *((u16 *) (((s8 *) scratch) + 0x24));
    ASM_KEEP_NV(temp_v1_6);   /* MATCH pin: retail register colouring depends on it */
    if (temp_v1_6 & 8)
    {
      if (temp_v1_6 & 4)
      {
        *((u8 *) (((s8 *) temp_s7) + 0xF)) = temp_a0_2 | 2;
      }
      else
      {
        *((u8 *) (((s8 *) temp_s7) + 0xF)) = temp_a0_2 & 0xFD;
      }
    }
    *((s32 *) (((s8 *) var_s4) + 4)) = (s32) (*((s32 *) (((s8 *) temp_s7) + 0xC)));
    *((Blk40 *) sp28) = *((Blk40 *) var_s4);
    {
      Blk16 *dst16 = (Blk16 *) (&sp28[10]);
      Blk16 *src16 = (Blk16 *) sp28;
      do
      {
        *(dst16++) = *(src16++);
      }
      while (((s32 *) src16) != sp84);
      *((Blk8 *) dst16) = *((Blk8 *) src16);
    }
    var_s6 = 0;
    ASM_KEEP(var_s6);   /* MATCH pin: retail immediate-load split depends on it */
    var_s1 = *((s16 *) (((s8 *) arg1) + 0x8C));
    do
    {
      *((s8 *) (((s8 *) var_s4) + 0x3)) = 9;
      {
        Blk16 *dst16b = (Blk16 *) var_s4;
        Blk16 *src16b = (Blk16 *) sp28;
        do
        {
          *(dst16b++) = *(src16b++);
        }
        while (((s32 *) src16b) != sp84);
        *((Blk8 *) dst16b) = *((Blk8 *) src16b);
      }
      temp_a1 = func_800644B8(var_s1);
      temp_s2 = arg1 + var_s6;
      *((u16 *) (((s8 *) var_s4) + 0x8)) = (u16) ((*((u16 *) (((s8 *) var_s4) + 0x8))) + (((s32) (temp_a1 * (*((u8 *) (((s8 *) temp_s2) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) var_s4) + 0x10)) = (u16) ((*((u16 *) (((s8 *) var_s4) + 0x10))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) temp_s2) + 0x50))))) >> 0x10));
      var_s1 = var_s1 + (*((s16 *) (((s8 *) arg1) + 0x8E)));
      if (var_s1 >= 0x1001)
      {
        var_s1 -= 0x1000;
      }
      *((u16 *) (((s8 *) var_s4) + 0x18)) = (u16) ((*((u16 *) (((s8 *) var_s4) + 0x18))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) temp_s2) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) var_s4) + 0x20)) = (u16) ((*((u16 *) (((s8 *) var_s4) + 0x20))) + (((s32) (func_800644B8(var_s1) * (*((u8 *) (((s8 *) temp_s2) + 0x50))))) >> 0x10));
      *((u16 *) (((s8 *) var_s4) + 0xA)) = *((volatile u16 *) (((s8 *) sp28) + 50));
      *((u16 *) (((s8 *) var_s4) + 0x12)) = *((volatile u16 *) (((s8 *) sp28) + 50));
      *((s16 *) (((s8 *) var_s4) + 0x1A)) = (s16) ((*((volatile u16 *) (((s8 *) sp28) + 50))) + 1);
      *((s16 *) (((s8 *) var_s4) + 0x22)) = (s16) ((*((volatile u16 *) (((s8 *) sp28) + 50))) + 1);
      *((u8 *) (((s8 *) var_s4) + 0xD)) = *((u8 *) (((s8 *) sp28) + 53));
      *((u8 *) (((s8 *) var_s4) + 0x15)) = *((u8 *) (((s8 *) sp28) + 53));
      var_s6 += 1;
      *((s8 *) (((s8 *) var_s4) + 0x1D)) = (s8) ((*((u8 *) (((s8 *) sp28) + 53))) + 1);
      *((s8 *) (((s8 *) var_s4) + 0x25)) = (s8) ((*((u8 *) (((s8 *) sp28) + 53))) + 1);
      {
        s32 hiA = (*((s32 *) var_s4)) & 0xFF000000;
        s32 rA = hiA | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & sp88);
        ASM_KEEP_NV(rA);   /* MATCH pin: retail register colouring depends on it */
        *((s32 *) var_s4) = rA;
      }
      temp_a0_3 = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
      {
        s32 rB = ((*temp_a0_3) & 0xFF000000) | (((s32) var_s4) & sp88);
        ASM_KEEP_NV(rB);   /* MATCH pin: retail register colouring depends on it */
        *temp_a0_3 = rB;
      }
      *((Blk40 *) (&sp28[10])) = *((Blk40 *) var_s4);
      temp_v1_7 = (*((volatile u16 *) (((s8 *) sp28) + 50))) + 1;
      *((volatile u16 *) (((s8 *) sp28) + 50)) = temp_v1_7;
      *((u8 *) (((s8 *) sp28) + 53)) += 1;
      var_s1 = var_s1 + (*((s16 *) (((s8 *) arg1) + 0x8E)));
      var_s4 += 0x28;
      if (var_s1 >= 0x1001)
      {
        var_s1 -= 0x1000;
      }
    }
    while (((s16) temp_v1_7) < (*((s16 *) (((s8 *) sp28) + 26))));
    ASM_USE2(temp_s7, temp_s5);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_USE_G_NV(sp80);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_USE_G_NV(sp78);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_USE(temp_fp);   /* MATCH pin: retail delay-slot fill depends on it */
    func_80024990();
    return;
  }
  temp_v0_9 = (u8 *(*)(void *, s32, void *, void *, u8 *)) (*((s32 *) (((s8 *) temp_s5) + 0)));
  if (temp_v0_9 != 0)
  {
    temp_a0_4 = sp80;
    var_s4 = temp_v0_9(arg1, temp_a0_4, temp_s7, temp_fp, var_s4);
  }
  if (((s8) (*((u8 *) (((s8 *) temp_fp) + 0)))) >= 0)
  {
    temp_s5 = temp_s5 + 0xC;
    ASM_KEEP(temp_s5);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    temp_fp = ((u8 *) temp_fp) + 0xC;
    ASM_TAILSLOT_PIN_TIED(temp_fp);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    func_80024298();
    return;
  }
  var_a0_2 = var_s4;
  if ((sp78 << 0x10) != 0)
  {
    func_80067EF4(var_a0_2, 0, 1);
    *((s32 *) var_s4) = ((*((s32 *) var_s4)) & 0xFF000000) | ((*((s32 *) (*((s32 *) (((s8 *) scratch) + 0x20))))) & 0xFFFFFF);
    temp_v1_8 = (s32 *) (*((s32 *) (((s8 *) scratch) + 0x20)));
    var_a0_2 = (u8 *) (((s32) var_s4) & 0xFFFFFF);
    var_s4 += 0xC;
    *temp_v1_8 = ((*temp_v1_8) & 0xFF000000) | ((s32) var_a0_2);
  }
  ASM_CLOBBER("$17");   /* MATCH pin: retail immediate-load split depends on it */
  ASM_CLOBBER("$18");   /* MATCH pin: retail immediate-load split depends on it */
  ASM_CLOBBER("$22");   /* MATCH pin: retail immediate-load split depends on it */
  func_80064A40((s32) var_a0_2);
  pgb = (u8 *) (&D_80083160);
  hz = (s32) ((u16) ((s32) var_s4));
  pgt = pgb + (hz & 0x10000);
  var_pg1 = *((void **) (((s8 *) pgt) + 0));
  *((s32 **) (((s8 *) var_pg1) + 0x8D0)) = var_s4;
}
