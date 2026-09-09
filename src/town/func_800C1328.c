
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
extern void func_8006733C(void *arg0, void *arg1);
extern void func_80067014(s32 arg0);
extern void func_800673A0(void *arg0, s32 arg1, s32 arg2);
extern u8 D_800D231C[];
extern u8 D_800D2324[];
extern u8 D_80113138[];
/* pool_clut_store: Store the pool CLUT and update its transfer region. */
void pool_clut_store(void)
{
 do { func_8006733C(D_800D231C, D_80113138); func_80067014(0); func_800673A0(D_800D2324, 0x60, 0x1FA); } while (0);
}
