
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
extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_80099734(s32, s32);
extern void func_80099290(s32);
extern void func_800A5720(s32);
extern u8 D_80176440[9];
extern u8 D_80176455[9];
void func_80175DA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 new_var2;
  s32 temp_v0;
  unsigned int new_var;
  if (1)
  {
    new_var2 = func_800990FC(arg0, arg1, arg2, arg3);
    if (1)
    {
      temp_v0 = new_var2;
      new_var = func_80099194(D_80176440, temp_v0);
      new_var2 = arg0;
      func_80099290(func_80099194(D_80176455, func_80099734(new_var2, new_var)));
    }
    func_800A5720(temp_v0);
  }
}
