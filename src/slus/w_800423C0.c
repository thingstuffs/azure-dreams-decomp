#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define PIN_KEEP(v) ((void)0)
#else
#define PIN_KEEP(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif
typedef struct S_800E3E48
{
  u8 pad00[0x14];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x8C - 0x20];
} S_800E3E48;
typedef struct S_800423C0_Src
{
  u8 pad0[3];
  u8 unk3;
} S_800423C0_Src;
typedef struct S_800423C0_Obj
{
  u8 pad00[0x12];
  u8 unk12;
  u8 pad13[0x14 - 0x13];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x45 - 0x20];
  u8 unk45;
} S_800423C0_Obj;
extern S_800E3E48 D_800E3E48[];
extern void func_80042710(void *dst, void *src);
extern s16 func_800A1BD0(void *a0, s32 a1);
/* Copies source template data, updates object direction fields, and sets a flag. */
void func_800423C0(S_800423C0_Obj *obj, s16 unused, S_800423C0_Src *source)
{
  int next_direction;
  S_800E3E48 *template_entry;
  s32 direction;
  register s32 upper_bits_mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  if (source != 0)
  {
    S_800423C0_Obj *pinned_obj;

    template_entry = &D_800E3E48[source->unk3 & 0x1F];
    func_80042710(obj, template_entry);
    pinned_obj = obj;
    PIN_KEEP(pinned_obj);
    upper_bits_mask = -8;
    obj->unk14 &= upper_bits_mask;
    obj->unk1C &= upper_bits_mask;
    obj->unk14 |= template_entry->unk14 & 7;
    obj->unk1C |= template_entry->unk1C & 7;
    direction = func_800A1BD0(pinned_obj, upper_bits_mask);
    if (direction >= 0)
    {
      register u8 *direction_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
      u16 *other_direction = (u16 *)0x80012094;
      s32 slot_offset;

      direction_page = (u8 *)0x80010000;
      slot_offset = direction * 2;
      PIN_KEEP(direction_page);
      direction_page = (u8 *)((unsigned long)slot_offset + (unsigned long)direction_page);
      if (direction == 0)
      {
        other_direction = (u16 *)0x80012096;
      }
      direction = *(u16 *)(direction_page + 0x2094);
      if (direction == *other_direction)
      {
        next_direction = direction + 1;
        *(u16 *)(direction_page + 0x2094) = next_direction & 7;
      }
      obj->unk45 = direction_page[0x2094];
      obj->unk12 = direction_page[0x2098];
    }
  }
  obj->unk1C |= 0x20000;
}
