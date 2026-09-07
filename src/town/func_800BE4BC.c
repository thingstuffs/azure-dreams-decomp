
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
typedef struct 
{
  u8 pad0[8];
  s32 *field_0x8;
  u8 pad0xC[4];
  void *field_0x10;
} S_800BE4BC;
extern void func_80033B78(s32 arg0);
extern void *func_8003FD64(s32 arg0, void *arg1);
extern u8 D_80083498[16];
extern u8 D_800BBCA0[16];
s32 func_800BBC1C(s32 *arg0)
{
  S_800BE4BC *obj;
  u8 (*new_var4)[16];
  S_800BE4BC *new_var3;
  s32 *new_var2;
  u8 (*new_var)[16];
  func_80033B78(0x97);
  new_var = &D_80083498;
  obj = func_8003FD64(0x312, new_var);
  new_var3 = obj;
  if (new_var3 != 0)
  {
    new_var4 = &D_800BBCA0;
    obj->field_0x10 = new_var4;
    obj->field_0x8[0] = arg0[0];
    new_var2 = arg0;
    obj->field_0x8[1] = new_var2[1];
    obj->field_0x8[2] = new_var2[2];
  }
  if (obj)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}
