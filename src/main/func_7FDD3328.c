
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
extern void func_80053DA8();
extern void func_80053DCC();
extern void func_80053DF0();
extern void func_80053E14();
extern void func_80088BD0();
void func_8008A288(Menu *m)
{
  Pad *pad;
  s32 flags;
  s32 delta;
  s32 row;
  s32 val;
  s32 *slot;
  s32 *bp;
  s32 t0;
  s32 *pa;
  s32 *pd;
  s32 *pb;
  s32 *pc;
  s16 *cell;
  s32 r;
  s32 g;
  s32 b;
  s32 sh0;
  s32 chi;
  s32 packed;
  u16 f;
  u16 f2;
  s32 idx;
  s32 tb;
  s32 gc;
  D_80080A84 = 1;
  pad = &D_80083160;
  switch (m->state)
  {
    case 0:
      m->state = ((u16) m->state) + 1;

    case 1:
      if ((func_80053428(m) << 16) == 0)
    {
      return;
    }
      m->timer = 300;
      m->state = ((u16) m->state) + 1;
      return;

    case 2:
      flags = pad->pressed;
      if (flags & 0x1000)
    {
      func_80053DA8(0x502);
      m->row = (m->row + 6) % 7;
    }
    else
      if (flags & 0x4000)
    {
      func_80053DA8(0x502);
      m->row = (m->row + 1) % 7;
    }
    else
      if (flags & 0xA000)
    {
      if (m->row == 0)
      {
        func_80053DA8(0x502);
        f = m->flags;
        if (f & 2)
        {
          f2 = f & 0xFFFD;
        }
        else
        {
          f2 = f | 2;
        }
        m->flags = f2;
      }
    }
      flags = pad->held;
      delta = -8;
      if (!(flags & 0x8000))
    {
      delta = ((flags & 0x2000) != 0) * 8;
    }
      if (delta == 0)
    {
      goto shared;
    }
      row = m->row;
      if (row <= 0)
    {
      goto shared;
    }
      idx = row - 1;
      if (row < 4)
    {
      goto chan;
    }
      if (row >= 7)
    {
      goto shared;
    }
      goto rgb;
      chan:
    bp = D_8008B2F0;

      slot = bp + idx;
      val = *slot + delta;
      *slot = val;
      if (val < 0)
    {
      *slot = 0;
    }
    else
      if (val >= 0x101)
    {
      *slot = 0x100;
    }
      if (idx == 1)
    {
      func_80053DA8(0x516);
    }
      pa = &D_80080A98;
      r = 0x7FFF;
      t0 = D_8008B2F0[0];
      if (t0 < 0x100)
    {
      r = t0 << 7;
    }
      gc = 0x7FFF;
      do
    {
      *pa = r;
    }
    while (0);
      pc = &D_80080A9C;
      t0 = D_8008B2F0[1];
      if (t0 < 0x100)
    {
      gc = t0 << 7;
    }
      *pc = gc;
      pb = &D_80080A94;
      b = 0x7FFF;
      t0 = D_8008B2F0[2];
      if (t0 < 0x100)
    {
      b = t0 << 7;
    }
      *pb = b;
      func_80053DF0(*((s16 *) pa));
      func_80053E14(*((s16 *) pc));
      func_80053DCC(*((s16 *) (&D_80080A94)));
      goto shared;
      rgb:
    idx = m->row - 4;
      cell = (s16 *) ((u32) (idx * 2) + (u32) m);

      val = ((u16) cell[7]) + delta;
      cell[7] = val;
      val = (s16) val;
      if (val < 0)
    {
      cell[7] = 0;
      goto shared;
    }
      if (val >= 0x101)
    {
      cell[7] = 0x100;
    }
      shared:
    if ((pad->held & 9) == 9)
    {
      if (pad->pressed & 2)
      {
        m->shade = (m->shade + 1) & 3;
      }
    }

      if (!(pad->pressed & 0x840))
    {
      return;
    }
      do
    {
      sh0 = (s16) m->shade;
    }
    while (0);
      delta = sh0 << 5;
      idx = ((Gfx *) 0x80010000)->color & 0xFF000000;
      b = 0xFF;
      if (m->red < 0x100)
    {
      b = m->red;
    }
      t0 = m->green;
      g = t0 < 0x100;
      if (g)
    {
      g = t0 << 8;
    }
    else
    {
      g = 0xFF00;
    }
      do
    {
      packed = b + g;
    }
    while (0);
      do
    {
      tb = m->blue;
    }
    while (0);
      if (tb < 0x100)
    {
      idx = idx + (packed + (tb << 16));
    }
    else
    {
      chi = idx + 0xFF0000;
      idx = chi + packed;
    }
      if (((Gfx *) 0x80010000)->shade != delta)
    {
      D_80080A8A = 1;
    }
      if (((Gfx *) 0x80010000)->color != idx)
    {
      D_80080A8A = 1;
    }
      if (m->flags & 2)
    {
      if (((Gfx *) 0x80010000)->flags & 1)
      {
        D_80080A8A = 1;
      }
    }
    else
      if (!(((Gfx *) 0x80010000)->flags & 1))
    {
      D_80080A8A = 1;
    }
      if (D_80080A8A == 1)
    {
      ((Gfx *) 0x80010000)->shade = delta;
      D_800814AC = delta;
      ((Gfx *) 0x80010000)->color = idx;
      D_80081494 = idx;
      if (m->flags & 2)
      {
        ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags & 0xFE;
      }
      else
      {
        ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags | 1;
      }
      D_800814A4 = ((Gfx *) 0x80010000)->flags;
    }
      m->flags = m->flags | 0x8000;
      m->state = ((u16) m->state) + 1;
      return;

    case 3:
      func_80053DA8(0x1200);
      m->f2 = 0;
      m->f4 = 0x10;
      m->state = ((u16) m->state) + 1;

    case 4:
      if ((func_80053604(m) << 16) == 0)
    {
      return;
    }
      func_80088BD0();
      pd = &D_800814A0;
      ((u16 *) m)[-1] |= 0x8000;
      do
    {
      *pd |= 0x8000;
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
