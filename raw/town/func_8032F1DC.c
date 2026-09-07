
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
s32 func_8001ADE0();
extern s16 D_8001B8AA;
s32 func_800199DC(void *arg0)
{
  s32 var_v0;
  void *new_var3;
  int new_var2;
  void *new_var;
  if (new_var2)
  {
    new_var2 = 0;
    var_v0 = new_var2;
    new_var3 = arg0;
    new_var = new_var3;
  }
  else
  {
    new_var2 = 0;
    var_v0 = new_var2;
    new_var3 = arg0;
    new_var = new_var3;
  }
  if (func_8001ADE0(D_8001B8AA) == 0)
  {
    var_v0 = func_8001ADE0(*(s16 *) (((s8 *) new_var) + 0x18)) != 0;
  }
  return var_v0;
}
