
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
extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand(void);
extern u8 D_80025764[12];
extern u8 D_8002822C[12];
extern u8 D_80045340[12];
extern u8 D_800C95C0[12];
/* Spawn two pairs of effects at random offsets around the source. */
void func_8195A09C(void *source, s16 effect_param, s32 render_param)
{
  s32 remaining;
  void *effect;
  void *effect_data;
  void *render_data;
  remaining = 2;
  do
  {
    effect = func_8003FD64(0x212, source);
    if (effect != 0)
    {
      *((void **) (((u8 *) effect) + 0x10)) = D_80025764;
      func_8004491C(effect, D_80045340);
      effect_data = ((u8 *) effect) + 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
      render_data = *((void **) (((u8 *) effect) + 0xC));
      *((void **) (((u8 *) render_data) + 8)) = D_8002822C;
      *((s16 *) (((u8 *) render_data) + 0x1E)) = 0x1000;
      *((s16 *) (((u8 *) render_data) + 0x1C)) = 0x1000;
      *((s32 *) (((u8 *) render_data) + 0xC)) = render_param;
      *((s16 *) (((u8 *) render_data) + 6)) = 8;
      *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
      *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
    }
    remaining--;
  }
  while (remaining > 0);
  remaining = 2;
  do
  {
    effect = func_8003FD64(0x212, source);
    if (effect != 0)
    {
      *((void **) (((u8 *) effect) + 0x10)) = D_80025764;
      func_8004491C(effect, D_800C95C0);
      effect_data = ((u8 *) effect) + 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 2)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2))) + (rand() & 0x3F)) - 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 6)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6))) + (rand() & 0x3F)) - 0x20;
      *((s16 *) (((u8 *) (*((void **) (((u8 *) effect) + 8)))) + 0xA)) = ((*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA))) + (rand() & 0x3F)) - 0x20;
      *((s16 *) (((u8 *) effect) + 0x20)) = 0x20;
      *((s16 *) (((u8 *) effect_data) + 2)) = 0x20;
      *((s16 *) (((u8 *) effect_data) + 4)) = 1;
      *((s16 *) (((u8 *) effect_data) + 6)) = 0;
      *((s16 *) (((u8 *) effect_data) + 0x36)) = effect_param;
      *((s16 *) (((u8 *) effect_data) + 0x30)) = (rand() & 0xFF) | 0x80;
    }
    remaining--;
  }
  while (remaining > 0);
}
