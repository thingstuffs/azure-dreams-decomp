#include "common.h"

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
typedef struct DungeonTileRecordLocal
{
  u8 pad0[0xC];
  u16 flags;
  u8 padE[6];
} DungeonTileRecordLocal;
extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern s16 func_800A0134();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80171E00();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00[8];
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern DungeonTileRecordLocal D_800E2970[];
void func_80171410(u8 *object_arg, void *arg1, u8 *tile_arg, u8 *actor_arg)
{
  register u8 *object ASM_REG("$21") = object_arg;
  register u8 *tile ASM_REG("$19") = tile_arg;
  register u8 *actor ASM_REG("$18") = actor_arg;
  u8 *state = (u8 *) (&D_80083460);
  s32 actor_flags;
  s32 call_result;
  s32 special;
  s32 angle;
  u16 state_flags;
  void *found;
  u8 *other;
  state_flags = *((u16 *) (((u8 *) state) + 2));
  ASM_KEEP(object);
  ASM_KEEP(actor);
  ASM_KEEP(tile);
  special = 0;
  if (state_flags & 0x4000)
  {
    goto check_entry;
  }
  if ((*((s8 *) (((u8 *) actor) + 0x71))) < 0)
  {
    goto negative_entry;
  }
  check_entry:
  if ((*((u8 *) (((u8 *) actor) + 0x12))) >= 2)
  {
    goto reject_entry;
  }

  if ((func_80171E00(object, arg1, tile, actor) << 16) != 0)
  {
    goto accepted_entry;
  }
  reject_entry:
  func_800A9A0C(actor);

  goto done;
  accepted_entry:
  if ((*((void **) (((u8 *) state) + 0xC))) == actor)
  {
    *((u16 *) (((u8 *) actor) + 0x46)) = 0xC008;
  }

  goto done;
  negative_entry:
  if (!(state_flags & 0x2000))
  {
    goto done;
  }

  func_800A19E4(tile, actor, 3, 6, object + 0x9C);
  actor_flags = *((s32 *) (((u8 *) actor) + 0x1C));
  if (!(actor_flags & 0x410))
  {
    goto check_mode_2000;
  }
  if (!(actor_flags & 0x400))
  {
    goto mode_410_without_400;
  }
  found = func_800A02AC(actor, *((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)));
  if (found == 0)
  {
    goto no_found_actor;
  }
  other = *((void **) (((u8 *) found) + (-0x14)));
  *((u16 *) (((u8 *) actor) + 0x2A)) = func_800A0818(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((u8 *) (((u8 *) other) + 0x24)), *((u8 *) (((u8 *) other) + 0x25)), object + 0x98);
  {
    u8 cleared_state = (*((u8 *) (((u8 *) actor) + 0x71))) & 0x7F;
    ASM_USE(object);
    *((u8 *) (((u8 *) actor) + 0x71)) = cleared_state;
  }
  goto done;
  no_found_actor:
  {
    register s32 actor_state ASM_REG("$2") = *((s32 *) (((u8 *) actor) + 0x14));
    ASM_KEEP_NV(actor_state);
    if (actor_state < 0)
    {
      goto zero_counter;
    }
    *((s32 *) (((u8 *) actor) + 0x14)) = actor_state | 0x80000000;
  }

  call_result = func_800A6D30();
  *((u16 *) (((u8 *) actor) + 0x2A)) += (call_result & 7) << 9;
  goto zero_counter;
  mode_410_without_400:
  if (func_800A04F0(actor, *((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((s16 *) (((u8 *) actor) + 0x2A))) == 0)
  {
    goto loop_setup;
  }

  goto strip_path;
  check_mode_2000:
  if (!(actor_flags & 0x2000))
  {
    goto check_tile_kind;
  }

  if ((*((u16 *) (((u8 *) actor) + 0x46))) & 0x8000)
  {
    goto loop_setup;
  }
  if (!(actor_flags & 0x20000))
  {
    goto invoke_fallback;
  }
  {
    u8 *goal = D_80082E80;
    s32 direction = *((u8 *) (((u8 *) actor) + 0x45));
    s32 base_angle = *((s16 *) (((u8 *) D_800814A8) + 0x2A));
    s32 offset;
    s32 target_x;
    s32 target_y;
    direction += base_angle >> 9;
    offset = (direction & 7) * 2;
    target_x = (*((u8 *) (((u8 *) goal) + 0x24))) + (*((u16 *) (((u8 *) (&D_8006CCD8)) + offset)));
    target_y = (*((u8 *) (((u8 *) goal) + 0x25))) + (*((u16 *) (((u8 *) (&D_8006CCE8)) + offset)));
    if (((*((u8 *) (((u8 *) tile) + 0x24))) == ((u16) target_x)) && ((*((u8 *) (((u8 *) tile) + 0x25))) == ((u16) target_y)))
    {
      goto strip_path;
    }
    {
      u16 next_angle = func_800A0818(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), (s16) target_x, (s16) target_y, object + 0x98);
      *((u16 *) (((u8 *) actor) + 0x2A)) = next_angle;
      if ((func_8009A66C((s16) next_angle, tile, actor, 0x20) << 16) <= 0)
      {
        u8 *retry_goal = ((u8 *) (&D_80082EA4)) - 0x24;
        *((u16 *) (((u8 *) actor) + 0x2A)) = func_800A0818(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((u8 *) (((u8 *) retry_goal) + 0x24)), *((u8 *) (((u8 *) retry_goal) + 0x25)), object + 0x98);
      }
    }
  }
  {
    u8 *check_goal = ((u8 *) (&D_80082EA4)) - 0x24;
    if ((func_8009FD7C(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((u8 *) (((u8 *) check_goal) + 0x24)), *((u8 *) (((u8 *) check_goal) + 0x25))) << 16) != 0)
    {
      special = 1;
    }
  }
  goto loop_setup;
  check_tile_kind:
  {
    s8 kind = *((s8 *) (((u8 *) tile) + 0x26));
    if ((kind >= 0) && (D_800E2970[kind].flags & 2))
    {
      goto invoke_fallback_call;
    }
  }

  if ((*((u16 *) (((u8 *) actor) + 0x46))) & 0x8000)
  {
    goto retry_toward_goal;
  }
  found = func_800A04F0(actor, *((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((s16 *) (((u8 *) actor) + 0x2A)));
  if (found == 0)
  {
    goto retry_toward_goal;
  }
  if (!((*((s32 *) (((u8 *) found) + 0x1C))) & 0x2000))
  {
    goto retry_toward_goal;
  }
  if (func_800A0134(found, actor) >= 0x81)
  {
    goto retry_toward_goal;
  }
  if ((func_8009A540(((*((s16 *) (((u8 *) actor) + 0x2A))) >> 9) & 0xFFFF, *((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), (s16) ((*((u16 *) (((u8 *) actor) + 0x88))) - 0x20)) << 16) != 0)
  {
    goto strip_path;
  }
  retry_toward_goal:
  if (!((*((s32 *) (((u8 *) actor) + 0x1C))) & 0x20000))
  {
    goto invoke_fallback;
  }

  {
    u8 *goal = D_80082E80;
    u8 *out = object + 0x98;
    *((u16 *) (((u8 *) actor) + 0x2A)) = func_800A0818(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((u8 *) (((u8 *) goal) + 0x24)), *((u8 *) (((u8 *) goal) + 0x25)), out);
    if ((func_8009FD7C(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), *((u8 *) (((u8 *) goal) + 0x24)), *((u8 *) (((u8 *) goal) + 0x25))) << 16) == 0)
    {
      goto zero_counter;
    }
    if (func_800A0134(D_800814A8, actor) >= 0x81)
    {
      goto loop_setup_zero;
    }
    if ((func_8009A540(((*((s16 *) (((u8 *) actor) + 0x2A))) >> 9) & 0xFFFF, *((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), (s16) ((*((u16 *) (((u8 *) actor) + 0x88))) - 0x20)) << 16) == 0)
    {
      goto loop_setup;
    }
  }
  goto strip_path;
  invoke_fallback:
  invoke_fallback_call:
  func_800A0E6C(tile, *((s8 *) (((u8 *) object) + 0x9C)), actor, object + 0x98);


  zero_counter:
  goto loop_setup;

  loop_setup_zero:
  goto loop_setup;

  loop_setup:
  {
    s16 counter = 0;
    s16 *angle_steps = D_8006CD00;
    register s32 base_angle ASM_REG("$3");
    loop_body:
    base_angle = *((s16 *) (((u8 *) actor) + 0x2A));

    if ((*((u16 *) (((u8 *) object) + 0x98))) & 2)
    {
      angle = base_angle - angle_steps[counter];
    }
    else
    {
      angle = base_angle + angle_steps[counter];
    }
    if ((func_8009A66C((s16) angle, tile, actor, 0x20) << 16) <= 0)
    {
      goto move_failed;
    }
    if (counter >= 3)
    {
      register s32 special_copy ASM_REG("$2") = special;
      ASM_KEEP_NV(special_copy);
      if (special_copy)
      {
        goto strip_path;
      }
    }
    *((u16 *) (((u8 *) actor) + 0x2A)) = angle;
    *((u8 *) (((u8 *) (actor + ((*((u8 *) (((u8 *) actor) + 0x71))) & 0x7F))) + 0x74)) = *((u8 *) (((u8 *) tile) + 0x24));
    *((u8 *) (((u8 *) (actor + ((*((u8 *) (((u8 *) actor) + 0x71))) & 0x7F))) + 0x7C)) = *((u8 *) (((u8 *) tile) + 0x25));
    (*((u8 *) (((u8 *) actor) + 0x71)))++;
    func_8009A3D0(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), ((*((s32 *) (((u8 *) actor) + 0x1C))) & 0x2000) ? (0x300) : (0x3000));
    {
      register u8 *x_table ASM_REG("$3") = &D_8006CCD8;
      register s32 direction ASM_REG("$4") = ((*((u16 *) (((u8 *) actor) + 0x2A))) >> 8) & 0xE;
      *((u8 *) (((u8 *) tile) + 0x24)) += *((u8 *) (((u8 *) x_table) + direction));
      *((u8 *) (((u8 *) tile) + 0x25)) += *((u8 *) (((u8 *) (&D_8006CCE8)) + direction));
    }
    func_8009A21C(*((u8 *) (((u8 *) tile) + 0x24)), *((u8 *) (((u8 *) tile) + 0x25)), ((*((s32 *) (((u8 *) actor) + 0x1C))) & 0x2000) ? (0x300) : (0x3000));
    goto check_counter_limit;
    move_failed:
    if (counter == 0)
    {
      if ((*((u16 *) (((u8 *) (&D_80082EA4)) + 0))) != (*((u16 *) (((u8 *) tile) + 0x24))))
      {
        ASM_SCHED_BARRIER();
        if ((func_8009A180(actor, (*((s32 *) (((u8 *) D_800814A8) + 0x58))) + 0x20) << 16) != 0)
        {
          goto done;
        }
      }
    }

    counter++;
    if (counter < 8)
    {
      goto loop_body;
    }
    check_counter_limit:
    if (counter >= 8)
    {
      *((u8 *) (((u8 *) actor) + 0x71)) &= 0x7F;
      *((u16 *) (((u8 *) actor) + 0x46)) &= 0x7FFF;
      func_800A9A0C(actor);
      goto done;
    }

  }

  *((u16 *) (((u8 *) actor) + 0x46)) &= 0x7FFF;
  *((u8 *) (((u8 *) object) + 0x9C)) = *((u8 *) (((u8 *) tile) + 0x26));
  (*((u8 *) (((u8 *) actor) + 0x6D)))--;
  {
    u8 *late_state = (u8 *) (&D_80083460);
    (*((u16 *) (((u8 *) late_state) + 8)))++;
  }
  if ((*((s8 *) (((u8 *) actor) + 0x6D))) != 0)
  {
    goto actor_survives;
  }
  strip_path:
  *((u8 *) (((u8 *) actor) + 0x71)) &= 0x7F;

  goto done;
  actor_survives:
  {
    register s16 result ASM_REG("$17") = func_800BCB04(((*((u8 *) (((u8 *) tile) + 0x24))) << 6) | 0x20, ((*((u8 *) (((u8 *) tile) + 0x25))) << 6) | 0x20, (s16) ((*((u16 *) (((u8 *) actor) + 0x88))) - 0x20));
    if (result < 0x200)
    {
      *((u16 *) (((u8 *) actor) + 0x88)) = result;
    }
  }

  goto done;
  done:
  return;

}
