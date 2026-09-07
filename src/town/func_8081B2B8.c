
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
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern u8 D_8002609C[];
extern u8 D_80045340[];
extern u8 D_800F15AC[];
void func_800252B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 new_var2;
  void *temp_a0;
  void *new_var;
  void *temp_v0;
  temp_v0 = func_8003FC64(0x136);
  if (temp_v0 != 0)
  {
    *((M2C_UNK **) (((s8 *) temp_v0) + 0x10)) = &D_8002609C;
    func_8004491C(temp_v0, &D_80045340);
    temp_a0 = *((void **) (((s8 *) temp_v0) + 0xC));
    *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 0)) = arg1;
    *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 4)) = arg2;
    *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 8)) = arg3;
    *((s16 *) (((s8 *) temp_a0) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) temp_a0) + 0x1C)) = 0x1000;
    *((M2C_UNK **) (((s8 *) temp_a0) + 0)) = &D_800F15AC;
    new_var2 = *((s32 *) (((s8 *) (&D_800F15AC)) + 4));
    *((s8 *) (((s8 *) temp_a0) + 4)) = 0;
    *((s8 *) (((s8 *) temp_a0) + 5)) = 0;
    *((s32 *) (((s8 *) temp_a0) + 0xC)) = arg0;
    new_var = temp_a0;
    *((s32 *) (((s8 *) new_var) + 8)) = (s32) new_var2;
    if (arg0 != 0x808080)
    {
      if (arg0 == 0xF0F0F0)
      {
        *((s16 *) (((s8 *) temp_a0) + 0x10)) = 0x60;
        *((s32 *) (((s8 *) (*((void **) (((s8 *) temp_v0) + 8)))) + 0x14)) = 0xFFF00000;
        goto block_4;
      }
    }
    else
    {
      block_4:
      *((u16 *) (((s8 *) temp_a0) + 0x14)) = (u16) ((*((u16 *) (((s8 *) temp_a0) + 0x14))) | 0xC);

    }
  }
}
