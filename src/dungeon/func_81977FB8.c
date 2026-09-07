#include "common.h"

typedef s32 M2C_UNK;
extern u8 D_80083498[];
struct TargetVec;
extern struct TargetVec *D_80026208[];
extern u8 D_80045340[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
s32 rand();
extern M2C_UNK D_8002560C;
extern M2C_UNK D_80026180;
typedef struct TargetSub {
  u8 pad0[4];
  s16 field4;
  s16 field6;
  s16 field8;
  u16 fieldA;
} TargetSub;
typedef struct TargetVec {
  s32 field0;
  s32 field4;
  u8 pad8[2];
  u16 fieldA;
} TargetVec;
typedef struct TargetData {
  u8 pad0[0xC];
  u8 byteC;
  u8 byteD;
  u8 byteE;
  u8 padF;
  u16 field10;
  u8 pad12[2];
  u16 field14;
  u8 pad16[6];
  u16 field1C;
  u16 field1E;
} TargetData;
typedef struct TargetObj {
  u8 pad0[8];
  TargetVec *field8;
  TargetData *fieldC;
  void *field10;
  u8 pad14[0xC];
  TargetSub sub;
} TargetObj;
void func_81977FB8(void)
{
  s32 temp_lo;
  s32 temp_v0_2;
  s32 temp_v0_3;
  s32 temp_v0_4;
  s32 temp_remainder;
  s32 var_v0;
  s32 var_v0_2;
  TargetSub *temp_s2;
  TargetObj *temp_v0;
  temp_v0 = func_8003FD64(0x212, D_80083498);
  if (temp_v0 != 0)
  {
    temp_s2 = &temp_v0->sub;
    temp_v0->field10 = &D_8002560C;
    temp_s2->field4 = 0;
    temp_s2->field6 = 0x20;
    temp_v0_2 = rand();
    var_v0 = temp_v0_2;
    if (temp_v0_2 < 0)
    {
      var_v0 += 0xFFF;
    }
    var_v0 >>= 0xC;
    temp_s2->field8 = (s16) (temp_v0_2 - (var_v0 << 0xC));
    temp_v0_3 = rand();
    var_v0_2 = temp_v0_3;
    if (temp_v0_3 < 0)
    {
      var_v0_2 += 0x1F;
    }
    var_v0_2 >>= 5;
    temp_remainder = (var_v0_2 << 5) - temp_v0_3;
    {
      TargetData *temp_s0;
      void *temp_arg1;
      temp_arg1 = &D_80026180;
      ASM_KEEP(temp_arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
      temp_s2->fieldA = (u16) temp_remainder;
      temp_s0 = temp_v0->fieldC;
      temp_s0->byteE = (temp_remainder = 0x80);
      temp_s0->byteD = temp_remainder;
      temp_s0->byteC = temp_remainder;
      func_8003DB94(temp_s0, temp_arg1, 0);
      temp_s0->field1E = 0x200;
      temp_s0->field1C = 0x200;
      temp_s0->field14 = (u16) (temp_s0->field14 | 0xC);
      temp_s0->field10 = (u16) (temp_s0->field10 | 0x20);
    }
    {
      TargetVec *temp_s0_2;
      TargetVec *temp_a2;
      s32 temp_base;
      temp_s0_2 = temp_v0->field8;
      temp_lo = (func_800644B8(temp_s2->field8) >> 4) * temp_s2->field6;
      temp_s0_2->field0 = D_80026208[0]->field0 + (temp_lo << 8);
      temp_v0_4 = func_80064584(temp_s2->field8);
      temp_lo = (temp_v0_4 >> 4) * temp_s2->field6;
      temp_a2 = D_80026208[0];
      temp_base = temp_a2->field4;
      temp_s0_2->field4 = temp_base + (temp_lo << 8);
      temp_s0_2->fieldA = (s16) (temp_a2->fieldA + temp_s2->fieldA);
      func_8004491C(temp_v0, D_80045340, temp_a2, temp_lo);
    }
  }
}

/* MECHANISM: pure scheduler rotation.  Retail materialises the `&D_80026180`
   lui/addiu pair BEFORE the `sh v0,0xA(s2)` remainder store; gcc-2.8.1 sinks the
   address pair past both the store and the `li v0,0x80`.  Hoisting the
   assignment alone is not enough (the scheduler re-sinks it) -- the VOLATILE
   ASM_KEEP on the address temp is the anchor that pins it in place.  The
   non-volatile ASM_KEEP_NV spelling regresses straight back to aligned 4, and a
   $a1 register pin is unnecessary: gcc already colours the temp a1. */
