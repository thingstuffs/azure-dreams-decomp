#include "common.h"

extern s32 D_800814A0_loop __attribute__((section(".data")));
extern s32 D_800814A0_tail __attribute__((section(".data")));
__asm__(".set D_800814A0_loop, 0x800814A0\n.set D_800814A0_tail, 0x800814A0");
typedef struct A0
{
  u16 pad0[3];
  u16 unk6;
  u8 pad8[0x14];
  int unk1C;
} A0;
typedef struct FrameB
{
  s16 unk0;
  u16 unk2;
  u16 unk4;
  s16 unk6;
  u8 pad8[8];
} FrameB;
typedef struct AnimSub
{
  s16 pad0[3];
  s16 unk6;
  s16 pad8;
  s16 unkA;
  u16 unkC;
  s16 unkE;
  s16 unk10;
} AnimSub;
typedef struct Ent
{
  u16 pad[0xF];
  u16 flags;
  AnimSub anim;
} Ent;
typedef struct S_8005313C
{
  A0 *unk0;
  s16 state;
  u16 counter;
  s16 unk8;
  s16 unkA;
  FrameB *unkC;
  Ent *unk10[16];
} S_8005313C;
extern void func_80052C10(s16, FrameB *);
/* Plays timed entity animations, then flags the sequence and its entities for cleanup. */
void func_8005313C(S_8005313C *sequence)
{
  s16 *state_ptr;
  u16 elapsed_ticks;
  s16 entity_slot;
  Ent *entity;
  Ent *anim_entity;
  AnimSub *anim;
  FrameB *frame;
  s16 next_tick;
  int entity_index;
  s32 cleanup_flags;

  elapsed_ticks = sequence->counter + 1;
  sequence->counter = elapsed_ticks;
  switch (sequence->state)
  {
    case 0:
      if (sequence->unkA != 0)
      {
        sequence->unkA = 0;
        sequence->counter = 0;
        sequence->state = sequence->state + 1;
      }
      break;

    case 1:
      if (sequence->unkC->unk0 == ((s16) elapsed_ticks))
      {
        do
        {
          entity_slot = (sequence->unk8 + 1) % 16;
          sequence->unk8 = entity_slot;
          anim_entity = sequence->unk10[entity_slot];
          anim = &anim_entity->anim;
          if (anim->unk6 == 0)
          {
            anim->unk6 = 1;
            anim->unkA = sequence->unkC->unk2 - 0x180;
            anim->unk10 = sequence->unkC->unk2 - 0x180;
            anim->unkC = sequence->unkC->unk4;
            anim->unkE = (sequence->unkC->unk6 * 12) + 12;
            func_80052C10(sequence->unk8, sequence->unkC);
          }
          frame = sequence->unkC;
          sequence->unkC = frame + 1;
          next_tick = frame[1].unk0;
          if (next_tick == 0)
          {
            sequence->counter = 0;
            sequence->state = (*(state_ptr = &sequence->state)) + 1;
            return;
          }
        }
        while (next_tick == ((s16) sequence->counter));
      }
      break;

    case 2:
      if (((s16) elapsed_ticks) >= 0x190)
      {
        sequence->unk0->unk1C = 0;
        sequence->unk0->unk6 = sequence->unk0->unk6 + 1;
        for (entity_index = 0; entity_index < 0x10; entity_index++)
        {
          entity = sequence->unk10[entity_index];
          cleanup_flags = D_800814A0_loop | 0x8000;
          D_800814A0_loop = cleanup_flags;
          entity->flags |= 0x8000;
        }

        *((u16 *) (((u8 *) sequence) - 2)) |= 0x8000;
        D_800814A0_tail = cleanup_flags;
      }
      break;
  }
}
