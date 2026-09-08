#include "common.h"

typedef s32 M2C_UNK;
void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_800B835C(void *, void *, s32, s32);
extern u8 D_8002744C[9];
extern u8 D_80028880[9];
extern u8 D_8002888C[9];
extern s16 D_80083228;
extern s32 D_800CEEFC[3];
void *func_80027534(s16 arg0, s16 arg1, s16 arg2)
{
  volatile struct
  {
    s32 sp10;
    s32 sp14;
    u16 sp18;
    u16 sp1A;
    u8 pad1C[4];
    u16 sp20;
    u8 pad22[6];
    s32 sp28;
  } sp;
  register s32 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  s32 temp_s1;
  s32 temp_s6;
  register s32 temp_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  s32 var_s4;
  s32 var_s5;
  register s16 held_arg1 ASM_REG("$5") = arg1;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s16 held_arg2 ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s32 init0 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  s32 init1;
  register void *init_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  register void *init_stack ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register s32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 five;
  int new_var;
  register s32 inner_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  s32 call_result;
  register void *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  void *temp_s2;
  void *temp_v0;
  sp.sp1A = held_arg2;
  init0 = 0x01800380;
  init1 = 0x400040;
  init_obj = D_8002888C;
  sp.sp18 = held_arg1;
  init_stack = (void *) (&sp.sp10);
  ASM_USE_G_NV(D_80083228);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  sp.sp10 = init0;
  sp.sp14 = init1;
  temp_s0 = (((s32) (D_80083228 + 0x500)) >> 9) & 7;
  var_s5 = 0;
  ASM_USE2_NV(init_obj, init_stack);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  {
    register u16 initial_width ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    initial_width = temp_s0 << 9;
    *((u16 *) ((void *) (&sp.sp20))) = initial_width;
  }
  func_800B835C(init_obj, init_stack, 1, var_s5);
  sp.sp28 = temp_s0 << 9;
  do
  {
    var_s4 = 0;
    {
      register s32 sp28_value ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      sp28_value = sp.sp28;
      new_var = 1;
      five = 5;
      temp_s6 = five - var_s5;
      temp_s7 = sp28_value + 0x400;
    }
    loop_2:
    temp_v0 = func_8003FC64(0x202);

    if (temp_v0 != 0)
    {
      {
        register void *call_obj ASM_REG("$4") = temp_v0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register void *call_data ASM_REG("$5") = D_800CEEFC;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        register void *callback ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_USE2(call_obj, call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        callback = D_8002744C;
        *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = callback;
        func_8004491C(call_obj, call_data);
      }
      {
        void *temp_v0_2;
        register u16 value18 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 value1A ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        temp_v0_2 = *((void **) (((s8 *) temp_v0) + 8));
        *((s16 *) (((s8 *) temp_v0_2) + 2)) = arg0;
        *((s16 *) (((s8 *) temp_v0_2) + 0xE)) = arg0;
        value18 = sp.sp18;
        *((u16 *) (((s8 *) temp_v0_2) + 6)) = value18;
        *((u16 *) (((s8 *) temp_v0_2) + 0x12)) = value18;
        value1A = sp.sp1A;
        *((u16 *) (((s8 *) temp_v0_2) + 0xA)) = value1A;
        *((u16 *) (((s8 *) temp_v0_2) + 0x16)) = value1A;
      }
      call_result = func_80064584(temp_s7);
      temp_s1 = var_s4 << 7;
      inner_arg = temp_s1;
      temp_s0 = call_result;
      temp_s2 = temp_v0 + 0x20;
      {
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        product = temp_s0 * func_80064584(inner_arg);
        shifted = product >> temp_s6;
        *((s32 *) (((s8 *) temp_s2) + 0xC)) = shifted;
      }
      call_result = func_800644B8(temp_s7);
      inner_arg = temp_s1;
      temp_s0 = call_result;
      {
        register s32 product ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        product = temp_s0 * func_80064584(inner_arg);
        shifted = product >> temp_s6;
        *((s32 *) (((s8 *) temp_s2) + 0x10)) = shifted;
      }
      call_result = func_800644B8(temp_s1);
      {
        register s32 color ASM_REG("$5") = 0x808080;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        *((s32 *) (((s8 *) temp_s2) + 0x14)) = (s32) (call_result << ((var_s5 >> new_var) + 7));
        temp_a0 = *((void **) (((s8 *) temp_v0) + 0xC));
        *((s16 *) (((s8 *) temp_a0) + 0x1E)) = 0x400;
        *((s16 *) (((s8 *) temp_a0) + 0x1C)) = 0x400;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
          register void *late_address ASM_REG("$2") = D_80028880;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
          *((M2C_UNK **) (((s8 *) temp_a0) + 8)) = late_address;
        }
        *((s16 *) (((s8 *) temp_a0) + 0x10)) = 0x20;
        *((s32 *) (((s8 *) temp_a0) + 0xC)) = color;
        *((u16 *) (((s8 *) temp_a0) + 0x14)) = (u16) ((*((u16 *) (((s8 *) temp_a0) + 0x14))) | 0xC);
        *((s16 *) (((s8 *) temp_s2) + 0x66)) = 0xC;
        {
          register u16 final_width ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
          final_width = sp.sp20;
          *((u16 *) (((s8 *) temp_s2) + 0x74)) = final_width;
        }
      }
    }
    var_s4 += new_var;
    if (var_s4 < 0x20)
    {
      goto loop_2;
    }
    var_s5 += new_var;
  }
  while (var_s5 < 4);
  return temp_v0;
}
