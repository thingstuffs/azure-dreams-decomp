#include "common.h"


extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
typedef s32 M2C_UNK;
extern u8 D_80083498[];
extern u8 D_800DDC40[];
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_8004DA74();
s32 func_8004E298();
M2C_UNK func_8004E5A0();
s32 func_80069E98();
void *func_800B119C();
void *func_800B12F4();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
extern M2C_UNK D_80077FEC;
extern M2C_UNK D_800B0D34;
extern s32 D_800DEFF8[];
extern M2C_UNK D_800B06F0;
void *func_800B0F50(void *arg0)
{
  s8 stack[16];
  s32 i;
  s32 temp_a0;
  register s32 temp_a1_value ASM_REG("$5");
  register s32 temp_a2_value ASM_REG("$6");
  register s32 temp_a3_value ASM_REG("$7");
  register s32 temp_s4_value ASM_REG("$20");
  register s32 temp_v0_value ASM_REG("$2");
  s32 temp_v0_3;
  register s32 shared_a0 ASM_REG("$4");
  register s32 temp_v1_value ASM_REG("$3");
  u16 temp_v1_2;
  void *temp_a2;
  void *temp_a3;
  void *temp_s0;
  void *temp_s1;
  register void *temp_s3 ASM_REG("$19");
  s32 *temp_s4;
  void *temp_s5;
  void *temp_v0;
  void *temp_v1;
  temp_s5 = arg0;
  temp_v0 = func_8003FD64(0x12, D_80083498);
  if (temp_v0 != 0)
  {
    temp_s4_value = 0x808080;
    temp_v1 = *((void **) (((s8 *) temp_v0) + 0xC));
    temp_a3 = *((void **) (((s8 *) temp_v0) + 8));
    *((s16 *) (((s8 *) temp_v1) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) temp_v1) + 0x1E)) = 0x1000;
    *((s32 *) (((s8 *) temp_v1) + 0xC)) = temp_s4_value;
    *((u16 *) (((s8 *) temp_v1) + 0x18)) = 0xFC00;
    temp_a2 = *((void **) (((s8 *) temp_s5) + (-0x18)));
    *((u16 *) (((s8 *) temp_a3) + 2)) = (u16) (*((u16 *) (((s8 *) temp_a2) + 2)));
    *((u16 *) (((s8 *) temp_a3) + 6)) = (u16) (*((u16 *) (((s8 *) temp_a2) + 6)));
    *((s16 *) (((s8 *) temp_a3) + 0xA)) = (s16) ((*((u16 *) (((s8 *) temp_a2) + 0xA))) - (D_800DDC40[*((u8 *) (((s8 *) temp_s5) + 0x13))] + 0x50));
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = &D_800B0D34;
    func_8004491C(temp_v0, &D_800B06F0, temp_a2, temp_a3);
    temp_s3 = temp_v0 + 0x20;
    *((void **) (((s8 *) temp_s3) + 0x14)) = temp_s5;
    *((void **) (((s8 *) temp_v0) + 0x20)) = (void *) (temp_v0 + 0x70);
    *((void **) (((s8 *) temp_s3) + 4)) = (void *) (temp_v0 + 0x58);
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x70)) = &D_80077FEC;
    *((s32 *) (((s8 *) temp_v0) + 0x58)) = temp_s4_value;
    temp_s1 = func_800B12F4();
    *((void **) (((s8 *) temp_s3) + 0x28)) = temp_s1;
    if (temp_s1 != 0)
    {
      temp_a1_value = 3;
      ASM_KEEP_NV(temp_a1_value);
      {
        s32 stack_value;
        stack_value = 9;
        stack[2] = stack_value;
        stack[0] = stack_value;
        stack_value = 0x38;
        temp_s0 = &stack[4];
        stack[3] = stack_value;
        stack[1] = stack_value;
      }
      func_8004E5A0(*((u8 *) (((s8 *) temp_s5) + 0x28)), temp_a1_value, temp_s0);
      *((s32 *) (((s8 *) temp_v0) + 0x74)) = func_8004E298(temp_s1, stack, 0);
      func_800B1320(temp_s1, 8, ((s32) (0 - (((s32) ((*((u8 *) (((s8 *) temp_s1) + 3))) << 0x18)) >> 8))) >> 0x10);
      func_800B135C(temp_s1, 8);
      temp_s1 += 0x24;
      *((s32 *) (((s8 *) temp_v0) + 0x5C)) = temp_s4_value;
      func_8004E5A0(*((u8 *) (((s8 *) temp_s5) + 0x25)), 3, temp_s0);
      *((s32 *) (((s8 *) temp_v0) + 0x78)) = func_8004E298(temp_s1, stack, 0);
      func_800B1320(temp_s1, 8, (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) temp_s1) + 3))))) + 8)));
      func_800B135C(temp_s1, 8);
      temp_s1 += 0x24;
      *((s32 *) (((s8 *) temp_v0) + 0x60)) = temp_s4_value;
      temp_v1_2 = *((u16 *) (((s8 *) temp_s5) + 0x46));
      temp_s4_value = (s32) (temp_v0 + 0x64);
      if (temp_v1_2 & 0x8000)
      {
        *((s32 *) (((s8 *) temp_v0) + 0x7C)) = func_8004DA74(temp_s1, D_800DEFF8[temp_v1_2 & 0x3FFF] + 1, 0);
        shared_a0 = D_800DEFF8[(*((u16 *) (((s8 *) temp_s5) + 0x46))) & 0x3FFF];
 do { i = 4; } while (0);
        goto join_69e98;
      }
      else
      {
        s32 *base = D_800DEFF8;
        *((s32 *) (((s8 *) temp_v0) + 0x7C)) = func_8004DA74(temp_s1, base[4] + 1, 0);
        shared_a0 = base[4];
        ASM_SCHED_BARRIER();
        i = 4;
        join_69e98:
        temp_v0_3 = func_80069E98(shared_a0 + 1);

        temp_v0_3 *= 4;
        ASM_SCHED_BARRIER();
        func_800B1320(temp_s1, (s16) ((((s32) (0x20 - temp_v0_3)) >> 1) + 0x80), (s32) ((s16) ((0 - ((s8) (*((u8 *) (((s8 *) temp_s1) + 3))))) + 0x11)));
        func_800B135C(temp_s1, 8);
        temp_s1 += 0x30;
      }
      ASM_KEEP(temp_s4_value);
      *((s32 *) temp_s4_value) = 0x808080;
      *((void **) (((s8 *) ((i * 4) + temp_s3)) + 0x50)) = temp_s1;
      *((u8 *) (((s8 *) temp_s1) + 1)) = 0x38U;
      *((s8 *) (((s8 *) temp_s1) + 2)) = -2;
      *((s8 *) (((s8 *) temp_s1) + 3)) = -2;
      *((s8 *) (((s8 *) temp_s1) + 9)) = 0;
      *((s8 *) (((s8 *) temp_s1) + 8)) = 0;
      *((s8 *) (((s8 *) temp_s1) + 0xB)) = 0x24;
      *((s8 *) (((s8 *) temp_s1) + 0xA)) = 0x24;
      temp_a0 = 0xC0;
      *((u8 *) (((s8 *) temp_s1) + 0)) = temp_a0;
      temp_a1_value = 0x202020;
      temp_a3_value = 0x402020;
      temp_a2_value = 0x204020;
      temp_v1_value = 0x200000;
      *((s32 *) (((s8 *) temp_s3) + 0x18)) = temp_a1_value;
      ASM_KEEP_NV(temp_a1_value);
      temp_v0_value = temp_a1_value;
      ASM_KEEP_NV(temp_v0_value);
      ASM_KEEP_NV(temp_v1_value);
      temp_v1_value |= 0x2040;
      *((s32 *) (((s8 *) temp_s3) + 0x1C)) = temp_a3_value;
      *((s32 *) (((s8 *) temp_s3) + 0x20)) = temp_a2_value;
      *((s32 *) (((s8 *) temp_s3) + 0x24)) = temp_v1_value;
      *((s32 *) (((s8 *) temp_s1) + 4)) = temp_v0_value;
      temp_v0_value = *((s32 *) (((s8 *) temp_s3) + 0x1C));
      ASM_KEEP_NV(temp_v0_value);
      *((s32 *) (((s8 *) temp_s1) + 0xC)) = temp_v0_value;
      temp_v0_value = *((s32 *) (((s8 *) temp_s3) + 0x20));
      ASM_KEEP_DEP_NV(i, temp_v0_value);
      i++;
      *((s32 *) (((s8 *) temp_s1) + 0x10)) = temp_v0_value;
      ASM_SCHED_BARRIER();
      temp_v1_value = *((s32 *) (((s8 *) temp_s3) + 0x24));
      *((u8 *) (((s8 *) temp_s1) + 1)) = (u8) ((*((u8 *) (((s8 *) temp_s1) + 1))) | 2);
      *((s32 *) (((s8 *) temp_s1) + 0x14)) = temp_v1_value;
      ASM_SCHED_BARRIER();
      temp_s1 += 0x18;
      *((void **) (((s8 *) ((i * 4) + temp_s3)) + 0x50)) = temp_s1;
      *((u8 *) (((s8 *) temp_s1) + 1)) = 0x81;
      *((s16 *) (((s8 *) temp_s1) + 4)) = 0x40;
      *((s16 *) (((s8 *) temp_s1) + 6)) = 0;
      *((u8 *) (((s8 *) temp_s1) + 0)) = temp_a0;
    }
  }
  return temp_v0;
}
