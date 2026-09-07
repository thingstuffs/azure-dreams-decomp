
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
typedef struct Rec
{
  u8 pad[0x5c];
  u8 *next;
} Rec;
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A41F0(u8 *);
void *func_8009B4B0(u8 *arg0, s16 arg1, s16 arg2)
{
  u16 sp10;
  u8 *root;
  u16 key1;
  u16 key2;
  key1 = arg1 - 1;
  root = arg0;
  if (((func_8009A350((s16) key1, arg2, 0, &sp10) << 0x10) == 0) || ((sp10 & 0x3300) != 0))
  {
    arg0 = ((Rec *) arg0)->next + 0x20;
    if (arg0 != root)
    {
 do { } while (0);
      key1 = arg1;
      key2 = arg2;
      do
      {
        u8 *item = *((u8 **) (arg0 - 0x14));
        if ((((*((u8 *) (item + 0x24))) == key1) && ((*((u8 *) (item + 0x25))) == key2)) && ((func_800A41F0(arg0) << 0x10) != 0))
        {
          return arg0;
        }
        arg0 = ((Rec *) arg0)->next + 0x20;
      }
      while (arg0 != root);
    }
  }
  return 0;
}
