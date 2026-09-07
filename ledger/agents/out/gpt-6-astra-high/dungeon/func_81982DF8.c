
struct S_80083178Vector
{
  short x;
  short y;
  short z;
  short pad;
};
struct S_80083178State
{
  struct S_80083178Vector v[4];
};
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94 - 0xC];
  struct S_80083178State state_94;
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
extern struct S_80083178State D_80083CE8;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
typedef struct 
{
  s32 f0;
  s32 f4;
  s32 f8;
  s32 fc;
  s32 f10;
  s32 f14;
} Arg1;
typedef struct 
{
  u8 pad0[0xC];
  u8 c;
  u8 d;
  u8 e;
  u8 padF[0xD];
  u16 f1c;
  u16 f1e;
} Arg2;
extern u16 D_800269F8[5];
extern s32 D_800814A0[3];
/* Move, fade, and expand the effect, marking it finished when its timer expires. */
void func_800245F8(void *effect_data, void *motion_data, void *sprite_data)
{
  Arg2 *sprite = (Arg2 *) sprite_data;
  void *effect = effect_data;
  Arg1 *motion = (Arg1 *) motion_data;
  s16 frames_left;
  s32 next_x;
  u16 scale;
  u16 count_or_scale;
  int zero;
  u8 brightness;
  u8 faded_brightness;
  count_or_scale = D_800269F8[0] + 1;
  next_x = motion->f0 + motion->fc;
  D_800269F8[0] = (u16) count_or_scale;
  motion->f0 = next_x;
  zero = 0;
  motion->f4 = motion->f4 + motion->f10;
  motion->f8 = motion->f8 + motion->f14;
  motion->f14 = motion->f14 + 0xC000;
  func_800478B8(sprite);
  brightness = sprite->c;
  faded_brightness = brightness - (((s32) brightness) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
  sprite->c = faded_brightness;
  sprite->d = faded_brightness;
  sprite->e = faded_brightness;
  scale = sprite->f1c;
  count_or_scale = scale + (((s32) (0x400 - scale)) / ((s16) (*((s16 *) (((s8 *) effect) + 0x30)))));
  sprite->f1c = count_or_scale;
  sprite->f1e = count_or_scale;
  frames_left = ((u16) (*((s16 *) (((s8 *) effect) + 0x30)))) - 1;
  *((s16 *) (((s8 *) effect) + 0x30)) = frames_left;
  if ((frames_left << 0x10) <= zero)
  {
    *((u16 *) (((s8 *) effect) + (-2))) = (u16) ((*((u16 *) (((s8 *) effect) + (-2)))) | 0x8000);
    D_800814A0[zero] = (s32) (D_800814A0[0] | 0x8000);
  }
}
