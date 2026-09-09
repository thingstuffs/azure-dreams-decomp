#include "common.h"

typedef s32 M2C_UNK;
typedef struct 
{
  u8 b[32];
} DungeonTable;
extern u8 D_80171704[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern DungeonTable D_8016A894;
extern M2C_UNK D_801718E4;
void func_80171A10(void *arg0, s32 arg1, s32 arg2, s32 unused, volatile s32 arg4)
{
  register void *r_arg0 ASM_REG("$17") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  register u32 r_arg1 ASM_REG("$18") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  register s32 r_arg2 ASM_REG("$22") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  s32 r_mode;
  void *new_var;
  DungeonTable sp10 = D_8016A894;
  register u8 *body_sp ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register u8 *body_base ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  void *temp_a0_2;
  void *temp_a1;
  void *temp_a1_2;
  void *temp_a2;
  void *temp_a2_2;
  void *temp_s1;
  void *temp_v0;
  void *temp_func;
  register s32 temp_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  u32 temp_s5;
  s32 temp_tail;
  void *temp_tail_base;
  ASM_KEEP(r_arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  ASM_KEEP(r_arg2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  {
    u32 call_arg0 = 0x211;
    ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    r_mode = arg4;
    ASM_KEEP(r_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s5 = r_arg1;
    temp_v0 = func_8003FD64(call_arg0, r_arg0);
  }
  ASM_UNDEF(body_sp);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  if (temp_v0 != 0)
  {
    register u32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    body_base = body_sp + 0x10;
    ASM_KEEP(body_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_func = &D_801718E4;
    ASM_KEEP_DEP_NV(r_arg1, temp_func);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_a0 = r_arg1 >> 7;
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = temp_func;
    *((u16 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 2)) = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) r_arg0) + 8)))) + 2)));
    temp_a0 &= 0x1C;
    *((u16 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 6)) = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) r_arg0) + 8)))) + 6)));
    temp_a0 = (u32) body_base + temp_a0;
    ASM_KEEP(r_arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    *((s16 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 0xA)) = (s16) ((*((u16 *) (((s8 *) (*((void **) (((s8 *) r_arg0) + 8)))) + 0xA))) - 0x14);
    ASM_KEEP(r_arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_a1 = *((void **) (((s8 *) temp_v0) + 8));
    *((u16 *) (((s8 *) temp_a1) + 2)) = (u16) ((*((u16 *) (((s8 *) temp_a1) + 2))) + ((*((s16 *) (((s8 *) ((void *) temp_a0)) + 0))) * 0x10));
    temp_a0_2 = *((void **) (((s8 *) temp_v0) + 8));
    *((u16 *) (((s8 *) temp_a0_2) + 6)) = (u16) ((*((u16 *) (((s8 *) temp_a0_2) + 6))) + (((s32) ((*((u16 *) (((s8 *) ((void *) temp_a0)) + 2))) << 0x10)) >> 0xC));
    *((s16 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 0xC)))) + 6)) = 6;
    temp_s1 = temp_v0 + 0x20;
    if ((r_mode << 0x10) == 0)
    {
      *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 0xC)) = (s32) (((func_80069EF8(temp_a0_2, temp_a1) & 0x7FFF) - 0x4000) << 7);
      temp_tail = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 7);
      temp_tail_base = *((void **) (((s8 *) temp_v0) + 8));
      *((s32 *) (((s8 *) temp_tail_base) + 0x10)) = temp_tail;
    }
    else
    {
      *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 0xC)) = (s32) (((func_80069EF8(temp_a0_2, temp_a1) & 0x7FFF) - 0x4000) << 6);
      temp_tail = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 6);
      temp_tail_base = *((void **) (((s8 *) temp_v0) + 8));
      *((s32 *) (((s8 *) temp_tail_base) + 0x10)) = temp_tail;
    }
    temp_value = (s32) (((func_80069EF8() & 0x7FFF) - 0x4000) << 5);
    {
      register u8 *tail_sp ASM_REG("$29");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      ASM_UNDEF(tail_sp);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
      temp_a2 = tail_sp + 0x10;
    }
    temp_a1_2 = (new_var = *((void **) (((s8 *) temp_v0) + 8)));
    *((s32 *) (((s8 *) temp_a1_2) + 0x14)) = temp_value;
    new_var = temp_v0;
    temp_value = temp_s5 >> 7;
    temp_value &= 0x1C;
    temp_a2 += temp_value;
    temp_a1_2 = *((void **) (((s8 *) new_var) + 8));
    *((s32 *) (((s8 *) temp_a1_2) + 0xC)) = (s32) ((*((s32 *) (((s8 *) temp_a1_2) + 0xC))) + ((*((s16 *) (((s8 *) temp_a2) + 0))) * 0x160000));
    temp_a2_2 = *((void **) (((s8 *) new_var) + 8));
    *((s32 *) (((s8 *) temp_a2_2) + 0x10)) = (s32) ((*((s32 *) (((s8 *) temp_a2_2) + 0x10))) + (((s16) (*((volatile u16 *) (((s8 *) temp_a2) + 2)))) * 0x160000));
    *((u16 *) (((s8 *) temp_s1) + 0x14)) = temp_s5;
    *((s16 *) (((s8 *) temp_s1) + 0x32)) = 7;
    *((s16 *) (((s8 *) temp_s1) + 0x34)) = 7;
    func_8004491C(new_var, D_80171704, temp_a2_2);
    ASM_KEEP(temp_s1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    *((s32 *) temp_s1) = r_arg2;
    *((s32 *) (((s8 *) temp_s1) + 8)) = r_arg2;
  }
}
