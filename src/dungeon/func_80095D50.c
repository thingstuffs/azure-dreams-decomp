
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
/* Finds an eligible entry at the requested coordinates after checking the tile to the left. */
void *func_8009B4B0(u8 *entry, s16 x, s16 y)
{
  u16 tile_flags;
  u8 *list_head;
  u16 tile_x;
  u16 tile_y;
  tile_x = x - 1;
  list_head = entry;
  if (((func_8009A350((s16) tile_x, y, 0, &tile_flags) << 0x10) == 0) || ((tile_flags & 0x3300) != 0))
  {
    entry = ((Rec *) entry)->next + 0x20;
    if (entry != list_head)
    {
      do { } while (0);
      tile_x = x;
      tile_y = y;
      do
      {
        u8 *entry_data = *((u8 **) (entry - 0x14));
        if ((((*((u8 *) (entry_data + 0x24))) == tile_x) && ((*((u8 *) (entry_data + 0x25))) == tile_y)) && ((func_800A41F0(entry) << 0x10) != 0))
        {
          return entry;
        }
        entry = ((Rec *) entry)->next + 0x20;
      }
      while (entry != list_head);
    }
  }
  return 0;
}
