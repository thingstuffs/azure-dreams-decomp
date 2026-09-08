
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
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern u8 D_8002609C[];
extern u8 D_80045340[];
extern u8 D_800F15AC[];
/* Creates a sprite at the given position and applies color-specific settings. */
void func_800252B8(s32 color, s32 x, s32 y, s32 z)
{
  s32 resource_word;
  void *sprite;
  void *sprite_alias;
  void *object;
  object = func_8003FC64(0x136);
  if (object != 0)
  {
    *((M2C_UNK **) (((s8 *) object) + 0x10)) = &D_8002609C;
    func_8004491C(object, &D_80045340);
    sprite = *((void **) (((s8 *) object) + 0xC));
    *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 0)) = x;
    *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 4)) = y;
    *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 8)) = z;
    *((s16 *) (((s8 *) sprite) + 0x1E)) = 0x1000;
    *((s16 *) (((s8 *) sprite) + 0x1C)) = 0x1000;
    *((M2C_UNK **) (((s8 *) sprite) + 0)) = &D_800F15AC;
    resource_word = *((s32 *) (((s8 *) (&D_800F15AC)) + 4));
    *((s8 *) (((s8 *) sprite) + 4)) = 0;
    *((s8 *) (((s8 *) sprite) + 5)) = 0;
    *((s32 *) (((s8 *) sprite) + 0xC)) = color;
    sprite_alias = sprite;
    *((s32 *) (((s8 *) sprite_alias) + 8)) = (s32) resource_word;
    if (color != 0x808080)
    {
      if (color == 0xF0F0F0)
      {
        *((s16 *) (((s8 *) sprite) + 0x10)) = 0x60;
        *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 0x14)) = 0xFFF00000;
        goto enable_flags;
      }
    }
    else
    {
      enable_flags:
      *((u16 *) (((s8 *) sprite) + 0x14)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x14))) | 0xC);

    }
  }
}
