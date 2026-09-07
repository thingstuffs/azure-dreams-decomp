
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
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
extern s32 D_800250E8[3];
extern u8 D_800251E8[9];
s32 func_80099194();
s32 func_8009929C();
extern s32 D_80025024;
extern s32 D_800250B8;
extern s32 D_800250D8;
extern s32 D_800250F4;
extern s32 D_80025110;
extern s32 D_8002512C;
extern s32 D_80025154;
extern s32 D_80025184;
extern s32 D_800251B4;
extern s32 D_80025208;
extern s32 D_8002522C;
extern s32 D_80025244;
extern s32 D_80025260;
extern s32 D_80025284;
extern s32 D_800252A4;
extern s32 D_800252C8;
extern s32 D_800252E4;
extern s32 D_80025300;
extern s32 D_80025318;
extern M2C_UNK D_80025160;
s32 func_80028208(void *arg0, s32 arg1)
{
  s32 var_a1;
  s32 var_s0;
  s32 result;
  var_s0 = 0;
  var_a1 = func_80099194(&D_800250B8);
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 1)
  {
    var_a1 = func_80099194(&D_800250D8, func_8009929C(0xA, var_a1));
    var_s0 = 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 2)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_800250F4, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 4)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025110, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 8)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_8002512C, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x10)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025154, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x20)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025160, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x80)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025184, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x100)
  {
    arg0++;
    arg0--;
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_800251B4, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x8000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194((s32 *) D_800251E8, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x100000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025208, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x10000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_8002522C, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x02000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025244, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x04000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025260, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x08000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025284, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x10000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_800252A4, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x20000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_800252C8, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x40000000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_800252E4, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x200000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025300, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((*((s32 *) (((s8 *) arg0) + 0x54))) & 0x4000)
  {
    if ((var_s0 << 0x10) != 0)
    {
      var_a1 = func_80099194(D_800250E8, var_a1);
    }
    var_a1 = func_80099194(&D_80025318, func_8009929C(0xA, var_a1));
    var_s0 += 1;
  }
  if ((var_s0 << 0x10) != 0)
  {
    result = func_80099194(&D_80025024, var_a1);
  }
  else
  {
    result = arg1;
  }
  return result;
}
