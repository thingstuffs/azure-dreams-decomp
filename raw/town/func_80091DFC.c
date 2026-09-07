
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
void func_8008F55C(s32 arg0, void *arg1, void *arg2)
{
  int new_var;
  void *temp_v1;
  if ((*((u8 *) (((s8 *) arg2) + 0x28))) == 0)
  {
    new_var = (*((s32 *) (((s8 *) arg1) + 0))) - (*((s32 *) (((s8 *) arg2) + 0x10)));
    *((s32 *) (((s8 *) arg1) + 0xC)) = 0;
    *((s32 *) (((s8 *) arg1) + 0)) = (s32) new_var;
  }
  temp_v1 = arg0 + (*((s32 *) (((s8 *) arg2) + 0x2C)));
  *((u8 *) (((s8 *) temp_v1) + 0x3A)) = (u8) ((*((u8 *) (((s8 *) temp_v1) + 0x3A))) + 1);
  *((s32 *) (((s8 *) (((*((s32 *) (((s8 *) arg2) + 0x2C))) * 4) + arg0)) + 0x1C)) = (s32) (*((s32 *) (((s8 *) arg2) + 4)));
}
