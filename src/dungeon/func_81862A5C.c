
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
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_8002418C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEDB0[3];
void func_81862A5C(s32 arg0, void *arg1)
{
  s32 temp_v0_2;
  void *temp_s0;
  int new_var;
  void *temp_s0_2;
  void *temp_v0;
  temp_v0 = func_8003FC64(0x212);
  if (temp_v0 != 0)
  {
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = &D_8002418C;
    temp_s0 = *((void **) (((s8 *) temp_v0) + 0xC));
    *((s32 *) (((s8 *) temp_v0) + 0x20)) = arg0;
    *((s8 *) (((s8 *) temp_v0) + 0x24)) = 0;
    new_var = 0x80;
    *((s8 *) (((s8 *) temp_s0) + 0xE)) = new_var;
    *((s8 *) (((s8 *) temp_s0) + 0xD)) = new_var;
    *((s8 *) (((s8 *) temp_s0) + 0xC)) = new_var;
    func_8003DB94(temp_s0, D_800DEDB0, 0);
    *((s16 *) (((s8 *) temp_s0) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) temp_s0) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) temp_s0) + 0x12)) = 0x7E0B;
    *((u16 *) (((s8 *) temp_s0) + 0x10)) = (u16) ((*((u16 *) (((s8 *) temp_s0) + 0x10))) | 0x60);
    *((u16 *) (((s8 *) temp_s0) + 0x14)) = (u16) ((*((u16 *) (((s8 *) temp_s0) + 0x14))) | 0x10C);
    func_8004491C(temp_v0, &D_80045340);
    temp_s0_2 = *((void **) (((s8 *) temp_v0) + 8));
    rand();
    *((u16 *) (((s8 *) temp_s0_2) + 2)) = (u16) (*((u16 *) (((s8 *) arg1) + 2)));
    *((u16 *) (((s8 *) temp_s0_2) + 6)) = (u16) (*((u16 *) (((s8 *) arg1) + 6)));
    temp_v0_2 = rand();
    *((s16 *) (((s8 *) temp_s0_2) + 0xA)) = (s16) (((*((u16 *) (((s8 *) arg1) + 0xA))) - 0x40) - (temp_v0_2 % 16));
  }
}
