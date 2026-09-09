
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
extern s32 func_800C2B6C(s16 arg0);
extern u8 D_80082660;
extern s32 D_80082A38[];
/* player_now_ang_get: Store the current player angle when the player slot is available. */
void player_now_ang_get(void)
{
  u8 *player_slot;
  void *player;
  s32 *script_values;
  s32 player_angle;
  int slot_index;
  slot_index = 8;
  script_values = D_80082A38;
  player_slot = (&D_80082660) + slot_index;
  if ((*((s8 *) (player_slot + 1))) == 0)
  {
    player = *((void **) (player_slot + 4));
    if (player != 0)
    {
      slot_index = 0x12;
      player_angle = func_800C2B6C(*((s16 *) (((u8 *) player) + 0x30)));
      script_values[slot_index] = player_angle;
    }
  }
}
