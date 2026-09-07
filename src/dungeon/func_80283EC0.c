
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
extern u8 D_800E3DB0[];
void func_80016EC0(void)
{
  s16 next;
  s16 next2;
  u8 *new_var;
  s16 count;
  s16 count2;
  u8 *record;
  u8 *tail;
  u8 *tail2;
  short index;
  s32 kind;
  record = D_800E3DB0;
  count = 0;
  index = 0;
  kind = 1;
  tail = record + 4;
  do
  {
    next = count + 1;
    count = next;
    *record = kind;
    *((volatile s8 *) (((u8 *) tail) + (-1))) = index;
    index += 1;
    *((volatile s8 *) (((u8 *) tail) + (-3))) = 0;
    *((volatile s8 *) (((u8 *) tail) + (-2))) = 0;
    *((volatile s32 *) (((u8 *) tail) + 0)) = 0;
    tail += 8;
    record += 8;
  }
  while (next < 4);
  count2 = 0;
  kind = 3;
  tail2 = record + 4;
  do
  {
    next2 = count2 + 1;
    count2 = next2;
    *record = kind;
    *((volatile s8 *) (((u8 *) tail2) + (-1))) = index;
    index += 1;
    *((volatile s8 *) (((u8 *) tail2) + (-3))) = 0;
    *((volatile s8 *) (((u8 *) tail2) + (-2))) = 0;
    *((volatile s32 *) (((u8 *) tail2) + 0)) = 0;
    tail2 += 8;
    record += 8;
  }
  while (next2 < 2);
  *((volatile s8 *) (((u8 *) record) + 0)) = 2;
  *((volatile s8 *) (((u8 *) record) + 1)) = 0;
  *((volatile s8 *) (((u8 *) record) + 2)) = 0;
  new_var = record + 4;
  *((volatile s8 *) (((u8 *) record) + 3)) = index;
  *((s32 *) new_var) = 0;
}
