
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
typedef struct 
{
  s32 f0;
  s32 f4;
  s32 f8;
  s32 fc;
  s32 f10;
  s32 f14;
} Arg1;
typedef struct 
{
  u8 pad0[0xC];
  u8 c;
  u8 d;
  u8 e;
  u8 padF[0xD];
  u16 f1c;
  u16 f1e;
} Arg2;
extern u16 D_800269F8[5];
extern s32 D_800814A0[3];
void func_800245F8(void *arg0, void *arg1, void *arg2)
{
  Arg2 *p2 = (Arg2 *) arg2;
  void *p0 = arg0;
  Arg1 *p1 = (Arg1 *) arg1;
  s16 temp_v0;
  s32 temp_v1_0;
  u16 temp_v1_3;
  u16 temp_v1_4;
  int new_var;
  u8 temp_v1;
  u8 temp_v1_2;
  temp_v1_4 = D_800269F8[0] + 1;
  temp_v1_0 = p1->f0 + p1->fc;
  D_800269F8[0] = (u16) temp_v1_4;
  p1->f0 = temp_v1_0;
  new_var = 0;
  p1->f4 = p1->f4 + p1->f10;
  p1->f8 = p1->f8 + p1->f14;
  p1->f14 = p1->f14 + 0xC000;
  func_800478B8(p2);
  temp_v1 = p2->c;
  temp_v1_2 = temp_v1 - (((s32) temp_v1) / ((s16) (*((s16 *) (((s8 *) p0) + 0x30)))));
  p2->c = temp_v1_2;
  p2->d = temp_v1_2;
  p2->e = temp_v1_2;
  temp_v1_3 = p2->f1c;
  temp_v1_4 = temp_v1_3 + (((s32) (0x400 - temp_v1_3)) / ((s16) (*((s16 *) (((s8 *) p0) + 0x30)))));
  p2->f1c = temp_v1_4;
  p2->f1e = temp_v1_4;
  temp_v0 = ((u16) (*((s16 *) (((s8 *) p0) + 0x30)))) - 1;
  *((s16 *) (((s8 *) p0) + 0x30)) = temp_v0;
  if ((temp_v0 << 0x10) <= new_var)
  {
    *((u16 *) (((s8 *) p0) + (-2))) = (u16) ((*((u16 *) (((s8 *) p0) + (-2)))) | 0x8000);
    D_800814A0[new_var] = (s32) (D_800814A0[0] | 0x8000);
  }
}
