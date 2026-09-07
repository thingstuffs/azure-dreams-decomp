#include "common.h"

typedef struct MapCell {
    s16 kind;
    u16 value;
    s16 flags;
} MapCell;

typedef struct DungeonCfg {
    MapCell *cells;
    u8 pad04[16];
    s16 shift_x;
    s16 shift_y;
    s16 mask_x;
    s16 mask_y;
    s16 span_x;
    s16 span_y;
} DungeonCfg;

typedef struct Room {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    s16 tint;
    s16 active;
    u16 link;
    u8 pad0E[2];
    u8 *tiles;
} Room;

typedef struct Pair {
    u8 a;
    u8 b;
} Pair;

extern DungeonCfg D_8008333C;
extern MapCell D_800EA000[];
extern Room D_800E2970[];
extern s16 D_80081468[];
extern s32 D_8001F660;
extern s32 D_8001F664;
extern s16 D_8001F668;
extern u16 D_8001F66A;
extern Pair D_8001F6A8[];

extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, u16);
extern s16 func_80017584(s16, s16, s16, s16);
extern void func_80017668(s16, s16, s16, s16, u16);
extern void func_80017530(void);
extern void func_80017560(void);
extern void func_800176EC(void);
extern void func_80019A84(s16);
extern void func_8001A710(void);
extern s16 func_8001A768(s16 *, s16, s16, s8 *, s32 *, s32, s32);
extern s16 func_8001AC4C(s16, s16, s32, s16, s8 *);
extern void func_8001CE44(Room *, s16);
extern void func_8001DC34(Room *);
extern void func_8001DE2C(void);

