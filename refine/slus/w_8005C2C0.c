#include "common.h"

typedef struct S_8005C2C0_slot
{
  s16 field_00;
  u8 pad02[0x06 - 0x02];
  s16 field_06;
  u8 pad08[0x0A - 0x08];
  s16 field_0A;
  u8 pad0C[0x10 - 0x0C];
  s16 field_10;
  u16 field_12;
  s8 field_14;
  s8 field_15;
  s8 field_16;
  s8 field_17;
  u8 pad18[0x1A - 0x18];
  s16 field_1A;
  u8 pad1C[0x22 - 0x1C];
  s8 field_22;
  s8 field_23;
  u8 pad24[0x5C - 0x24];
  s16 field_5C;
  u8 pad5E[0x78 - 0x5E];
} S_8005C2C0_slot;
typedef struct S_8005C2C0_kind
{
  u8 pad00[0x10];
  s32 field_10;
  u8 pad14[0x1C - 0x14];
} S_8005C2C0_kind;
typedef struct S_8005C2C0_req
{
  s32 field_00;
  s32 field_04;
  s16 field_08;
  u16 field_0A;
  s16 field_0C;
  s16 field_0E;
  u8 pad10[0x16 - 0x10];
  u16 field_16;
  s16 field_18;
  u8 pad1A[0x1C - 0x1A];
  s32 field_1C;
  u8 pad20[0x24 - 0x20];
  s32 field_24;
  s32 field_28;
  s32 field_2C;
  s16 field_30;
  s16 field_32;
  s16 field_34;
  s16 field_36;
  s16 field_38;
} S_8005C2C0_req;
extern s32 D_80073740[32];
extern S_8005C2C0_slot D_80085458;
extern s32 D_80085F98[4];
extern S_8005C2C0_kind D_80086A40;
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
extern void func_8005EC0C(void *a0);
/* Initialize a sound voice with the requested volume, pitch, and note. */
s16 func_8005C2C0(s16 sound_id, s32 voice_id, s16 note, unsigned short note_offset, u16 pitch, u16 left_volume, u16 right_volume)
{
  S_8005C2C0_req voice_attr;
  S_8005C2C0_kind *sounds;
  S_8005C2C0_slot *voice_slots;
  S_8005C2C0_slot *voice;
  s32 *voice_mask;
  s32 *voice_masks;
  s32 key_status;
  s32 key_off_status;
  s8 full_volume;
  D_80085F98[0] = 1;
  if (sound_id != (-1))
  {
    if (voice_id < 0x18)
    {
      func_80056DB4(voice_id);
      voice_masks = D_80073740;
      voice_mask = &voice_masks[voice_id];
      key_off_status = 2;
      do
      {
        func_8005E97C(0, *voice_mask);
        key_status = func_8005EB78(*voice_mask);
      }
      while ((key_status != key_off_status) && (key_status != 0));
      voice_attr.field_04 = 0x1FFEF;
      voice_attr.field_24 = 1;
      voice_attr.field_28 = 1;
      voice_attr.field_2C = 3;
      voice_attr.field_30 = 0;
      voice_attr.field_32 = 0;
      voice_attr.field_34 = 0;
      voice_attr.field_36 = 0;
      voice_attr.field_38 = 0;
      voice_attr.field_0C = 0;
      voice_attr.field_0E = 0;
      sounds = &D_80086A40;
      voice_slots = &D_80085458;
      voice_attr.field_00 = *voice_mask;
      voice_attr.field_1C = sounds[sound_id].field_10;
      full_volume = 0x7F;
      ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
      voice = &voice_slots[voice_id];
      voice->field_06 = 0x11;
      voice->field_16 = 0x40;
      voice->field_17 = 0x40;
      voice->field_14 = full_volume;
      voice->field_15 = full_volume;
      voice->field_10 = left_volume << 7;
      voice->field_00 = voice_id;
      voice->field_1A = 1;
      voice->field_22 = note;
      voice->field_23 = note_offset;
      voice->field_0A = pitch;
      voice->field_5C = sound_id;
      voice->field_12 = right_volume << 7;
      voice_attr.field_08 = voice->field_10;
      voice_attr.field_0A = voice->field_12;
      voice_attr.field_16 = pitch;
      if (note_offset & 0xFFFF)
      {
        voice_attr.field_18 = ((note - 1) << 8) | (0x7F - note_offset);
      }
      else
      {
        voice_attr.field_18 = note_offset | (note << 8);
      }
      func_8005EC0C(&voice_attr);
    }
  }
  D_80085F98[0] = 0;
  return voice_id;
}
