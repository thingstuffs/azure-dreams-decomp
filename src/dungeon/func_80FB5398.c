#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedS32;

typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) PackedPair;

typedef struct {
    s16 screen[2];
    s32 outer;
} Scratch;

typedef struct {
    void *vertices;
    void *output;
    s16 pad08;
    s16 pad0A;
    s16 z;
    s16 pad0E;
    PackedPair v10;
    s16 count;
    s16 pad1A;
    s32 pad1C;
} Projection;

extern u8 D_8017089C[];
extern u8 D_80083160[];
extern u8 D_801C9E40[];

extern void func_800DBA90(void *);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_800644B8(s32);
extern void func_800666F4(void *);
extern void func_80066640(void *, s32);
extern s32 func_80066460(s32, s32, s32, s32);

s32 func_80174B98(void *arg0, void *arg1, void *arg2)
{
  s16 bounds[4];
  PackedPair material;
  Vertex vertices[4];
  Projection proj;
  Scratch sc;
  void *obj;
  Projection *pp;
  s32 end;
  s32 start;
  s32 depth;
  Vertex *vbase;
  s32 tile_count;
  s32 bucket_off;
  u8 *p16;
  s32 i;
  s32 xb;
  s32 yb;
  register s32 r20 ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
  s32 limit;
  register s32 tile_w;
  register s32 tag_mask ASM_REG("$23");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
  register s32 sub_off;
  u8 *gp;
  (void) arg1;
  gp = D_80083160;
  material = *((PackedPair *) D_8017089C);
  depth = 0;
  vbase = vertices;
  for (;;)
  {
    s32 xv;
    s32 xn;
    s32 zn;
    s32 zp;
    register Vertex *vp ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 zval;
    s16 miny;
    s16 maxy;
    s16 base_y;
    s16 height;
    s16 row0;
    s32 r0s;
    s32 h16;
    s32 h16b;
    s32 bound_base;
    s32 bound_limit;
    s32 b16;
    s32 prod;
    s32 q2;
    void *next;
    sc.outer = 48;
    xv = (u16) sc.outer;
    i = 3;
    zn = -160;
    obj = arg0;
    ASM_USE_NV(obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    zp = 16;
    xn = -xv;
    vp = vbase + 3;
    ASM_KEEP4(vp, xv, xn, i);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(zn);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP_NV(zp);   /* MATCH pin: keeps a statement from moving across a call/branch */
    do
    {
      vp->x = xv;
      if (i < 2)
      {
        vp->x = xn;
      }
      vp->y = 0;
      if (i & 1)
      {
        vp->z = zn;
      }
      else
      {
        vp->z = zp;
      }
      i--;
      vp--;
    }
    while (i >= 0);
    pp = &proj;
    ASM_KEEP4_NV(pp, pp, pp, pp);   /* MATCH pin: retail schedule: same instructions, different order without it */
    xb &= 0xFFFF;
    yb &= 0xFFFF;
    i = 3;
    zval = *((u16 *) (((u8 *) gp) + 0xC8));
    proj.pad0A = 0;
    proj.pad08 = 0;
    r20 = (s32) (&sc.outer);
    p16 = ((u8 *) vbase) + 24;
    proj.vertices = vbase;
    proj.output = vbase;
    ASM_KEEP_MEM_NV(zval, proj);   /* MATCH pin: keeps a statement from moving across a call/branch */
    proj.z = -zval;
    proj.v10 = *((PackedPair *) (((u8 *) obj) + 0xA2));
    proj.count = 4;
    proj.pad1A = 0;
    func_800DBA90(pp);
    xb |= 0x75300000;
    xb &= 0xFFFF0000;
    xb |= 0x7530;
    yb |= 0x8AD00000;
    yb &= 0xFFFF0000;
    yb |= 0x8AD0;
    do
    {
      s32 projected;
      s32 sx;
      u16 usx;
      s32 sy;
      u16 usy;
      projected = func_80065420(p16, sc.screen, (void *) r20, (void *) r20);
      depth += projected - 8;
      usx = (u16) sc.screen[0];
      sx = sc.screen[0];
      if (((s16) yb) < sx)
      {
        yb &= 0xFFFF0000;
        yb = usx | yb;
      }
      else
        if (sx < ((s16) xb))
      {
        xb &= 0xFFFF0000;
        xb = usx | xb;
      }
      sy = sc.screen[1];
      usy = (u16) sc.screen[1];
      if (((s16) (yb >> 16)) < sy)
      {
        yb &= 0xFFFF;
        yb |= usy << 16;
      }
      else
        if (sy < ((s16) (xb >> 16)))
      {
        xb &= 0xFFFF;
        xb |= usy << 16;
      }
      i--;
      p16 -= 8;
    }
    while (i >= 0);
    h16 = (s16) xb;
    base_y = (s16) (xb >> 16);
    miny = base_y;
    bounds[2] = (s16) (yb - xb);
    bounds[0] = h16;
    depth = depth >> 2;
    if ((*((u8 **) gp)) != D_801C9E40)
    {
      ASM_KEEP_NV(base_y);   /* MATCH pin: load-bearing for the whole function shape */
      base_y += 0xE0;
    }
    maxy = (s16) (yb >> 16);
    height = maxy - miny;
    bounds[1] = base_y;
    bounds[3] = height;
    if (((u32) depth) < 0x1E0U)
    {
      sub_off = (*((s16 *) (((u8 *) obj) + 0x96))) - 0x34;
      if (sub_off < 0)
      {
        sub_off = 0;
      }
      h16b = (s16) height;
      prod = h16b * sub_off;
      sub_off = prod / 8;
      bound_base = (s16) base_y;
      bound_limit = bound_base + h16b;
      b16 = bound_base;
      limit = bound_limit;
      row0 = bound_base / 0xE0;
      r0s = row0;
      if ((r0s != row0) && (limit != bound_limit))
      {
        q2 = 0;
      }
      q2 = bound_limit / 0xE0;
      end = limit;
      if (r0s != q2)
      {
        limit = q2 * 0xE0;
      }
      sc.outer = 4;
      tag_mask = 0x00FFFFFF;
      bucket_off = depth << 2;
      do
      {
        s32 ov;
        s32 tmp;
        ov = sc.outer;
        tmp = (*((s16 *) (((u8 *) obj) + 0x96))) + ov;
        r20 = tmp << 7;
        if (!(ov & 1))
        {
          r20 += 0x800;
        }
        tmp = bounds[1];
                i = tmp + sub_off;
        start = i;
        if (limit >= i)
        {
          tile_w = end - i;
          tile_count = tile_w + 1;
          do
          {
            u8 *base;
            u8 *bucket;
            s32 itmp;
            s32 sh4;
            s32 mb;
            s32 w;
            s32 step;
            s32 u;
            s32 v;
            s32 sine;
            s32 old_tag;
            s32 old_tag2;
            sh4 = sc.outer << 2;
            itmp = r20 + 80;
            ASM_USE2_NV(r20, itmp);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_KEEP4_NV(sh4, sh4, sh4, sh4);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            r20 = itmp + sh4;
            base = *((u8 **) gp);
            p16 = *((u8 **) (base + 0x8D0));
            *((u8 **) (base + 0x8D0)) = p16 + 40;
            *((s32 *) (((u8 *) p16) + 4)) = *((s32 *) (((u8 *) arg2) + 0xC));
            func_800666F4(p16);
            func_80066640(p16, 1);
            *((s16 *) (((u8 *) p16) + 0x16)) = (s16) func_80066460(2, ((u8 *) arg2)[0xC] != 0x80, 0x340, 0x100);
            *((u8 *) (((u8 *) p16) + 0x14)) = 0;
            *((u8 *) (((u8 *) p16) + 0x0C)) = 0;
            mb = ((u8 *) (&material))[4];
            *((s16 *) (((u8 *) p16) + 8)) = (s16) tile_w;
            *((u8 *) (((u8 *) p16) + 0x24)) = mb;
            *((u8 *) (((u8 *) p16) + 0x1C)) = mb;
            if (((s16) tile_w) == 0)
            {
              *((u16 *) (((u8 *) p16) + 8)) = (u16) tile_count;
            }
            step = ((s16 *) (&material))[3] * (i - start);
            step = step / (*((s16 *) (((u8 *) p16) + 8)));
            *((u8 *) (((u8 *) p16) + 0x1D)) = (u8) step;
            *((u8 *) (((u8 *) p16) + 0x0D)) = (u8) step;
            step = ((s16 *) (&material))[3] / (*((s16 *) (((u8 *) p16) + 8)));
            u = *((u8 *) (((u8 *) p16) + 0x0D));
            *((u8 *) (((u8 *) p16) + 0x25)) = (u8) step;
            if (((u8) step) >= 2)
            {
              v = u + (*((u8 *) (((u8 *) p16) + 0x25)));
            }
            else
            {
              v = u + 2;
            }
            *((u8 *) (((u8 *) p16) + 0x25)) = (u8) v;
            *((u8 *) (((u8 *) p16) + 0x15)) = (u8) v;
            sine = func_800644B8(r20);
            sine = ((u16) bounds[0]) + (sine >> 9);
            *((s16 *) (((u8 *) p16) + 0x10)) = (s16) sine;
            *((s16 *) (((u8 *) p16) + 8)) = (s16) sine;
            sine = sine + ((u16) bounds[2]);
            *((s16 *) (((u8 *) p16) + 0x20)) = (s16) sine;
            *((s16 *) (((u8 *) p16) + 0x18)) = (s16) sine;
            w = i - ((i / 0xE0) * 0xE0);
            i++;
            w = w - ((u16) sc.outer);
            *((s16 *) (((u8 *) p16) + 0x1A)) = (s16) w;
            *((s16 *) (((u8 *) p16) + 0x0A)) = (s16) w;
            w += 2;
            *((s16 *) (((u8 *) p16) + 0x22)) = (s16) w;
            *((s16 *) (((u8 *) p16) + 0x12)) = (s16) w;
            old_tag = *((s32 *) ((u8 *) (bucket_off + ((s32) (*((u8 **) gp)))) + 0xB0));
            *((s32 *) (((u8 *) p16) + 0)) = ((*((s32 *) (((u8 *) p16) + 0))) & 0xFF000000) | (old_tag & tag_mask);
            bucket = (u8 *) (bucket_off + ((s32) (*((u8 **) gp))));
            old_tag2 = *((s32 *) (((u8 *) bucket) + 0xB0));
            *((s32 *) (((u8 *) bucket) + 0xB0)) = (old_tag2 & 0xFF000000) | (((s32) p16) & tag_mask);
          }
          while (limit >= i);
        }
      }
      while ((--sc.outer) > 0);
    }
    next = *((void **) (((u8 *) arg0) - 8));
    if (next == 0)
    {
      break;
    }
    arg0 = ((u8 *) next) + 0x20;
    arg2 = *((void **) (((u8 *) next) + 0xC));
  }

  return 0;
}
