#include "common.h"
typedef struct S_80086A40
{
  s16 unk0;
  s16 unk2;
  u8 *unk4;
  u8 pad08[0x10 - 0x08];
  s32 unk10;
  u8 pad14[0x18 - 0x14];
  u8 unk18;
  u8 pad19[0x1B - 0x19];
  u8 unk1B;
} S_80086A40;
typedef struct S_80085458
{
  s16 unk00;
  u8 pad02[0x04 - 0x02];
  s16 unk04;
  s16 unk06;
  s16 unk08;
  s16 unk0A;
  u8 pad0C[0x10 - 0x0C];
  s16 unk10;
  s16 unk12;
  u8 unk14;
  u8 unk15;
  u8 unk16;
  u8 unk17;
  s16 unk18;
  u16 unk1A;
  u8 pad1C[0x20 - 0x1C];
  u8 unk20;
  u8 unk21;
  u8 unk22;
  u8 unk23;
  u8 pad24[0x5C - 0x24];
  s16 unk5C;
  u8 pad5E[0x60 - 0x5E];
  s32 unk60;
  s32 unk64;
  u8 pad68[0x78 - 0x68];
} S_80085458;
typedef struct S_8005B4D0_hdr
{
  u8 unk00;
  u8 unk01;
  u8 pad02[0x04 - 0x02];
  u8 unk04;
  u8 pad05[0x10 - 0x05];
} S_8005B4D0_hdr;
typedef struct S_8005B4D0_data
{
  u8 pad00[0x01 - 0x00];
  u8 unk01;
  u8 unk02;
  u8 unk03;
  u8 unk04;
  u8 unk05;
  u8 unk06;
  u8 unk07;
  u8 pad08[0x0C - 0x08];
  u8 unk0C;
  u8 unk0D;
  u8 pad0E[0x10 - 0x0E];
  u16 unk10;
  u16 unk12;
  u8 pad14[0x16 - 0x14];
  s16 unk16;
  u8 pad18[0x20 - 0x18];
} S_8005B4D0_data;
typedef struct S_8005B4D0_req
{
  s32 f00;
  s32 f04;
  s16 f08;
  s16 f0a;
  s16 f0c;
  s16 f0e;
  u8 pad10[0x16 - 0x10];
  s16 f16;
  s16 f18;
  u8 pad1a[0x1C - 0x1A];
  s32 f1c;
  s32 f20;
  s32 f24;
  u8 pad28[0x3A - 0x28];
  s16 f3a;
  s16 f3c;
  u8 pad3e[0x40 - 0x3E];
} S_8005B4D0_req;
extern s32 D_80073734[4];
extern s32 D_80073740[128];
extern S_80085458 D_80085458[64];
extern s32 D_80085F98[4];
extern S_80086A40 D_80086A40[16];
extern S_80086A40 D_80086A40_C[16] __asm__("D_80086A40");
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 arg0);
extern void func_8005EC0C(void *a0);
extern s32 func_8005E4A0(s32 a0, s32 a1);
/* Allocates and configures voices for program tones matching the requested note. */
void func_8005B4D0(s32 bank_program, s32 note_pitch, s16 left_gain, s16 right_gain, s32 force_effect)
{
  S_8005B4D0_req voice_req;
  u16 left_scale;
  u16 right_scale;
  s32 note;
  s32 used_programs;
  u8 *bank_data;
  u8 *bank_header;
  S_8005B4D0_hdr *program;
  S_8005B4D0_data *tone;
  s32 bank_id;
  s32 program_id;
  s32 voice_slot;
  s32 tone_id;
  s32 entry_index;
  u8 *program_cursor;
  s32 voice_status;
  s32 sample_offset;
  s32 sample_id;
  s16 *sample_sizes;
  s32 pan;
  s32 volume;
  s32 left_volume;
  s32 right_volume;
  u16 adsr1;
  u16 adsr2;
  s32 scaled_left;
  s32 scaled_right;
  s32 bank_index;
  entry_index = 0;
  used_programs = 0;
  program_id = bank_program & 0x7F;
  bank_index = bank_program >> 8;
  D_80085F98[0] = 1;
  left_scale = left_gain;
  right_scale = right_gain;
  bank_header = D_80086A40[(s16) bank_index].unk4;
  bank_id = bank_index;
  bank_data = bank_header;
  if (program_id != 0)
  {
    program_cursor = bank_header;
    do
    {
      if (((S_8005B4D0_hdr *) (program_cursor + 0x20))->unk00 != 0)
      {
        used_programs += 1;
      }
      program_cursor += 0x10;
      entry_index += 1;
    }
    while (entry_index < program_id);
  }

  tone_id = 0;
  program = (S_8005B4D0_hdr *) (bank_data + ((program_id * 0x10) + 0x20));
  note = note_pitch >> 8;
  if (program->unk00 == 0)
  {
    D_80085F98[0] = 0;
    return;
  }
  do
  {
    tone = (S_8005B4D0_data *) (bank_data + ((((used_programs * 0x10) + tone_id) << 5) + 0x820));
    if ((note >= ((s32) tone->unk06)) && (((s32) tone->unk07) >= note))
    {
      voice_slot = 0;
      while (1)
      {
        if (func_8005EB78(D_80073740[voice_slot]) == 0)
        {
          break;
        }
        voice_slot += 1;
        if ((D_80073734[0] - 1) < voice_slot)
        {
          voice_slot = -1;
          break;
        }
      }

      if (voice_slot == (-1))
      {
        voice_slot = 0;
        while (1)
        {
          if (D_80085458[voice_slot].unk1A == 0)
          {
            break;
          }
          voice_slot += 1;
          if ((D_80073734[0] - 1) < voice_slot)
          {
            voice_slot = -1;
            break;
          }
        }

      }
      if (voice_slot != (-1))
      {
        func_80056DB4(voice_slot);
        do
        {
          func_8005E97C(0, D_80073740[voice_slot]);
          voice_status = func_8005EB78(D_80073740[voice_slot]);
        }
        while ((voice_status != 2) && (voice_status != 0));
        entry_index = 0;
        sample_offset = 0;
        sample_sizes = (s16 *) ((D_80086A40[(s16) bank_id].unk4 + ((*((u16 *) (bank_header + 0x12))) << 9)) + 0x820);
        sample_id = tone->unk16;
        if (sample_id > 0)
        {
          do
          {
            sample_offset += *((u16 *) sample_sizes);
            sample_sizes += 1;
            entry_index += 1;
          }
          while (entry_index < sample_id);
        }
        sample_offset <<= 3;
        voice_req.f04 = 0x701EF;
        voice_req.f0c = 0;
        voice_req.f0e = 0;
        voice_req.f00 = D_80073740[voice_slot];
        voice_req.f1c = D_80086A40_C[(s16) bank_id].unk10 + sample_offset;
        adsr1 = tone->unk10;
        voice_req.f3a = adsr1;
        D_80085458[voice_slot].unk60 = adsr1;
        adsr2 = tone->unk12;
        voice_req.f3c = adsr2;
        D_80085458[voice_slot].unk64 = adsr2;
        if (tone->unk10 & 0x80)
        {
          voice_req.f24 = 5;
        }
        else
        {
          voice_req.f24 = 1;
        }
        voice_req.f20 = voice_req.f1c;
        D_80085458[voice_slot].unk22 = tone->unk04;
        D_80085458[voice_slot].unk23 = tone->unk05;
        D_80085458[voice_slot].unk21 = tone->unk0C;
        D_80085458[voice_slot].unk20 = tone->unk0D;
        D_80085458[voice_slot].unk00 = voice_slot;
        D_80085458[voice_slot].unk04 = program_id;
        D_80085458[voice_slot].unk08 = tone_id;
        D_80085458[voice_slot].unk0A = note_pitch >> 8;
        D_80085458[voice_slot].unk06 = 0x11;
        D_80085458[voice_slot].unk1A = 1;
        D_80085458[voice_slot].unk14 = program->unk01;
        D_80085458[voice_slot].unk16 = program->unk04;
        D_80085458[voice_slot].unk15 = tone->unk02;
        D_80085458[voice_slot].unk17 = tone->unk03;
        D_80085458[voice_slot].unk5C = bank_id;
        pan = ((D_80086A40[(s16) bank_id].unk1B + D_80085458[voice_slot].unk16) + D_80085458[voice_slot].unk17) - 0x80;
        if (pan < 0)
        {
          pan = 0;
        }
        if (pan >= 0x80)
        {
          pan = 0x7F;
        }
        D_80085458[voice_slot].unk18 = pan;
        volume = ((D_80086A40[(s16) bank_id].unk18 * D_80085458[voice_slot].unk14) * D_80085458[voice_slot].unk15) >> 7;
        if (pan >= 0x40)
        {
          right_volume = volume;
          left_volume = ((0x40 - (pan & 0x3F)) * (right_volume << 1)) >> 7;
        }
        else
        {
          left_volume = volume;
          right_volume = (pan * (left_volume << 1)) >> 7;
        }
        left_volume = (left_volume * D_80086A40[(s16) bank_id].unk18) >> 7;
        right_volume = (right_volume * D_80086A40[(s16) bank_id].unk18) >> 7;
        scaled_left = left_volume * left_scale;
        scaled_right = right_volume * right_scale;
        D_80085458[voice_slot].unk10 = scaled_left >> 7;
        D_80085458[voice_slot].unk12 = scaled_right >> 7;
        voice_req.f08 = (u16) D_80085458[voice_slot].unk10;
        voice_req.f0a = D_80085458[voice_slot].unk12;
        voice_req.f16 = note_pitch;
        if (tone->unk05 != 0)
        {
          voice_req.f18 = ((tone->unk04 - 1) << 8) | (0x7F - tone->unk05);
        }
        else
        {
          voice_req.f18 = (tone->unk04 << 8) | tone->unk05;
        }
        func_8005EC0C(&voice_req);
        if ((tone->unk01 & 4) || (force_effect != 0))
        {
          func_8005E4A0(1, D_80073740[voice_slot]);
        }
        else
        {
          func_8005E4A0(0, D_80073740[voice_slot]);
        }
      }
    }
    tone_id += 1;
  }
  while (tone_id < ((s32) program->unk00));
  D_80085F98[0] = 0;
}
