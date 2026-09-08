
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
extern void *func_8003FC64(s32);
extern void func_800A56E0(s32);
extern u8 D_80083460[12];
extern M2C_UNK D_800D5294;
extern M2C_UNK D_800DECF8[3];
/* Creates a colored effect at the source object's position. */
void func_800D5460(void *source, s32 color, unsigned short event_id)
{
  M2C_UNK *effect_state;
  s32 *color_ptr;
  s32 event_code;
  s32 effect_color;
  void *render_setup;
  void *render_data;
  void *effect_data;
  void *render_params;
  void *effect;
  void *position;
  color_ptr = &color;
  effect = func_8003FC64(0x12);
  if (effect != 0)
  {
    effect_data = effect + 0x20;
    *((void **) (((u8 *) effect_data) + 0x24)) = source;
    *((M2C_UNK **) (((u8 *) effect) + 0x10)) = &D_800D5294;
    *((s16 *) (((u8 *) effect_data) + 0x1E)) = 0x32;
    render_setup = *((void **) (((u8 *) effect) + 0xC));
    *((s16 *) (((u8 *) render_setup) + 0x10)) = 0x20;
    *((u16 *) (((u8 *) render_setup) + 0x14)) = (u16) ((*((u16 *) (((u8 *) render_setup) + 0x14))) | 0xC);
    position = *((void **) (((u8 *) effect) + 8));
    *((u16 *) (((u8 *) position) + 2)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2)));
    *((u16 *) (((u8 *) position) + 6)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6)));
    *((u16 *) (((u8 *) position) + 0xA)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA)));
    render_data = *((void **) (((u8 *) effect) + 0xC));
    *((u8 *) (((u8 *) render_data) + 0xE)) = 0x80;
    *((u8 *) (((u8 *) render_data) + 0xD)) = 0x80;
    *((u8 *) (((u8 *) render_data) + 0xC)) = 0x80;
    effect_color = *color_ptr;
    *((s16 *) (((u8 *) render_data) + 0x1E)) = 0x1000;
    *((s16 *) (((u8 *) render_data) + 0x1C)) = 0x1000;
    *((s32 *) (((u8 *) render_data) + 0xC)) = effect_color;
    *((s32 *) (((u8 *) effect_data) + 0xC)) = effect_color;
    *((s16 *) (((u8 *) render_data) + 0x12)) = 0x7DCE;
    render_params = D_800DECF8;
    *((u16 *) (((u8 *) render_data) + 0x14)) = (u16) ((*((u16 *) (((u8 *) render_data) + 0x14))) | 0x100);
    func_8003DB94(render_data, render_params, 0);
    event_code = event_id & 0xFFFF;
    if (event_code != 0)
    {
      func_800A56E0(event_code);
    }
    effect_state = (M2C_UNK *) D_80083460;
    *((u16 *) (((u8 *) effect_state) + 0xA)) = (u16) ((*((u16 *) (((u8 *) effect_state) + 0xA))) + 1);
  }
}
