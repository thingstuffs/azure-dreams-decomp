
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
typedef s32 M2C_UNK;
extern void *func_8003FD64();
extern M2C_UNK D_800240F0;
extern M2C_UNK D_80083498;
/* Allocate an effect and initialize its state and sprite. */
void func_80024494(s32 effect_data, s32 effect_param, s32 render_param)
{
  int color;
  void *effect;
  void *state;
  void *sprite;
  effect = func_8003FD64(0x12, &D_80083498);
  if (effect != 0)
  {
    *((M2C_UNK **) (((s8 *) effect) + 0x10)) = &D_800240F0;
    color = 0x80;
    state = effect + 0x20;
    *((s16 *) (((s8 *) state) + 0xC)) = 0;
    *((s16 *) (((s8 *) state) + 0xE)) = 0;
    *((s32 *) (((s8 *) effect) + 0x20)) = effect_data;
    *((M2C_UNK **) (((s8 *) state) + 4)) = &D_80083498;
    *((s32 *) (((s8 *) state) + 8)) = effect_param;
    sprite = *((void **) (((s8 *) effect) + 0xC));
    *((s8 *) (((s8 *) sprite) + 0xE)) = color;
    *((s8 *) (((s8 *) sprite) + 0xD)) = color;
    *((s8 *) (((s8 *) sprite) + 0xC)) = color;
    *((s16 *) (((s8 *) sprite) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) sprite) + 0x1C)) = 0x1000;
    *((s16 *) (((s8 *) sprite) + 0x12)) = 0x7E00;
    *((s32 *) (((s8 *) sprite) + 8)) = render_param;
    *((u16 *) (((s8 *) sprite) + 0x10)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x10))) | 0x20);
    *((u16 *) (((s8 *) sprite) + 0x14)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x14))) | 0x10C);
  }
}
