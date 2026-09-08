#include "common.h"

typedef struct Scratch
{
  u16 unk0;
  u16 unk2;
  u16 unk4;
  u8 pad6[0x12];
  u8 *current;
  u8 pad1C[4];
  u32 *table;
  u8 pad24[0x6C];
  u32 unk90;
  u32 unk94;
  u8 pad98[0x28];
  u32 index;
} Scratch;
typedef struct Arg0
{
  u8 pad0[8];
  s32 unk8;
  u8 padC[0x26];
  s16 scale;
  s16 divisor;
} Arg0;
typedef struct Arg1
{
  u8 pad0[2];
  u16 unk2;
  u8 pad4[2];
  u16 unk6;
  u8 pad8[2];
  u16 unkA;
} Arg1;
extern u8 D_80083160[];
extern void func_80025080() __attribute__((noreturn));
extern u32 func_80065420();
extern u32 func_80066460();
extern void func_80067F20();
s32 func_81875828(Arg0 *arg0, Arg1 *arg1)
{
  Arg1 *input = arg1;
  u32 high_mask = 0xFF000000;
  register Scratch *scratch ASM_REG("$17") = (Scratch *) 0x1F800000;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  register u8 **state_slot ASM_REG("$21") = (u8 **) D_80083160;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
  u32 low_mask = 0x00FFFFFF;
  u8 *state = *((u8 **) D_80083160);
  u8 *initial_current;
  u16 first_coord;
  u16 second_coord;
  u16 third_coord;
  register u8 *entry ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
  Scratch *active;
  Scratch *call_base;
  Scratch *call_arg;
  u32 *out90;
  u32 *out94;
  u8 *entry_arg;
  u8 *previous;
  Scratch *tail_arg;
  ASM_KEEP(state_slot);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  initial_current = *((u8 **) (state + 0x8D0));
  scratch->current = initial_current;
  scratch->table = (u32 *) (state + 0xB0);
  ASM_KEEP(state_slot);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  active = scratch;
  ASM_KEEP(active);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  call_arg = active;
  ASM_KEEP(call_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  out90 = &active->unk90;
  first_coord = input->unk2;
  ASM_KEEP(first_coord);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
  entry = *((u8 * volatile *) (&active->current));
  out94 = &active->unk94;
  active->unk0 = first_coord;
  second_coord = input->unk6;
  entry_arg = entry + 8;
  active->unk2 = second_coord;
  third_coord = input->unkA;
  active->current = entry + 0xC;
  active->unk4 = third_coord;
  active->index = func_80065420(call_arg, entry_arg, out90, out94);
  if (active->index < 0x1E0U)
  {
    *((s32 *) (((u8 *) entry) + 4)) = arg0->unk8;
    *((u8 *) (((u8 *) entry) + 4)) = ((*((u8 *) (((u8 *) entry) + 4))) * arg0->scale) / arg0->divisor;
    *((u8 *) (((u8 *) entry) + 5)) = ((*((u8 *) (((u8 *) entry) + 5))) * arg0->scale) / arg0->divisor;
    *((u8 *) (((u8 *) entry) + 6)) = ((*((u8 *) (((u8 *) entry) + 6))) * arg0->scale) / arg0->divisor;
    *((u8 *) (((u8 *) entry) + 3)) = 2;
    *((u8 *) (((u8 *) entry) + 7)) = 0x6A;
    *((u32 *) (((u8 *) entry) + 0)) = ((*((u32 *) (((u8 *) entry) + 0))) & high_mask) | (active->table[active->index] & low_mask);
    {
      register u32 table_slot ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      u32 packet_bits;
      register u32 table_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
      table_slot = active->index;
      table_slot = (table_slot << 2) + (u32) active->table;
      packet_bits = (u32) entry & low_mask;
      table_word = *((u32 *) table_slot);
      table_word = (table_word & high_mask) | packet_bits;
      ASM_KEEP_DEP_NV(table_word, entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
      *((u32 *) table_slot) = table_word;
    }
    entry = active->current;
    active->current = entry + 0xC;
    func_80067F20(entry, 0, 0, (u16) func_80066460(0, 1, 0, 0), 0);
    *((u32 *) (((u8 *) entry) + 0)) = ((*((u32 *) (((u8 *) entry) + 0))) & high_mask) | (active->table[active->index] & low_mask);
    entry = (u8 *) (((u32) entry) & low_mask);
    active->table[active->index] = (active->table[active->index] & high_mask) | ((u32) entry);
  }
  previous = *((u8 **) (((u8 *) arg0) - 8));
  if (previous != 0)
  {
    arg0 = (Arg0 *) (previous + 0x20);
    input = *((Arg1 **) (previous + 8));
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    tail_arg = active;
    ASM_TAILSLOT_PIN(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    func_80025080(tail_arg);
  }
  ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
  call_base = (Scratch *) (*state_slot);
  *((u8 **) (((u8 *) call_base) + 0x8D0)) = active->current;
  return 0;
}
