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
extern u32 D_8006ADBC;
extern s32 D_800D3824[];
extern void func_800BC45C(s32 arg0, s16 arg1, void *state);
extern void func_800C0E4C(void);
void func_800C0DE8(void)
{
  s32 *entry;
  s8 *state;
  if (*((volatile s32 *) D_800D3824) != (-1))
  {
    do
    {
      state = (s8 *) (&D_8006ADBC);
    } while (0);
    entry = D_800D3824;
    loop:
    if (*((s16 *) (state + 0x1A)) == (*entry))
    {
      func_800BC45C(*((s32 *) (((s8 *) entry) + 4)), *((s16 *) (((s8 *) entry) + 8)), state);
      return;
    }
    entry += 3;
    if (*entry != (-1))
    {
      goto loop;
    }
  }
}
