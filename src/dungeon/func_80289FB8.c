struct S_80083178
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
} MonsterInitialStats;
typedef struct
{
  unsigned char data[12];
} Trap;
typedef struct
{
  unsigned char data[8];
} StatGrowth;
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern struct S_80083178 D_80083178;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
extern s32 D_800E296C[3];
extern u8 D_800E3648[];
s32 func_800A6D30(void *, s32, s32, s32);
s32 func_800A6DA4();
extern u8 D_800E39C8[];
void func_8001CFB8(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  u8 *var_s2;
  s16 temp_v1;
  s16 var_s4;
  s32 temp_lo;
  s32 temp_rand;
  s32 temp_s0;
  s32 temp_v0;
  s32 var_v1;
  int new_var;
  u8 *var_s1;
  if (!((*D_800E296C) & 0x10000000))
  {
    temp_rand = func_800A6D30(arg0, arg1, arg2, arg3) & 7;
    temp_lo = (*((u16 *) (((s8 *) arg0) + 6))) * (*((u16 *) (((s8 *) arg0) + 4)));
    temp_v1 = (temp_lo >> 2) + temp_rand;
    var_s4 = temp_v1;
    if (temp_v1 >= 0x1D)
    {
      var_s4 = 0x1C;
    }
    var_v1 = 0;
    var_s1 = D_800E3648;
    var_s2 = &D_800E39C8;
    loop_4:
    if ((*((u8 *) (((s8 *) var_s1) + 1))) == 0)
    {
      temp_s0 = func_800A6DA4(0, ((*((u16 *) (((s8 *) arg0) + 4))) - 1) & 0xFFFF, temp_lo) & 0xFFFF;
      temp_v0 = func_800A6DA4(0, ((*((u16 *) (((s8 *) arg0) + 6))) - 1) & 0xFFFF);
      new_var = temp_v0 & 0xFFFF;
      *((s8 *) (((s8 *) var_s2) + 6)) = (s8) ((*((u8 *) (((s8 *) arg0) + 0))) + temp_s0);
      *((s8 *) (((s8 *) var_s2) + 7)) = (s8) ((*((u8 *) (((s8 *) arg0) + 2))) + new_var);
      *((u8 *) (((s8 *) var_s1) + 0)) = 0x13;
      *((u8 *) (((s8 *) var_s1) + 1)) = 0x15U;
      *((u8 *) (((s8 *) var_s1) + 3)) = (u8) 0xC0;
      *((s8 *) (((s8 *) var_s1) + 2)) = (s8) var_s4;
      *((s32 *) (((s8 *) var_s2) + 8)) = 0;
      return;
    }
    var_v1 += 1;
    var_s1 += 4;
    var_s2 += 0x18;
    if (var_v1 >= 0x20)
    {
    }
    else
    {
      goto loop_4;
    }
  }
}
