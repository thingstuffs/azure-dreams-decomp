
struct S_80083178Vector
{
  short x;
  short y;
  short z;
  short pad;
};
struct S_80083178State
{
  struct S_80083178Vector v[4];
};
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94 - 0xC];
  struct S_80083178State state_94;
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
extern struct S_80083178State D_80083CE8;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
extern u8 D_800198A4[];
extern s32 D_80019B8C;
s32 func_80017958(void)
{
  s32 *new_var;
  s32 offset;
  u8 *base;
  base = D_800198A4;
  offset = ((unsigned int) D_80019B8C) * 0x18;
  new_var = (s8 *) (base + offset);
  new_var = new_var + 4;
  return *new_var;
}
