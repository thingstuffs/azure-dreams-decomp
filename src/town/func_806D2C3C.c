
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
extern void func_80016DDC(void *, void *, s32);
u8 *func_806D2C3C(u8 *arg0, u8 *arg1, s32 arg2, u32 arg3)
{
  u8 *cursor;
  u32 arg2_part;
  u8 *new_var;
  u32 arg3_part;
  cursor = arg0 + 12;
  do
  {
    func_80016DDC(arg0, arg1, 5);
    new_var = cursor;
    arg0 += 20;
    if (arg2 != 0)
    {
      *((u32 *) (new_var - 4)) = (arg2 & 0x3FFF0000) | 0xC0000010;
    }
 do { } while (0);
    arg1 += 20;
    {
      u32 value;
      u32 temp;
      arg2_part = ((arg2 >> 8) & 0x3F) << 24;
      arg3_part = (arg3 & 0xFF) << 16;
      value = 0xC0000000;
      value |= arg3_part;
      temp = arg2_part;
      temp |= value;
      value = temp;
      value |= *((u16 *) new_var);
      *((u32 *) new_var) = value;
    }
    cursor += 20;
  }
  while (arg1[-19] != 0x80);
  return arg0;
}
