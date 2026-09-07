
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
void func_800239A0(void *arg0, s16 *arg1, s16 arg2)
{
  s32 var_a3;
  void *var_v1;
  var_a3 = 0;
  var_v1 = arg0;
  do
  {
    if (((*((s16 *) (((s8 *) var_v1) + 0x44))) < 0) && ((*arg1) >= 4))
    {
      *((s16 *) (((s8 *) var_v1) + 0x44)) = arg2;
    }
    if (arg0)
    {
      var_a3 += 1;
      var_v1 += 2;
    }
    else
    {
      var_a3 += 1;
      var_v1 += 2;
    }
  }
  while (var_a3 < 2);
  if ((*((s16 *) (((s8 *) arg0) + 0x44))) == (*((s16 *) (((s8 *) arg0) + 0x46))))
  {
    *((s16 *) (((s8 *) arg0) + 0x46)) = -1;
  }
}
