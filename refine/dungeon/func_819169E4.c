#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_800814A0;
/* Advance motion counters and position, and set completion flags past the lifetime. */
void func_800241E4(void *motion, void *position, M2C_UNK update_context)
{
  s32 y_step;
  void *motion_state;
  void *page;
  void *owner;
  owner = *((void **) (((s8 *) motion) + 0));
  *((u16 *) (((s8 *) owner) + 0x14)) = (u16) ((*((u16 *) (((s8 *) owner) + 0x14))) + 1);
  *((u16 *) (((s8 *) motion) + 4)) = (u16) ((*((u16 *) (((s8 *) motion) + 4))) + 1);
  func_800478B8(update_context);
  *((s32 *) (((s8 *) position) + 0)) = (s32) ((*((s32 *) (((s8 *) position) + 0))) + ((func_80064584(*((s16 *) (((s8 *) motion) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) motion) + 8))) - ((s16) (*((u16 *) (((s8 *) motion) + 4))))) << 8)));
  y_step = (func_800644B8(*((s16 *) (((s8 *) motion) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) motion) + 8))) - ((s16) (*((u16 *) (((s8 *) motion) + 4))))) << 8);
  *((s32 *) (((s8 *) position) + 8)) = (s32) ((*((s32 *) (((s8 *) position) + 8))) + 0xFFFE0000);
  motion_state = motion;
  *((s32 *) (((s8 *) position) + 4)) = (s32) ((*((s32 *) (((s8 *) position) + 4))) + y_step);
  if (((s16) (*((u16 *) (((s8 *) motion_state) + 4)))) > (*((s16 *) (((s8 *) motion_state) + 6))))
  {
    *((u16 *) (((s8 *) motion_state) + (-2))) = (u16) ((*((u16 *) (((s8 *) motion_state) + (-2)))) | 0x8000);
    page = (void *) 0x80080000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    *((s32 *) (((s8 *) page) + 0x14A0)) = (s32) ((*((s32 *) (((s8 *) page) + 0x14A0))) | 0x8000);
  }
}
/* MECHANISM: The seed preserves the 0x20 frame and the long-lived s1/s0 argument bases.
   A literal 0x80080000 page local held by ASM_KEEP emits the branch-delay lui in v1.
   Both flag RMW accesses use +0x14A0 from that base, closing all three addressing words. */
