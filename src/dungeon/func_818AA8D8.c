
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
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern s32 D_80045340;
extern s32 D_800814A0;
extern M2C_UNK D_800DECF8;
/* Updates a rotating effect through movement, fading, and deactivation. */
void func_800240D8(void *effect, void *position, void *sprite)
{
  s32 quarter_turn;
  s32 rand_value;
  s32 rounded_random;
  s32 z_upper;
  s32 scale;
  s32 brightness;
  u16 state;
  void *owner;
  owner = *((void **) (((u8 *) effect) + 0));
  *(u16 *)((u8 *) owner + 0x14) = (*(u16 *)((u8 *) owner + 0x14)) + 1;
  *(u16 *)((u8 *) effect + 0x36) = (*(u16 *)((u8 *) effect + 0x36)) + 1;
  *(u16 *)((u8 *) sprite + 0x1A) = (*(u16 *)((u8 *) sprite + 0x1A)) + 0x10;
  *(u16 *)((u8 *) sprite + 0x1A) = (*(volatile u16 *)((u8 *) sprite + 0x1A)) & 0xFFF;
  switch (*(s16 *)((u8 *) effect + 0x34))
  {
    case 0:
      if ((*(s16 *)((u8 *) effect + 0x36)) < (*(s16 *)((u8 *) effect + 0x38)))
      {
        break;
      }
      state = *(u16 *)((u8 *) effect + 0x34);
      *(u16 *)((u8 *) effect + 0x36) = 0;
      state++;
      *(u16 *)((u8 *) effect + 0x34) = state;
      func_8004491C(((u8 *) effect) - 0x20, &D_80045340);
      return;

    case 1:
      quarter_turn = 0x400;
      *(s32 *)((u8 *) position + 0) =
          (*(s32 *)((u8 *) effect + 4))
          + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
              * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
          * ((*(s32 *)((u8 *) effect + 0x28)) >> 8));
      *(s32 *)((u8 *) position + 4) =
          (*(s32 *)((u8 *) effect + 8))
          + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
              * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
          * ((*(s32 *)((u8 *) effect + 0x2C)) >> 8));
      *(s32 *)((u8 *) position + 8) =
          (*(s32 *)((u8 *) effect + 0xC))
          + ((func_800644B8((quarter_turn / (*(s16 *)((u8 *) effect + 0x3A)))
              * (*(s16 *)((u8 *) effect + 0x36))) >> 4)
          * ((*(s32 *)((u8 *) effect + 0x30)) >> 8));
      if ((*(s16 *)((u8 *) effect + 0x36)) < (*(s16 *)((u8 *) effect + 0x3A)))
      {
        break;
      }
      state = *(u16 *)((u8 *) effect + 0x34);
      *(u16 *)((u8 *) effect + 0x36) = 0;
      state++;
      *(u16 *)((u8 *) effect + 0x34) = state;
      return;

    case 2:
      rand_value = rand();
      z_upper = (*(u16 *)((u8 *) position + 0xA)) - 1;
      rounded_random = rand_value;
      if (rand_value < 0)
      {
        rounded_random = rand_value + 3;
      }
      *(u16 *)((u8 *) position + 0xA) = z_upper - (rand_value - ((rounded_random >> 2) << 2));

    case 3:
      *(u8 *)((u8 *) sprite + 0xE) = (brightness = (*(u8 *)((u8 *) sprite + 0xE)) - 8);
      scale = (*(u16 *)((u8 *) sprite + 0x1E)) + 0x100;
      *(u16 *)((u8 *) sprite + 0x1E) = scale;
      *(u16 *)((u8 *) sprite + 0x1C) = scale;
      *(u8 *)((u8 *) sprite + 0xD) = brightness;
      *(u8 *)((u8 *) sprite + 0xC) = brightness;
      if (((u16) scale) < 0x1801U)
      {
        break;
      }
      *(u16 *)((u8 *) effect + 0x34) = (*(u16 *)((u8 *) effect + 0x34)) + 1;
      *(u8 *)((u8 *) sprite + 0xE) = 0x80;
      *(u8 *)((u8 *) sprite + 0xD) = 0x80;
      *(u8 *)((u8 *) sprite + 0xC) = 0x80;
      *(u16 *)((u8 *) sprite + 0x1E) = 0x1000;
      *(u16 *)((u8 *) sprite + 0x1C) = 0x1000;
      *(u16 *)((u8 *) sprite + 0x10) |= 0x20;
      func_8003DB94(sprite, &D_800DECF8, 0);
      return;

    case 4:
      func_800478B8(sprite);
      if (!((*(u16 *)((u8 *) sprite + 0x14)) & 0x6000))
      {
        break;
      }
      goto deactivate;

    default:
    deactivate:
      *(u16 *)((u8 *) effect + (-2)) |= 0x8000;
      D_800814A0 |= 0x8000;
      break;
  }
}
