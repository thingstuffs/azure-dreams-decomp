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

/* Selects a usable ability or adjacent attack and sets the angle toward the target. */
s16 func_800A384C(Actor *actor, Actor *target, u16 *out_angle, s32 prefer_ability)
{
  s16 tile_flags;
  s32 slots_checked;
  s16 selected_action;
  s16 best_score;
  u16 line_valid;
  register Actor *self ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  Entity *actor_entity;
  register Entity *target_entity ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
  u8 *ability;
  u8 ability_id;
  s32 target_mode;
  s32 effect_id;
  s32 obstacles;
  s32 distance;
  s16 target_angle;
  register s16 slot ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
  s16 effect_blocked;
  register s32 slot_seed ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register s32 slot_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 slot_index;
  register s32 ability_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  register s16 steps ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s16 next_steps;
  s16 x;
  s16 y;
  s32 height_delta;
  register s32 actor_height ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s32 score;
  s32 x_steps_base;
  s32 flags;
  s32 ability_flags;
  register s32 step_offset ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  register s32 direction_shifted ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  s16 direction;
  u16 facing_angle;
  register u16 *x_step ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  selected_action = -1;
  facing_angle = actor->field2a;
  ASM_USE_NV(facing_angle);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  best_score = -0x100;
  ASM_KEEP(best_score);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  *out_angle = facing_angle;
  self = actor;
  target_entity = *((Entity **) (((u8 *) target) - 0x14));
  actor_entity = *((Entity **) (((u8 *) self) - 0x14));
  actor_height = actor->coord88;
  height_delta = actor_height - target->coord88;
  if (height_delta < 0)
  {
    height_delta = -height_delta;
  }
  if (height_delta >= 0x40)
  {
    return -1;
  }
  x_steps_base = (s32) (&D_8006CCD8);
  line_valid = func_800A365C(actor_entity, target_entity);
  distance = func_8009FD40(target_entity, actor_entity);
  target_angle = func_800A0818(actor_entity->x, actor_entity->y, target_entity->x, target_entity->y, &tile_flags);
  *out_angle = target_angle;
  if ((prefer_ability == 0) && (distance == 1))
  {
    if ((func_8009A540(((((s32) target_angle) << 16) >> 25) & 0xFFFF, actor_entity->x, actor_entity->y, (s16) (actor->coord88 - 0x20)) << 16) != 0)
    {
      return 8;
    }
  }
  flags = actor->flags14;
  if (!(flags & 0x10000))
  {
    actor->flags14 = flags | 0x10000;
    if (func_8009FD40(D_80082E80, actor_entity) < 0x11)
    {
      ability_flags = actor->flags14;
      if (((ability_flags & 0x6000) || (!(self->status98 & 0x10))) || (!(func_800A6D30() & 0xF)))
      {
        if (!(func_800A6D30() & 3))
        {
          if ((func_80042900(actor, 6) << 16) == 0)
          {
            self->status98 |= 0x11;
            goto store_status;
          }
        }
      }
    }
    self->status98 &= 0xFFFE;
    store_status:
    ;

    ;
  }
  if (self->status98 & 1)
  {
    slots_checked = 0;
    slot_seed = D_8008347E;
    slot = slot_seed & 3;
    outer_loop:
    if (slot == 3)
    {
      slot = 0;
    }

    slot_index = slot;
    slot_offset = slot_index << 1;
    slot_offset += slot_index;
    ability_id = *((u8 *) (((u8 *) (((u8 *) actor) + slot_offset)) + 8));
    if (ability_id == 0)
    {
      goto outer_next;
    }
    ability_offset = ability_id * 0x14;
    ability = D_8006DE24 + ability_offset;
    effect_id = *((u8 *) (((u8 *) ability) + 0x11));
    if (((u32) effect_id) >= 0x12)
    {
      goto outer_next;
    }
    effect_blocked = func_80042900(target, (s8) effect_id);
    if (effect_blocked != 0)
    {
      goto outer_next;
    }
    if ((*((u8 *) (((u8 *) ability) + 0x13))) < distance)
    {
      goto outer_next;
    }
    score = func_800A35D8(*((u8 *) (((u8 *) ability) + 0x10)), *((u16 *) (((u8 *) actor) + 0x14)));
    if ((((s32) best_score) << 16) >= (score << 16))
    {
      goto outer_next;
    }
    target_mode = *((u8 *) (((u8 *) ability) + 0x12));
    if (target_mode == 1)
    {
      goto kind1;
    }
    if (target_mode == 0)
    {
      goto outer_next;
    }
    if (target_mode < 4)
    {
      best_score = score;
      goto set_slot;
    }
    goto outer_next;
    kind1:
    {
      if ((line_valid << 16) == 0)
      {
        goto outer_next;
      }
      x = actor_entity->x;
      y = actor_entity->y;
      steps = 0;
      direction = ((*out_angle) >> 9) & 7;
      if (steps >= distance)
      {
        goto accept;
      }
      ASM_SET(direction_shifted);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      direction_shifted = direction << 16;
      step_offset = ((u32) direction_shifted) >> 15;
      x_step = (u16 *) (step_offset + x_steps_base);
      inner_loop:
      func_8009A350(x, y, direction_shifted >> 16, &tile_flags);
      flags = actor->flags1c;
      ASM_USE2_NV(distance, distance);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
      ASM_USE_NV(score);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */

      if (!(flags & 0x410))
      {
        s32 path_flags = tile_flags;
        if (flags & 0x2000)
        {
          obstacles = path_flags & 0x300;
        }
        else
        {
          obstacles = path_flags & 0x3000;
        }
        if (obstacles != 0)
        {
          goto inner_done;
        }
      }
      next_steps = steps + 1;
      steps = next_steps;
      x += *x_step;
      y += *((u16 *) (((u8 *) (&D_8006CCE8)) + step_offset));
      if (next_steps < distance)
      {
        goto inner_loop;
      }
      inner_done:
      if (steps < distance)
      {
        goto outer_next;
      }
      ASM_USE_NV(steps);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

      accept:
      best_score = score;

      set_slot:
      selected_action = slot + 1;

      goto outer_next;
    }

    outer_next:
    slot++;

    slots_checked++;
    if (slots_checked < 3)
    {
      goto outer_loop;
    }
  }
  if ((prefer_ability != 0) && (distance == 1))
  {
    if ((func_8009A540(((((s32) (*out_angle)) << 16) >> 25) & 0xFFFF, actor_entity->x, actor_entity->y, (s16) (actor->coord88 - 0x20)) << 16) != 0)
    {
      if (((s16) selected_action) < 0)
      {
        selected_action = 8;
      }
    }
  }
  return (s16) selected_action;
}
