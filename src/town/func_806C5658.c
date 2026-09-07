
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
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
extern M2C_UNK D_80016000;
void func_80016658(void)
{
  char new_var;
  void *temp_v1;
  void *temp_v1_2;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x20)))) + 0x248)))(0);
  new_var = 0x6000;
  temp_v1 = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x1C));
  *((s32 *) (((s8 *) temp_v1) + 0x10)) = (s32) ((*((s32 *) (((s8 *) temp_v1) + 4))) + 0x28);
  temp_v1_2 = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x1C));
  *((s32 *) (((s8 *) temp_v1_2) + 0x14)) = (s32) (*((s32 *) (((s8 *) temp_v1_2) + 8)));
}
