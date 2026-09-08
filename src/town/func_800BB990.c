
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
/* Passes the selected entry's bottom-center coordinates to func_80041094 and clears the selection. */
void func_800B90F0(void)
{
  s32 entry_index = 0x20;
  u8 *selection_state = D_800D3814;
  u8 *shared_state = D_80082E60;
  u8 *entries = D_800D2EA4;
  u8 *entry = entries + 0x100;
  u8 *id_cursor = (u8 *) 0x80010040;
  u8 *fallback_entries;
  u8 *fallback_entry;
  scan_entries:
  entry_index--;

  if (id_cursor[0x33A4] == selection_state[6])
  {
    func_80041094(0xB, ((entry[0] + (entry[2] >> 1)) << 6) | 0x20, ((entry[1] + entry[3]) << 6) | 0x20, 0, (*((u16 *) (&shared_state[0x16]))) ^ 1);
    selection_state[6] = 0;
    return;
  }
  entry -= 8;
  id_cursor -= 2;
  if (entry_index <= 0)
  {
    fallback_entries = D_800D2EA4;
    fallback_entry = fallback_entries + (entry_index * 8);
    func_80041094(0xB, ((fallback_entry[0] + (fallback_entry[2] >> 1)) << 6) | 0x20, ((fallback_entry[1] + fallback_entry[3]) << 6) | 0x20, 0, D_80082E76 ^ 1);
    D_800D381A = 0;
    return;
  }
  goto scan_entries;
}
