
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
typedef struct 
{
  u8 x;
  u8 y;
  u8 w;
  u8 h;
  u8 pad[2];
  u8 id;
  u8 pad7;
} Entry;
extern u8 D_800D3814[12];
extern u8 D_800D2EA4[];
extern u8 D_80082E60[];
extern u16 D_80082E76;
extern volatile s8 D_800D381A;
extern s32 func_80041094();
extern s32 func_800B91F0();
void func_800B90F0(void)
{
  s32 i = 0x20;
  u8 *state = D_800D3814;
  u8 *shared = D_80082E60;
  u8 *table = D_800D2EA4;
  u8 *entry = table + 0x100;
  u8 *slot = (u8 *) 0x80010040;
  u8 *new_var;
  u8 *fallback;
  loop:
  i--;

  if (slot[0x33A4] == state[6])
  {
    func_80041094(0xB, ((entry[0] + (entry[2] >> 1)) << 6) | 0x20, ((entry[1] + entry[3]) << 6) | 0x20, 0, (*((u16 *) (&shared[0x16]))) ^ 1);
    state[6] = 0;
    func_800B91F0();
    return;
  }
  entry -= 8;
  slot -= 2;
  if (i <= 0)
  {
    new_var = D_800D2EA4;
    fallback = new_var + (i * 8);
    func_80041094(0xB, ((fallback[0] + (fallback[2] >> 1)) << 6) | 0x20, ((fallback[1] + fallback[3]) << 6) | 0x20, 0, D_80082E76 ^ 1);
    D_800D381A = 0;
    return;
  }
  goto loop;
}
