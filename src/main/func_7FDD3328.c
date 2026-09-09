
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
typedef struct Gfx
{
  u8 pad0[0x3180];
  s32 color;
  u8 shade;
  u8 pad5;
  u8 flags;
  u8 pad7;
} Gfx;
typedef struct Pad
{
  u8 pad0[8];
  s32 held;
  u8 padC[4];
  s32 pressed;
} Pad;
typedef struct Menu
{
  s16 pad0;
  s16 f2;
  s16 f4;
  s16 pad6;
  s16 state;
  s16 timer;
  s16 row;
  s16 red;
  s16 green;
  s16 blue;
  u16 shade;
  u16 flags;
} Menu;
extern Pad D_80083160;
extern u8 D_80080A84;
extern u8 D_80080A8A;
extern s32 D_80080A94;
extern s32 D_80080A98;
extern s32 D_80080A9C;
extern s32 D_8008B2F0[3];
extern s32 D_80081494;
extern s32 D_800814A0;
extern u8 D_800814A4;
extern u8 D_800814AC;
extern s32 func_80053428();
extern s32 func_80053604();
extern void SD_Call();
extern void func_80053DCC();
extern void func_80053DF0();
extern void func_80053E14();
extern void func_80088BD0();
/* Handles the options menu, adjusting audio levels and applying display settings. */
void func_8008A288(Menu *menu)
{
  Pad *pad;
  s32 buttons;
  s32 delta;
  s32 row;
  s32 adjusted_value;
  s32 *level_slot;
  s32 *levels;
  s32 level;
  s32 *volume_a;
  s32 *settings_flags;
  s32 *volume_c;
  s32 *volume_b;
  s16 *color_base;
  s32 scaled_a;
  s32 green_bits;
  s32 volume_or_red;
  s32 shade;
  s32 blue_bits;
  s32 red_green;
  u16 menu_flags;
  u16 new_flags;
  s32 channel_or_color;
  s32 blue;
  s32 scaled_b;
  D_80080A84 = 1;
  pad = &D_80083160;
  switch (menu->state)
  {
    case 0:
      menu->state = ((u16) menu->state) + 1;

    case 1:
      if ((func_80053428(menu) << 16) == 0)
      {
        return;
      }
      menu->timer = 300;
      menu->state = ((u16) menu->state) + 1;
      return;

    case 2:
      buttons = pad->pressed;
      if (buttons & 0x1000)
      {
        SD_Call(0x502);
        menu->row = (menu->row + 6) % 7;
      }
      else if (buttons & 0x4000)
      {
        SD_Call(0x502);
        menu->row = (menu->row + 1) % 7;
      }
      else if (buttons & 0xA000)
      {
        if (menu->row == 0)
        {
          SD_Call(0x502);
          menu_flags = menu->flags;
          if (menu_flags & 2)
          {
            new_flags = menu_flags & 0xFFFD;
          }
          else
          {
            new_flags = menu_flags | 2;
          }
          menu->flags = new_flags;
        }
      }
      buttons = pad->held;
      delta = -8;
      if (!(buttons & 0x8000))
      {
        delta = ((buttons & 0x2000) != 0) * 8;
      }
      if (delta == 0)
      {
        goto check_confirm;
      }
      row = menu->row;
      if (row <= 0)
      {
        goto check_confirm;
      }
      channel_or_color = row - 1;
      if (row < 4)
      {
        goto adjust_volume;
      }
      if (row >= 7)
      {
        goto check_confirm;
      }
      goto adjust_color;
    adjust_volume:
      levels = D_8008B2F0;

      level_slot = levels + channel_or_color;
      adjusted_value = *level_slot + delta;
      *level_slot = adjusted_value;
      if (adjusted_value < 0)
      {
        *level_slot = 0;
      }
      else if (adjusted_value >= 0x101)
      {
        *level_slot = 0x100;
      }
      if (channel_or_color == 1)
      {
        SD_Call(0x516);
      }
      volume_a = &D_80080A98;
      scaled_a = 0x7FFF;
      level = D_8008B2F0[0];
      if (level < 0x100)
      {
        scaled_a = level << 7;
      }
      scaled_b = 0x7FFF;
      do
      {
        *volume_a = scaled_a;
      }
      while (0);
      volume_b = &D_80080A9C;
      level = D_8008B2F0[1];
      if (level < 0x100)
      {
        scaled_b = level << 7;
      }
      *volume_b = scaled_b;
      volume_c = &D_80080A94;
      volume_or_red = 0x7FFF;
      level = D_8008B2F0[2];
      if (level < 0x100)
      {
        volume_or_red = level << 7;
      }
      *volume_c = volume_or_red;
      func_80053DF0(*((s16 *) volume_a));
      func_80053E14(*((s16 *) volume_b));
      func_80053DCC(*((s16 *) (&D_80080A94)));
      goto check_confirm;
    adjust_color:
      channel_or_color = menu->row - 4;
      color_base = (s16 *) ((u32) (channel_or_color * 2) + (u32) menu);

      adjusted_value = ((u16) color_base[7]) + delta;
      color_base[7] = adjusted_value;
      adjusted_value = (s16) adjusted_value;
      if (adjusted_value < 0)
      {
        color_base[7] = 0;
        goto check_confirm;
      }
      if (adjusted_value >= 0x101)
      {
        color_base[7] = 0x100;
      }
    check_confirm:
      if ((pad->held & 9) == 9)
      {
        if (pad->pressed & 2)
        {
          menu->shade = (menu->shade + 1) & 3;
        }
      }

      if (!(pad->pressed & 0x840))
      {
        return;
      }
      do
      {
        shade = (s16) menu->shade;
      }
      while (0);
      delta = shade << 5;
      channel_or_color = ((Gfx *) 0x80010000)->color & 0xFF000000;
      volume_or_red = 0xFF;
      if (menu->red < 0x100)
      {
        volume_or_red = menu->red;
      }
      level = menu->green;
      green_bits = level < 0x100;
      if (green_bits)
      {
        green_bits = level << 8;
      }
      else
      {
        green_bits = 0xFF00;
      }
      do
      {
        red_green = volume_or_red + green_bits;
      }
      while (0);
      do
      {
        blue = menu->blue;
      }
      while (0);
      if (blue < 0x100)
      {
        channel_or_color = channel_or_color + (red_green + (blue << 16));
      }
      else
      {
        blue_bits = channel_or_color + 0xFF0000;
        channel_or_color = blue_bits + red_green;
      }
      if (((Gfx *) 0x80010000)->shade != delta)
      {
        D_80080A8A = 1;
      }
      if (((Gfx *) 0x80010000)->color != channel_or_color)
      {
        D_80080A8A = 1;
      }
      if (menu->flags & 2)
      {
        if (((Gfx *) 0x80010000)->flags & 1)
        {
          D_80080A8A = 1;
        }
      }
      else if (!(((Gfx *) 0x80010000)->flags & 1))
      {
        D_80080A8A = 1;
      }
      if (D_80080A8A == 1)
      {
        ((Gfx *) 0x80010000)->shade = delta;
        D_800814AC = delta;
        ((Gfx *) 0x80010000)->color = channel_or_color;
        D_80081494 = channel_or_color;
        if (menu->flags & 2)
        {
          ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags & 0xFE;
        }
        else
        {
          ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags | 1;
        }
        D_800814A4 = ((Gfx *) 0x80010000)->flags;
      }
      menu->flags = menu->flags | 0x8000;
      menu->state = ((u16) menu->state) + 1;
      return;

    case 3:
      SD_Call(0x1200);
      menu->f2 = 0;
      menu->f4 = 0x10;
      menu->state = ((u16) menu->state) + 1;

    case 4:
      if ((func_80053604(menu) << 16) == 0)
      {
        return;
      }
      func_80088BD0();
      settings_flags = &D_800814A0;
      ((u16 *) menu)[-1] |= 0x8000;
      do
      {
        *settings_flags |= 0x8000;
      }
      while (0);
      if (((Gfx *) 0x80010000)->flags)
      {
        return;
      }
      else
      {
        return;
      }

  }

}
