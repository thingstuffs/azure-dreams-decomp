
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
extern void func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern u8 D_800345B8[];
extern u8 D_800A1FEC[];
extern s16 D_800D0A10[];
extern s32 D_800D0A1C[];
extern u16 D_800D0A34[];
extern u8 D_800F148C[];
void func_800A1F00(void *arg0, s32 arg1, void *arg2)
{
  s16 *temp_s0;
  s32 *table_s3;
  s32 *base_s3;
  u16 *table_s2;
  u16 *base_s2;
  u8 *new_var;
  u16 value_s2;
  s32 temp_s3;
  s32 temp_s2;
  temp_s3 = *((s16 *) (((s8 *) arg0) + 0x20));
  *((s32 *) (((s8 *) arg2) + 0)) = 0;
  *((s8 *) (((s8 *) arg2) + 4)) = 0;
  *((s8 *) (((s8 *) arg2) + 5)) = 0;
  *((u8 **) (((s8 *) arg2) + 8)) = D_800F148C;
  func_8004491C(arg0 - 0x20, D_800345B8);
  new_var = (u8 *) D_800D0A10;
  *((s16 *) (((s8 *) arg2) + 0x10)) = 0x20;
  *((u16 *) (((s8 *) arg2) + 0x14)) |= 0x1C;
  temp_s2 = temp_s3 * 2;
  temp_s0 = (s16 *) (new_var + temp_s2);
  *((s32 *) (((s8 *) arg0) + 0x24)) = func_800644B8(*temp_s0);
  temp_s3 *= 4;
  *((s32 *) (((s8 *) arg0) + 0x28)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x2C)) = func_80064584(*temp_s0);
  base_s3 = D_800D0A1C;
  table_s3 = (s32 *) (((u8 *) base_s3) + temp_s3);
  *((s32 *) (((s8 *) arg0) + 0x3C)) = *table_s3;
  base_s2 = D_800D0A34;
  table_s2 = (u16 *) (((u8 *) base_s2) + temp_s2);
  value_s2 = *table_s2;
  *((u8 **) (((s8 *) arg0) + 0)) = D_800A1FEC;
  *((u16 *) (((s8 *) arg0) + 0x22)) = value_s2;
}
