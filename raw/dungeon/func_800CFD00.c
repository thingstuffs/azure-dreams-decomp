
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
extern void func_8003DB94(void *, void *, s32);
extern void *func_8003FC64(s32);
extern void func_800A56E0(s32);
extern u8 D_80083460[12];
extern M2C_UNK D_800D5294;
extern M2C_UNK D_800DECF8[3];
void func_800D5460(void *arg0, s32 arg1, unsigned short arg2)
{
  M2C_UNK *var_v1;
  s32 *arg1_ptr;
  s32 temp_a0_3;
  s32 temp_arg1;
  void *temp_a0;
  void *temp_a0_2;
  void *temp_a1;
  void *temp_a1_2;
  void *temp_v0;
  void *temp_v1;
  arg1_ptr = &arg1;
  temp_v0 = func_8003FC64(0x12);
  if (temp_v0 != 0)
  {
    temp_a1 = temp_v0 + 0x20;
    *((void **) (((u8 *) temp_a1) + 0x24)) = arg0;
    *((M2C_UNK **) (((u8 *) temp_v0) + 0x10)) = &D_800D5294;
    *((s16 *) (((u8 *) temp_a1) + 0x1E)) = 0x32;
    temp_a0 = *((void **) (((u8 *) temp_v0) + 0xC));
    *((s16 *) (((u8 *) temp_a0) + 0x10)) = 0x20;
    *((u16 *) (((u8 *) temp_a0) + 0x14)) = (u16) ((*((u16 *) (((u8 *) temp_a0) + 0x14))) | 0xC);
    temp_v1 = *((void **) (((u8 *) temp_v0) + 8));
    *((u16 *) (((u8 *) temp_v1) + 2)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 8)))) + 2)));
    *((u16 *) (((u8 *) temp_v1) + 6)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 8)))) + 6)));
    *((u16 *) (((u8 *) temp_v1) + 0xA)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 8)))) + 0xA)));
    temp_a0_2 = *((void **) (((u8 *) temp_v0) + 0xC));
    *((u8 *) (((u8 *) temp_a0_2) + 0xE)) = 0x80;
    *((u8 *) (((u8 *) temp_a0_2) + 0xD)) = 0x80;
    *((u8 *) (((u8 *) temp_a0_2) + 0xC)) = 0x80;
    temp_arg1 = *arg1_ptr;
    *((s16 *) (((u8 *) temp_a0_2) + 0x1E)) = 0x1000;
    *((s16 *) (((u8 *) temp_a0_2) + 0x1C)) = 0x1000;
    *((s32 *) (((u8 *) temp_a0_2) + 0xC)) = temp_arg1;
    *((s32 *) (((u8 *) temp_a1) + 0xC)) = temp_arg1;
    *((s16 *) (((u8 *) temp_a0_2) + 0x12)) = 0x7DCE;
    temp_a1_2 = D_800DECF8;
    *((u16 *) (((u8 *) temp_a0_2) + 0x14)) = (u16) ((*((u16 *) (((u8 *) temp_a0_2) + 0x14))) | 0x100);
    func_8003DB94(temp_a0_2, temp_a1_2, 0);
    temp_a0_3 = arg2 & 0xFFFF;
    if (temp_a0_3 != 0)
    {
      func_800A56E0(temp_a0_3);
    }
    var_v1 = (M2C_UNK *) D_80083460;
    *((u16 *) (((u8 *) var_v1) + 0xA)) = (u16) ((*((u16 *) (((u8 *) var_v1) + 0xA))) + 1);
  }
}
