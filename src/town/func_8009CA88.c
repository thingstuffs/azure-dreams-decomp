#include "common.h"
#include "m2c_compat.h"

struct S_80083178_L
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94];
  short f_A0;
  char pad_a2[2];
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xB4 - 0xAA];
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
};
typedef struct 
{
  unsigned char data[24];
} MonsterInitialStats_L;
typedef struct 
{
  unsigned char data[12];
} Trap_L;
typedef struct 
{
  unsigned char data[8];
} StatGrowth_L;
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
s32 func_8003BD84();
M2C_UNK func_80098928();
M2C_UNK func_8009A324();
u16 func_800C2AE8();
extern u8 D_80082660;
extern M2C_UNK D_80099C18;
void func_8009A1E8(void *arg0, void *arg1, M2C_UNK arg2)
{
  unsigned int new_var2;
  s32 temp_a0;
  s32 var_v0_2;
  s32 var_v1;
  register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
  s32 var_v0;
  s8 *new_var;
  *(((*((s32 *) (((s8 *) arg0) + 0x40))) * 8) + (&D_80082660)) = 0;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_80099C18;
  var_v1 = func_8003BD84(((*((s16 *) (((s8 *) arg0) + 0x36))) << 0x10) - (*((s32 *) (((s8 *) arg1) + 0))), ((*((s16 *) (((s8 *) arg0) + 0x38))) << 0x10) - (*((s32 *) (((s8 *) arg1) + 4))));
  if (var_v1 < 0)
  {
    var_v1 += 0x1FFFF;
  }
  new_var = (s8 *) (((*((s32 *) (((s8 *) arg0) + 0x40))) * 8) + (&D_80082660));
  temp_a0 = var_v1 >> 0x11;
  *((s16 *) (((s8 *) arg0) + 0xA)) = (s16) temp_a0;
  temp_v1 = *((s8 *) (new_var + 2));
  if (temp_v1 == (-0x80))
  {
    *((s32 *) (((s8 *) arg1) + 0)) = (s32) ((*((s16 *) (((s8 *) arg0) + 0x36))) << 0x10);
    *((s32 *) (((s8 *) arg1) + 4)) = (s32) ((*((s16 *) (((s8 *) arg0) + 0x38))) << 0x10);
    *((u16 *) (((s8 *) arg1) + 0xA)) = (u16) ((*((u16 *) (((s8 *) arg1) + 0xA))) - 0x80);
    *((u16 *) (((s8 *) arg1) + 0xA)) = func_800C2AE8(arg1);
    func_80098928(arg0, arg1, arg2);
    return;
  }
  if (temp_v1 > 0)
  {
    *((s16 *) (((s8 *) arg0) + 0xA)) = (s16) ((temp_a0 << 4) / (temp_v1 + 0x10));
    return;
  }
  if (temp_v1 < 0)
  {
    ASM_KEEP(temp_v1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    new_var2 = temp_v1;
    if (temp_v1 < 0)
    {
      var_v0 = 0 - new_var2;
    }
    else
    {
      var_v0 = new_var2;
    }
    var_v0_2 = temp_a0 * (var_v0 + 0x10);
    if (var_v0_2 < 0)
    {
      var_v0_2 += 0xF;
    }
    *((s16 *) (((s8 *) arg0) + 0xA)) = (s16) (var_v0_2 >> 4);
  }
}
