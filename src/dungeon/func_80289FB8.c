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
typedef s8 M2C_UNK8;
extern s32 D_800E296C[3];
extern u8 D_800E3648[];
s32 func_800A6D30(void *, s32, s32, s32);
s32 func_800A6DA4();
extern u8 D_800E39C8[];
/* Initializes a free slot at a random position within the room. */
void func_8001CFB8(void *room, s32 rng_arg1, s32 rng_arg2, s32 rng_arg3)
{
  u8 *slot_data;
  s16 raw_size;
  s16 size;
  s32 room_area;
  s32 random_bonus;
  s32 x_offset;
  s32 y_roll;
  s32 slot_index;
  int y_offset;
  u8 *slot_info;
  if (!((*D_800E296C) & 0x10000000))
  {
    random_bonus = func_800A6D30(room, rng_arg1, rng_arg2, rng_arg3) & 7;
    room_area = (*((u16 *) (((s8 *) room) + 6))) * (*((u16 *) (((s8 *) room) + 4)));
    raw_size = (room_area >> 2) + random_bonus;
    size = raw_size;
    if (raw_size >= 0x1D)
    {
      size = 0x1C;
    }
    slot_index = 0;
    slot_info = D_800E3648;
    slot_data = &D_800E39C8;
    check_slot:
    if ((*((u8 *) (((s8 *) slot_info) + 1))) == 0)
    {
      x_offset = func_800A6DA4(0, ((*((u16 *) (((s8 *) room) + 4))) - 1) & 0xFFFF, room_area) & 0xFFFF;
      y_roll = func_800A6DA4(0, ((*((u16 *) (((s8 *) room) + 6))) - 1) & 0xFFFF);
      y_offset = y_roll & 0xFFFF;
      *((s8 *) (((s8 *) slot_data) + 6)) = (s8) ((*((u8 *) (((s8 *) room) + 0))) + x_offset);
      *((s8 *) (((s8 *) slot_data) + 7)) = (s8) ((*((u8 *) (((s8 *) room) + 2))) + y_offset);
      *((u8 *) (((s8 *) slot_info) + 0)) = 0x13;
      *((u8 *) (((s8 *) slot_info) + 1)) = 0x15U;
      *((u8 *) (((s8 *) slot_info) + 3)) = (u8) 0xC0;
      *((s8 *) (((s8 *) slot_info) + 2)) = (s8) size;
      *((s32 *) (((s8 *) slot_data) + 8)) = 0;
      return;
    }
    slot_index += 1;
    slot_info += 4;
    slot_data += 0x18;
    if (slot_index >= 0x20)
    {
    }
    else
    {
      goto check_slot;
    }
  }
}
