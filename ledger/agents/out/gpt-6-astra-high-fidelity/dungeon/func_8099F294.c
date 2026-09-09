#include "common.h"


typedef s32 (*ActorCallback)(void *, void *, void *, void *);
typedef struct 
{
  u16 value;
  u8 pad[14];
} U16Global;
typedef struct 
{
  s16 value;
  u8 pad[14];
} S16Global;
extern void func_80047738(void *, s32, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s16);
extern u8 D_8006CCF8[32];
extern S16Global D_80083228;
extern U16Global D_80083462;
extern u8 D_801710EC[12];
extern u8 D_80175E40[12];
extern ActorCallback D_80175ED8[16];
void func_80170A94(void *input0, void *input1, void *input2)
{
  register void *arg0 ASM_REG("$17") = input0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  void *entry_arg0 = input0;
  void *arg1 = input1;
  s32 direction;
  register s32 direction_index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
  s32 direction_value;
  void *arg2 = input2;
  s16 old_state;
  s16 height;
  s32 ground;
  u16 flags;
  u16 state_flags;
  s32 actor_flags;
  s32 random_value;
  s32 delta;
  s32 clear_delta;
  register s32 actor_mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  s32 accumulator_probe;
  s32 tail_value;
  s32 correction;
  register void *physics ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  ActorCallback callback;
  u32 initial_flags = D_80083462.value;
  if (initial_flags & 0x2000)
  {
    callback = *((ActorCallback *) (((u8 *) arg0) + 0x8C));
    if (callback == ((ActorCallback) D_801710EC))
    {
      ASM_KEEP(entry_arg0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      callback(entry_arg0, arg1, arg2, entry_arg0);
      return;
    }
    else
    {
      *((u8 *) (((u8 *) arg0) + 0x71)) &= 0x7F;
      return;
    }
  }
  ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  old_state = (s8) (*((u8 *) (((u8 *) arg0) + 0x6D)));
  if (func_800A9E70(arg0, arg1, arg2, arg0) != 0)
  {
    return;
  }
  if ((*((ActorCallback *) (((u8 *) arg0) + 0x8C))) != 0)
  {
    (*((ActorCallback *) (((u8 *) arg0) + 0x8C)))(arg0, arg1, arg2, arg0);
  }
  D_80175ED8[*((u8 *) (((u8 *) arg0) + 0x9A))](arg0, arg1, arg2, arg0);
  if (((s16) old_state) != (*((s8 *) (((u8 *) arg0) + 0x6D))))
  {
    func_800AA36C(arg0, arg1, arg2, arg0);
  }
  *((s32 *) (((u8 *) arg1) + 0)) += *((s32 *) (((u8 *) arg1) + 0xC));
  *((s32 *) (((u8 *) arg1) + 4)) += *((s32 *) (((u8 *) arg1) + 0x10));
  if ((!((*((u32 *) (((u8 *) arg0) + 0x1C))) & 0x40000)) && (!((*((u16 *) (((u8 *) arg0) + 0x98))) & 8)))
  {
    *((s32 *) (((u8 *) arg1) + 0x14)) += (*((s8 *) (((u8 *) arg0) + 0x9D))) * 0x14000;
    (*((u8 *) (((u8 *) arg0) + 0x9D)))++;
  }
  else
  {
    *((u8 *) (((u8 *) arg0) + 0x9D)) = 0;
  }
  *((s32 *) (((u8 *) arg0) + 0x90)) += *((s32 *) (((u8 *) arg1) + 0x14));
  direction_value = ((D_80083228.value + (*((s16 *) (((u8 *) physics) + 0x2A)))) + 0x100) >> 9;
  direction = direction_value & 7;
  ASM_KEEP(direction);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  direction_index = direction;
  if ((*((s16 *) (((u8 *) arg0) + 0x94))) != direction_index)
  {
    func_80047738(arg2, *((u8 *) ((*((u8 **) (((u8 *) arg2) + 0x2C))) + direction_index)), *((s8 *) (((u8 *) arg2) + 4)));
    *((s16 *) (((u8 *) arg0) + 0x94)) = direction;
  }
  if (D_8006CCF8[direction_index] != 0)
  {
    flags = (*((u16 *) (((u8 *) arg2) + 0x14))) | 1;
  }
  else
  {
    flags = (*((u16 *) (((u8 *) arg2) + 0x14))) & 0xFFFE;
  }
  *((u16 *) (((u8 *) arg2) + 0x14)) = flags;
  ASM_KEEP(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
  state_flags = *((volatile u16 *) (((u8 *) arg2) + 0x14));
  if (!(state_flags & 0x8000))
  {
    func_800A020C(*((s32 *) (((u8 *) physics) + 0x1C)), ((u8 *) arg2) + 0xC);
    if (!((*((u32 *) (((u8 *) physics) + 0x1C))) & 0x20))
    {
      if (!((*((u16 *) (((u8 *) arg2) + 0x14))) & 0x40))
      {
        func_800478B8(arg2);
      }
    }
    else
    {
      *((u16 *) (((u8 *) arg2) + 0x14)) |= 0x7000;
      *((u32 *) (((u8 *) physics) + 0x1C)) &= 0xFFFBFFFF;
    }
    *((u32 *) (((u8 *) physics) + 0x1C)) &= 0xF7FFFFFF;
    if ((*((u32 *) (((u8 *) physics) + 0x1C))) & 0x40000)
    {
      if ((!((*((u16 *) (((u8 *) arg2) + 0x14))) & 0x40)) && ((*((void **) (((u8 *) arg2) + 0x2C))) == D_80175E40))
      {
        if ((*((u16 *) (((u8 *) arg2) + 4))) == 0x100)
        {
          *((u16 *) (((u8 *) arg0) + 0x9E)) = 0;
          *((s32 *) (((u8 *) arg0) + 0xA0)) = 0;
        }
        if (((u32) ((*((u8 *) (((u8 *) arg2) + 4))) - 1)) < 4)
        {
          s16 count = *((u16 *) (((u8 *) arg0) + 0x9E));
          (*((u16 *) (((u8 *) arg0) + 0x9E)))++;
          random_value = func_800644B8(count * 0xAA);
          *((s32 *) (((u8 *) arg0) + 0xA0)) += random_value << 5;
        }
        else
        {
          s16 count = *((u16 *) (((u8 *) arg0) + 0x9E));
          (*((u16 *) (((u8 *) arg0) + 0x9E)))++;
          random_value = func_800644B8(count * 0xAA);
          *((s32 *) (((u8 *) arg0) + 0xA0)) += random_value << 6;
        }
      }
      if (!((*((u16 *) (((u8 *) arg0) + 0x98))) & 8))
      {
        height = *((s16 *) (((u8 *) arg0) + 0x92));
        if (height >= (-0x1F))
        {
          *((u16 *) (((u8 *) arg0) + 0x92)) = ((u16) height) - 8;
        }
        else if (height < (-0x28))
        {
          *((u16 *) (((u8 *) arg0) + 0x92)) = ((u16) height) + 8;
        }
      }
      goto post_physics;
    }
    goto clear_accumulator;
  }
  state_flags = (state_flags & 0x800) ? (state_flags & 0x8FFF) : (state_flags | 0x7000);
  do
  {
    *((u16 *) (((u8 *) arg2) + 0x14)) = state_flags;
  }
  while (0);
  actor_mask = 0xF7FFFFFF;
  actor_flags = actor_mask & (*((u32 *) (((u8 *) physics) + 0x1C)));
  actor_mask = 0x40000;
  *((volatile u32 *) (((u8 *) physics) + 0x1C)) = actor_flags;
  actor_flags &= actor_mask;
  if (!actor_flags)
  {
    clear_accumulator:
    clear_delta = *((s32 *) (((u8 *) arg0) + 0xA0));

    *((u16 *) (((u8 *) arg0) + 0x9E)) = 0;
    *((s32 *) (((u8 *) arg0) + 0xA0)) = 0;
    *((s32 *) (((u8 *) arg0) + 0x90)) -= clear_delta;
    if (!((*((u16 *) (((u8 *) arg0) + 0x98))) & 8))
    {
      ground = func_800BCB04(*((u16 *) (((u8 *) arg1) + 2)), *((u16 *) (((u8 *) arg1) + 6)), (s16) ((*((u16 *) (((u8 *) physics) + 0x88))) - 0x20));
      delta = ground - (*((u16 *) (((u8 *) physics) + 0x88)));
      if (((s16) delta) < (*((s16 *) (((u8 *) arg0) + 0x92))))
      {
        *((s16 *) (((u8 *) arg0) + 0x92)) = delta;
        *((u8 *) (((u8 *) arg0) + 0x9D)) = 0;
        *((s32 *) (((u8 *) arg1) + 0x14)) = 0;
        *((u32 *) (((u8 *) physics) + 0x1C)) |= 0x08000000;
        goto post_physics;
      }
    }
    goto post_physics;
  }
  if ((!((*((u16 *) (((u8 *) arg2) + 0x14))) & 0x40)) && ((*((void **) (((u8 *) arg2) + 0x2C))) == D_80175E40))
  {
    if ((*((u16 *) (((u8 *) arg2) + 4))) == 0x100)
    {
      *((u16 *) (((u8 *) arg0) + 0x9E)) = 0;
      *((s32 *) (((u8 *) arg0) + 0xA0)) = 0;
    }
    if (((u32) ((*((u8 *) (((u8 *) arg2) + 4))) - 1)) < 4)
    {
      s16 count = *((u16 *) (((u8 *) arg0) + 0x9E));
      (*((u16 *) (((u8 *) arg0) + 0x9E)))++;
      random_value = func_800644B8(count * 0xAA);
      *((s32 *) (((u8 *) arg0) + 0xA0)) += random_value << 5;
    }
    else
    {
      s16 count = *((u16 *) (((u8 *) arg0) + 0x9E));
      (*((u16 *) (((u8 *) arg0) + 0x9E)))++;
      random_value = func_800644B8(count * 0xAA);
      *((s32 *) (((u8 *) arg0) + 0xA0)) += random_value << 6;
    }
  }
  if (!((*((u16 *) (((u8 *) arg0) + 0x98))) & 8))
  {
    height = *((s16 *) (((u8 *) arg0) + 0x92));
    if (height >= (-0x1F))
    {
      *((u16 *) (((u8 *) arg0) + 0x92)) = ((u16) height) - 8;
    }
    else if (height < (-0x28))
    {
      *((u16 *) (((u8 *) arg0) + 0x92)) = ((u16) height) + 8;
    }
  }
  post_physics:
  actor_flags = *((u32 *) (((u8 *) physics) + 0x1C));

  if (actor_flags & 0x40000000)
  {
    *((u32 *) (((u8 *) physics) + 0x1C)) = actor_flags & 0xBFFFFFFF;
    ground = func_800BCB04(((*((u8 *) (((u8 *) arg2) + 0x24))) << 6) | 0x20, ((*((u8 *) (((u8 *) arg2) + 0x25))) << 6) | 0x20, (s16) ((*((u16 *) (((u8 *) physics) + 0x88))) - 0x20));
    if (((s16) ground) < 0x200)
    {
      correction = (*((u16 *) (((u8 *) physics) + 0x88))) - ground;
      *((u16 *) (((u8 *) arg0) + 0x92)) += correction;
      *((u16 *) (((u8 *) physics) + 0x88)) = ground;
    }
  }
  *((s16 *) (((u8 *) arg1) + 0xA)) = ((*((u16 *) (((u8 *) physics) + 0x88))) + (*((u16 *) (((u8 *) arg0) + 0x92)))) - (*((u16 *) (((u8 *) arg0) + 0xA2)));
  *((u16 *) (((u8 *) arg2) + 0x14)) |= 0x40;
}
