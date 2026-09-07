
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
typedef s32 M2C_UNK;
extern void *func_8003FD64();
extern M2C_UNK D_800240F0;
extern M2C_UNK D_80083498;
void func_80024494(s32 arg0, s32 arg1, s32 arg2)
{
  int new_var;
  void *temp_v0;
  void *temp_v0_2;
  void *temp_v1;
  temp_v0 = func_8003FD64(0x12, &D_80083498);
  if (temp_v0 != 0)
  {
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = &D_800240F0;
    new_var = 0x80;
    temp_v0_2 = temp_v0 + 0x20;
    *((s16 *) (((s8 *) temp_v0_2) + 0xC)) = 0;
    *((s16 *) (((s8 *) temp_v0_2) + 0xE)) = 0;
    *((s32 *) (((s8 *) temp_v0) + 0x20)) = arg0;
    *((M2C_UNK **) (((s8 *) temp_v0_2) + 4)) = &D_80083498;
    *((s32 *) (((s8 *) temp_v0_2) + 8)) = arg1;
    temp_v1 = *((void **) (((s8 *) temp_v0) + 0xC));
    *((s8 *) (((s8 *) temp_v1) + 0xE)) = new_var;
    *((s8 *) (((s8 *) temp_v1) + 0xD)) = new_var;
    *((s8 *) (((s8 *) temp_v1) + 0xC)) = new_var;
    *((s16 *) (((s8 *) temp_v1) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) temp_v1) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) temp_v1) + 0x12)) = 0x7E00;
    *((s32 *) (((s8 *) temp_v1) + 8)) = arg2;
    *((u16 *) (((s8 *) temp_v1) + 0x10)) = (u16) ((*((u16 *) (((s8 *) temp_v1) + 0x10))) | 0x20);
    *((u16 *) (((s8 *) temp_v1) + 0x14)) = (u16) ((*((u16 *) (((s8 *) temp_v1) + 0x14))) | 0x10C);
  }
}
