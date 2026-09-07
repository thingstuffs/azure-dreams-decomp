
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
M2C_UNK func_80058588();
s32 func_80071424();
void func_80526BE4(void) __attribute__((noreturn));
extern s32 D_80084D5C;
void func_8080BF18(void *arg0)
{
  s16 temp_v1;
  u16 temp_v0;
  u16 temp_v1_u;
  void *temp_s1;
  temp_s1 = *((void **) (((s8 *) arg0) + 0xC));
  func_80058588(*(*((s16 **) (((s8 *) arg0) + 8))), func_80071424(*((s32 *) (((s8 *) arg0) + 4))), *((s32 *) (((s8 *) arg0) + 4)));
  temp_v1 = *((s16 *) (((s8 *) arg0) + 0));
  if (temp_v1 == 0)
  {
    goto state_0;
  }
  if (temp_v1 == 1)
  {
    goto state_1;
  }
  func_80526BE4();
  return;
 do { state_0: temp_v0 = (*((u16 *) (((s8 *) arg0) + 2))) - 1; *((u16 *) (((s8 *) arg0) + 2)) = temp_v0; if ((temp_v0 << 0x10) > 0) { return; } temp_v1_u = (*((u16 *) (((s8 *) arg0) + 0))) + 1; temp_v0 = (*((u16 *) (((s8 *) arg0) + 0x1C))) & 0xFFFD; } while (0);
  *((u16 *) (((s8 *) arg0) + 0x1C)) = temp_v0;
  *((u16 *) (((s8 *) arg0) + 0)) = temp_v1_u;
  func_80526BE4();
  return;
  state_1:
  if ((*((u16 *) (((s8 *) temp_s1) + 0x2A))) & 1)
  {
    *((u16 *) (((s8 *) arg0) + (-2))) = (u16) ((*((u16 *) (((s8 *) arg0) + (-2)))) | 0x8000);
    *((s32 *) 0x80084D5C) = D_80084D5C | 0x8000;
  }

}
