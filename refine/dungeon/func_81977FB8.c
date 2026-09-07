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
/* Creates an object at a random angle and height offset around the reference position. */
void func_81977FB8(void)
{
  s32 axis_offset;
  s32 angle_random;
  s32 height_random;
  s32 axis_factor;
  s32 height_or_shade;
  s32 angle_quotient;
  s32 height_quotient;
  TargetSub *motion;
  TargetObj *obj;
  obj = func_8003FD64(0x212, D_80083498);
  if (obj != 0)
  {
    motion = &obj->sub;
    obj->field10 = &D_8002560C;
    motion->field4 = 0;
    motion->field6 = 0x20;
    angle_random = rand();
    angle_quotient = angle_random;
    if (angle_random < 0)
    {
      angle_quotient += 0xFFF;
    }
    angle_quotient >>= 0xC;
    motion->field8 = (s16) (angle_random - (angle_quotient << 0xC));
    height_random = rand();
    height_quotient = height_random;
    if (height_random < 0)
    {
      height_quotient += 0x1F;
    }
    height_quotient >>= 5;
    height_or_shade = (height_quotient << 5) - height_random;
    {
      TargetData *render_data;
      void *render_config;
      render_config = &D_80026180;
      ASM_KEEP(render_config);   /* MATCH pin: retail schedule: same instructions, different order without it */
      motion->fieldA = (u16) height_or_shade;
      render_data = obj->fieldC;
      render_data->byteE = (height_or_shade = 0x80);
      render_data->byteD = height_or_shade;
      render_data->byteC = height_or_shade;
      func_8003DB94(render_data, render_config, 0);
      render_data->field1E = 0x200;
      render_data->field1C = 0x200;
      render_data->field14 = (u16) (render_data->field14 | 0xC);
      render_data->field10 = (u16) (render_data->field10 | 0x20);
    }
    {
      TargetVec *position;
      TargetVec *origin;
      s32 origin_y;
      position = obj->field8;
      axis_offset = (func_800644B8(motion->field8) >> 4) * motion->field6;
      position->field0 = D_80026208[0]->field0 + (axis_offset << 8);
      axis_factor = func_80064584(motion->field8);
      axis_offset = (axis_factor >> 4) * motion->field6;
      origin = D_80026208[0];
      origin_y = origin->field4;
      position->field4 = origin_y + (axis_offset << 8);
      position->fieldA = (s16) (origin->fieldA + motion->fieldA);
      func_8004491C(obj, D_80045340, origin, axis_offset);
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