s32 func_80019AF8(void)
{
  s8 flags[16];
  s32 conn[16];
  s16 dirv;
  s16 ox;
  s16 oy;
  s32 tries;
  s16 *hdr;
  u8 *bp;
  int new_var;
  s32 j;
  s32 jr;
  s32 i;
  s32 k;
  s32 ks;
  s32 n;
  s32 nt;
  s32 next;
  s32 rnd;
  s32 dir;
  s32 dw;
  s32 *cn;
  Room *dc;
  Room *rp;
  s32 rh;
  s32 x0;
  s32 y0;
  s32 x1;
  s32 y1;
  dc = (Room *) &D_8008333C;
  j = 0;
  tries = 1024;
  rnd = func_800A6D30();
  if ((rnd & 0x7F) == 0)
  {
    D_8001F660 = 2;
  }
  else
    if ((rnd & 0x1F) == 0)
  {
    D_8001F660 = 3;
  }
  else
  {
    D_8001F660 = 4;
  }
  rnd = func_800A6D30();
  if ((rnd & 0x7F) == 0)
  {
    D_8001F664 = 2;
  }
  else
    if ((rnd & 0x1F) == 0)
  {
    D_8001F664 = 3;
  }
  else
  {
    D_8001F664 = 4;
  }
  for (i = 32; i > 0; i--)
  {
    D_8001F6A8[i].b = 0;
    D_8001F6A8[i].a = 0;
  }

  D_8001F668 = 0;
  if (((s16) func_800A6DA4(0, 512)) < 2)
  {
    j = 1;
  }
  else
  {
    oy = (D_8001F664 * D_8001F660) - 1;
    k = 0;
    while (oy >= 0)
    {
      flags[k] = (func_800A6D30() & 3) != 0;
      oy--;
      conn[k] = 0;
      k++;
    }

    for (oy = 0; oy < D_8001F664; oy++)
    {
      for (ox = 0; ox < D_8001F660; ox++)
      {
        k = (oy * D_8001F660) + ox;
        if (flags[k] > 0)
        {
          s32 rx;
          s32 ry;
          rx = func_800A6DA4(0, ((64 / D_8001F660) / 2) - 1) + (ox * (64 / D_8001F660));
          ry = func_800A6DA4(0, ((64 / D_8001F664) / 2) - 1) + (oy * (64 / D_8001F664));
          dw = func_800A6DA4(0, ((64 / D_8001F660) / 2) - 1);
          jr = func_800A6DA4(0, ((64 / D_8001F664) / 2) - 1) + 5;
          rh = jr;
          do { } while (0);
          if (((s16) jr) < 5)
          {
            rh = 5;
          }
          x0 = (s16) (rx - 2);
          y0 = (s16) (ry - 2);
          x1 = (s16) (dw + 9);
          y1 = (s16) (rh + 4);
          if (func_80017584(x0, y0, x1, y1) == 0)
          {
            D_800E2970[k].active = 1;
            func_80017668(x0, y0, x1, y1, k + 1);
            D_800E2970[k].x = rx + 1;
            D_800E2970[k].y = ry + 1;
            D_800E2970[k].w = dw + 3;
            D_800E2970[k].h = rh - 2;
            D_800E2970[k].tint = func_800A6D30() & 0x60;
            j++;
            flags[k] = 2;
            conn[k] += 0x01010101;
          }
          else
          {
            s32 sy;
            s32 sx;
            flags[k] = 0;
            sx = ((ox * (64 / D_8001F660)) + (func_800A6D30() & 7)) + 6;
            sy = (oy * (64 / D_8001F664)) + (func_800A6D30() & 7);
            sy = sy + 6;
            D_800E2970[k].x = sx;
            D_800E2970[k].y = sy;
            D_800EA000[(((s16) sy) << ((DungeonCfg *) dc)->shift_x) + ((s16) sx)].value = func_800A6D30() & 0x60;
          }
        }
        else
        {
          s32 sy;
          s32 sx;
          sx = ((ox * (64 / D_8001F660)) + (func_800A6D30() & 7)) + 6;
          sy = (oy * (64 / D_8001F664)) + (func_800A6D30() & 7);
          sy = sy + 6;
          D_800E2970[k].x = sx;
          D_800E2970[k].y = sy;
          D_800EA000[(((s16) sy) << ((DungeonCfg *) dc)->shift_x) + ((s16) sx)].value = func_800A6D30() & 0x60;
        }
      }

    }

  }
  func_80017560();
  hdr = D_80081468;
  hdr[3] = j;
  if (((s16) j) < 2)
  {
    hdr[3] = 1;
    D_800E2970[0].x = 2;
    D_800E2970[0].y = 2;
    new_var = 1 << ((DungeonCfg *) dc)->shift_y;
    D_800E2970[0].active = 1;
    D_800E2970[0].w = (1 << ((DungeonCfg *) dc)->shift_x) - 4;
    D_800E2970[0].h = new_var - 4;
    D_800E2970[0].tint = func_800A6D30() & 0x60;
    func_8001CE44(&D_800E2970[0], 0);
  }
  else
  {
    Room *room;
    s32 x;
    for (oy = 0; oy < D_8001F664; oy++)
    {
      for (ox = 0; ox < D_8001F660; ox++)
      {
        k = (oy * D_8001F660) + ox;
        if (D_800E2970[k].active != 0)
        {
          func_8001CE44(&D_800E2970[k], k);
        }
      }

    }

    func_80019A84(16384);
    k = (func_800A6D30() & 0xFFFF) % (D_8001F664 * D_8001F660);
    dir = func_800A6D30() & 6;
    rp = D_800E2970;
    do
    {
      n = D_8001F664 * D_8001F660;
      if (n <= 0)
      {
        goto tally;
      }
      i = 0;
      do
      {
        if ((flags[k] > 0) && (rp[k].active != 0))
        {
          goto srch;
        }
        k++;
        k = k % n;
        i++;
      }
      while (i < n);
      srch:
      if (i >= (D_8001F664 * D_8001F660))
      {
        goto tally;
      }
      i = 4;
      oy = k / D_8001F660;
      ox = k % D_8001F660;
      next = k;
      x = k << 2;
      cn = conn;
      j = ((s32) cn) + x;
      ks = (s16) k;
      room = (Room *) ((((x + k) << 2)) + ((s32) rp));
      do
      {
        rh = (s16) dir;
        bp = (u8 *) (j + (((u32) (dir << 16)) >> 17));
        if ((*bp) != 0)
        {
          dirv = dir;
          func_8001A710();
          next = func_8001A768(&dirv, ox, oy, flags, cn, 1, ks);
          if (next >= 0)
          {
            u8 *bq;
            s32 idx;
            if (func_8001AC4C(rh, dirv, ks, next, flags) != 0)
            {
              return 1;
            }
            bq = (u8 *) (&cn[next]);
            (*bp)--;
            bq[((dirv + 4) & 7) >> 1]--;
            x0 = (s32) (&D_8001F668);
            idx = ((s16 *) x0)[0];
            room->link = 1;
            rp[next].link = 1;
            do { } while (0);
            ASM_USE_NV(k);
            n = (s32) D_8001F6A8;
            ((Pair *) n)[idx].a = k;
            ((Pair *) n)[((s16 *) x0)[0]].b = next;
            ((s16 *) x0)[0]++;
            break;
          }
        }
        i--;
        dir = (dir + 2) & 6;
      }
      while (i > 0);
      if (i <= 0)
      {
        n = D_8001F664 * D_8001F660;
        j = (k + 1) % n;
        for (i = 0; i < n; i++)
        {
          if ((rp[j].link != 0) && (flags[j] > 0))
          {
            break;
          }
          j++;
          j = j % n;
        }

        next = j;
      }
      else
      {
        dir = (((u16) dirv) + 2) & 7;
        flags[k]--;
        if (flags[k] <= 0)
        {
          flags[k] = -1;
        }
      }
      k = next;
      tries--;
      if (tries < 0)
      {
        i = (D_8001F664 * D_8001F660) - 1;
        break;
      }
    }
    while (1);
    for (; i >= 0; i--)
    {
      if ((rp[i].link == 0) && (rp[i].active != 0))
      {
        func_8001DC34(&rp[i]);
      }
    }

    tally:
    D_8001F66A = 0;

    nt = D_8001F664 * D_8001F660;
    for (i = 0; i < nt; i++)
    {
      if ((D_800E2970[i].link == 0) && (D_800E2970[i].active != 0))
      {
        D_8001F66A++;
      }
    }

  }
  rnd = jr;
  func_800176EC();
  func_80017530();
  func_8001DE2C();
  return 0;
}
