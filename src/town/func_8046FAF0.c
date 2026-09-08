
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
extern M2C_UNK func_80018F74();
extern s32 func_800196F4();
extern s32 func_8001979C();
extern void *D_80016000;
/* Invoke the callback for a match, or process a valid fallback lookup result. */
void func_80016AF0(void)
{
  s32 lookup_result;

  if (func_800196F4(0xD, 3) != 0)
  {
    (*((M2C_UNK (**)(M2C_UNK))
        (((s8 *) (*((void **) (((s8 *) D_80016000) + 0x20)))) + 0x78)))(0);
    return;
  }
  lookup_result = func_8001979C(0xD, 3);
  if (lookup_result != (-1))
  {
    func_80018F74(lookup_result);
  }
}
