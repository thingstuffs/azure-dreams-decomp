#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Actor {
    u8 pad00[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x0A];
    u16 field2a;
    u8 pad2c[0x5C];
    s16 coord88;
    u8 pad8a[0x0E];
    u16 status98;
} Actor;

typedef struct Entity {
    u8 pad00[0x24];
    u8 x;
    u8 y;
} Entity;

extern s16 func_80042900();
extern void func_8009A350();
extern s32 func_8009A540();
extern s16 func_8009FD40();
extern u16 func_800A0818();
extern s32 func_800A35D8();
extern u16 func_800A365C();
extern s32 func_800A6D30();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_8006DE24[];
extern u8 D_80082E80[];
extern u16 D_8008347E;

s16 func_800A384C(Actor *arg0, Actor *arg1, u16 *arg2, s32 arg3)
{
  s16 sp18;
  s32 sp1C;
  s16 sp20;
  s16 sp28;
  u16 sp30;
  register Actor *actor0 ASM_REG("$17");
  Entity *entity0;
  register Entity *entity1 ASM_REG("$16");
  u8 *record;
  u8 record_id;
  s32 kind;
  s32 kind_id;
  s32 mask;
  s32 distance;
  s16 result;
  register s16 rotation ASM_REG("$21");
  s16 blocked;
  register s32 rot_raw ASM_REG("$3");
  register s32 rot3 ASM_REG("$3");
  s32 rotsx;
  register s32 recoff ASM_REG("$3");
  register s16 steps ASM_REG("$18");
  s16 next_steps;
  s16 x;
  s16 y;
  s32 delta;
  register s32 c0 ASM_REG("$2");
  s32 value;
  s32 new_var;
  s32 flags;
  s32 flags2;
  register s32 index2 ASM_REG("$19");
  register s32 dirx ASM_REG("$20");
  s16 direction;
  u16 f2a;
  register u16 *x_step ASM_REG("$22");
  sp20 = -1;
  f2a = arg0->field2a;
  ASM_USE_NV(f2a);
  sp28 = -0x100;
  ASM_KEEP(sp28);
  *arg2 = f2a;
  actor0 = arg0;
  entity1 = *((Entity **) (((u8 *) arg1) - 0x14));
  entity0 = *((Entity **) (((u8 *) actor0) - 0x14));
  c0 = arg0->coord88;
  delta = c0 - arg1->coord88;
  if (delta < 0)
  {
    delta = -delta;
  }
  if (delta >= 0x40)
  {
    return -1;
  }
  new_var = (s32) (&D_8006CCD8);
  sp30 = func_800A365C(entity0, entity1);
  distance = func_8009FD40(entity1, entity0);
  result = func_800A0818(entity0->x, entity0->y, entity1->x, entity1->y, &sp18);
  *arg2 = result;
  if ((arg3 == 0) && (distance == 1))
  {
    if ((func_8009A540(((((s32) result) << 16) >> 25) & 0xFFFF, entity0->x, entity0->y, (s16) (arg0->coord88 - 0x20)) << 16) != 0)
    {
      return 8;
    }
  }
  flags = arg0->flags14;
  if (!(flags & 0x10000))
  {
    arg0->flags14 = flags | 0x10000;
    if (func_8009FD40(D_80082E80, entity0) < 0x11)
    {
      flags2 = arg0->flags14;
      if (((flags2 & 0x6000) || (!(actor0->status98 & 0x10))) || (!(func_800A6D30() & 0xF)))
      {
        if (!(func_800A6D30() & 3))
        {
          if ((func_80042900(arg0, 6) << 16) == 0)
          {
            actor0->status98 |= 0x11;
            goto store_status;
          }
        }
      }
    }
    actor0->status98 &= 0xFFFE;
    store_status:
    ;

    ;
  }
  if (actor0->status98 & 1)
  {
    sp1C = 0;
    rot_raw = D_8008347E;
    rotation = rot_raw & 3;
    outer_loop:
    if (rotation == 3)
    {
      rotation = 0;
    }

    rotsx = rotation;
    rot3 = rotsx << 1;
    rot3 += rotsx;
    record_id = *((u8 *) (((u8 *) (((u8 *) arg0) + rot3)) + 8));
    if (record_id == 0)
    {
      goto outer_next;
    }
    recoff = record_id * 0x14;
    record = D_8006DE24 + recoff;
    kind_id = *((u8 *) (((u8 *) record) + 0x11));
    if (((u32) kind_id) >= 0x12)
    {
      goto outer_next;
    }
    blocked = func_80042900(arg1, (s8) kind_id);
    if (blocked != 0)
    {
      goto outer_next;
    }
    if ((*((u8 *) (((u8 *) record) + 0x13))) < distance)
    {
      goto outer_next;
    }
    value = func_800A35D8(*((u8 *) (((u8 *) record) + 0x10)), *((u16 *) (((u8 *) arg0) + 0x14)));
    if ((((s32) sp28) << 16) >= (value << 16))
    {
      goto outer_next;
    }
    kind = *((u8 *) (((u8 *) record) + 0x12));
    if (kind == 1)
    {
      goto kind1;
    }
    if (kind == 0)
    {
      goto outer_next;
    }
    if (kind < 4)
    {
      sp28 = value;
      goto set_slot;
    }
    goto outer_next;
    kind1:
    {
      if ((sp30 << 16) == 0)
      {
        goto outer_next;
      }
      x = entity0->x;
      y = entity0->y;
      steps = 0;
      direction = ((*arg2) >> 9) & 7;
      if (steps >= distance)
      {
        goto accept;
      }
      ASM_SET(dirx);
      ASM_CLOBBER("$3");
      ASM_CLOBBER("$4");
      ASM_CLOBBER("$5");
      dirx = direction << 16;
      index2 = ((u32) dirx) >> 15;
      x_step = (u16 *) (index2 + new_var);
      inner_loop:
      func_8009A350(x, y, dirx >> 16, &sp18);
      flags = arg0->flags1c;
      ASM_USE2_NV(distance, distance);
      ASM_USE_NV(value);

      if (!(flags & 0x410))
      {
        s32 raw = sp18;
        if (flags & 0x2000)
        {
          mask = raw & 0x300;
        }
        else
        {
          mask = raw & 0x3000;
        }
        if (mask != 0)
        {
          goto inner_done;
        }
      }
      next_steps = steps + 1;
      steps = next_steps;
      x += *x_step;
      y += *((u16 *) (((u8 *) (&D_8006CCE8)) + index2));
      if (next_steps < distance)
      {
        goto inner_loop;
      }
      inner_done:
      if (steps < distance)
      {
        goto outer_next;
      }
      ASM_USE_NV(steps);

      accept:
      sp28 = value;

      set_slot:
      sp20 = rotation + 1;

      goto outer_next;
    }

    outer_next:
    rotation++;

    sp1C++;
    if (sp1C < 3)
    {
      goto outer_loop;
    }
  }
  if ((arg3 != 0) && (distance == 1))
  {
    if ((func_8009A540(((((s32) (*arg2)) << 16) >> 25) & 0xFFFF, entity0->x, entity0->y, (s16) (arg0->coord88 - 0x20)) << 16) != 0)
    {
      if (((s16) sp20) < 0)
      {
        sp20 = 8;
      }
    }
  }
  return (s16) sp20;
}
