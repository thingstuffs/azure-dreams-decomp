#include "common.h"

typedef struct 
{
  s16 f00;
  u8 pad02[2];
  u8 *f04;
  u8 pad08[8];
  s32 f10;
  u8 pad14[4];
  u8 f18;
  u8 pad19[2];
  u8 f1b;
} S_80086A40;
typedef struct 
{
  s16 f00;
  s16 f02;
  u16 f04;
  u16 f06;
  s16 f08;
  u16 f0a;
  u8 pad0c[4];
  s16 f10;
  u16 f12;
  u8 f14;
  u8 f15;
  u8 f16;
  u8 f17;
  s16 f18;
  u16 f1a;
  u8 pad1c[4];
  u8 f20;
  u8 f21;
  u8 f22;
  u8 f23;
  u8 pad24[0x38];
  u16 f5c;
  u8 pad5e[2];
  s32 f60;
  s32 f64;
  u8 pad68[0x10];
} S_80085458;
typedef struct 
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u8 f04;
  u8 f05;
  u8 f06;
  u8 f07;
  u8 pad08[4];
  u8 f0c;
  u8 f0d;
  u8 pad0e[2];
  u16 f10;
  u16 f12;
  u8 pad14[2];
  s16 f16;
} S_8005BBFC_rec;
typedef struct 
{
  s32 f00;
  s32 f04;
  s16 f08;
  u16 f0a;
  s16 f0c;
  s16 f0e;
  u8 pad10[6];
  s16 f16;
  s16 f18;
  u8 pad1a[2];
  s32 f1c;
  s32 f20;
  s32 f24;
  u8 pad28[0x12];
  u16 f3a;
  u16 f3c;
  u8 pad3e[2];
} S_8005BBFC_req;
extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern S_80085458 D_80085458[64];
extern s32 D_80085F98[4];
extern S_80086A40 D_80086A40[16];
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
extern void func_8005EC0C(void *a0);
extern s32 func_8005E4A0(s32 a0, s32 a1);
enum E_u16 { E_u16_zero = 0, E_u16_max = 0xFFFF } __attribute__((packed));
/* Starts a channel voice with sample, pitch, envelope, and panned volume settings. */
s32 func_8005BBFC(channel_arg, bank_arg, program_arg, tone_arg, note_arg, fine_note_arg, left_gain_arg, right_gain_arg)
s32 channel_arg;
s32 bank_arg;
s32 program_arg;
s32 tone_arg;
volatile s32 note_arg;
s32 fine_note_arg;
enum E_u16 left_gain_arg;
enum E_u16 right_gain_arg;
{
  S_8005BBFC_req req;
  u16 program;
  u16 left_gain;
  u16 right_gain;
  s32 channel;
  s16 bank;
  s16 tone;
  u8 *bank_data;
  u8 *program_data;
  S_8005BBFC_rec *tone_data;
  u16 adsr1;
  u16 adsr2;
  s32 program_offset;
  s32 note_pitch;
  s32 *voice_id;
  s32 voice_state;
  s32 sample_offset;
  s16 sample_index;
  register s32 sample ASM_REG("$6");
  u16 *sample_sizes;
  register s32 pan ASM_REG("$3");
  register s32 pan_total ASM_REG("$2");
  s32 volume;
  s32 left_volume;
  s32 right_volume;
  u8 bank_volume;
  s32 left_scaled;
  s32 right_scaled;
  u8 tone_param;
  s32 note;
  register s32 fine_note ASM_REG("$9");
  channel = (s16) channel_arg;
  note = note_arg;
  bank = bank_arg;
  fine_note = fine_note_arg;
  program = program_arg;
  left_gain = left_gain_arg;
  tone = tone_arg;
  right_gain = right_gain_arg;
  D_80085F98[0] = 1;
  if ((D_80073734[0] - 1) < channel)
  {
    channel = -1;
  }
  if (channel != (-1))
  {
    bank_data = D_80086A40[(s16) bank_arg].f04;
    program_offset = ((s32) (program_arg << 0x10)) >> 0xC;
    program_data = bank_data + (program_offset + 0x20);
    note_pitch = (((s16) note) << 8) + ((s16) fine_note);
    tone_data = (S_8005BBFC_rec *) (bank_data + (((program_offset + ((s16) tone_arg)) << 5) + 0x820));
    if ((((s16) note) >= ((s32) tone_data->f06)) && (((s32) tone_data->f07) >= ((s16) note)))
    {
      ASM_USE_NV(fine_note);
      func_80056DB4(channel);
      { s32 *voice_ids = D_80073740; voice_id = voice_ids + channel; }
      do
      {
        func_8005E97C(0, *voice_id);
        voice_state = func_8005EB78(*voice_id);
        if (voice_state == 2)
        {
          break;
        }
      }
      while (voice_state != 0);
      sample = 0;
      sample_offset = sample;
      sample_index = tone_data->f16;
      sample_sizes = (u16 *) ((D_80086A40[(s16) bank].f04 + ((*((u16 *) (bank_data + 0x12))) << 9)) + 0x820);
      if (sample_index > 0)
      {
        do
        {
          sample_offset += *sample_sizes;
          sample_sizes += 1;
          sample += 1;
        }
        while (sample < sample_index);
      }
      req.f04 = 0x701EF;
      req.f0c = 0;
      req.f0e = 0;
      req.f00 = D_80073740[channel];
      sample_offset <<= 3;
      req.f1c = D_80086A40[(s16) bank].f10 + sample_offset;
      adsr1 = tone_data->f10;
      req.f3a = adsr1;
      D_80085458[channel].f60 = adsr1;
      adsr2 = tone_data->f12;
      req.f3c = adsr2;
      D_80085458[channel].f64 = adsr2;
      if (tone_data->f10 & 0x80)
      {
        req.f24 = 5;
      }
      else
      {
        req.f24 = 1;
      }
      req.f20 = req.f1c;
      D_80085458[channel].f22 = tone_data->f04;
      D_80085458[channel].f23 = tone_data->f05;
      D_80085458[channel].f21 = tone_data->f0c;
      tone_param = tone_data->f0d;
      D_80085458[channel].f00 = channel;
      D_80085458[channel].f04 = program;
      D_80085458[channel].f0a = (s16) (note_pitch >> 8);
      D_80085458[channel].f06 = 0x11;
      D_80085458[channel].f08 = tone;
      ASM_USE_NV(tone);
      D_80085458[channel].f1a = 1;
      D_80085458[channel].f20 = tone_param;
      D_80085458[channel].f14 = program_data[1];
      D_80085458[channel].f16 = program_data[4];
      ASM_USE_NV(program_data);
      D_80085458[channel].f15 = tone_data->f02;
      D_80085458[channel].f17 = tone_data->f03;
      D_80085458[channel].f5c = bank;
      pan_total = (D_80086A40[(s16) bank].f1b + D_80085458[channel].f16) + D_80085458[channel].f17;
      pan = pan_total - 0x80;
      if (pan < 0)
      {
        pan = 0;
      }
      if (!(pan < 0x80))
      {
        pan = 0x7F;
      }
      D_80085458[channel].f18 = pan;
      volume = ((s32) ((D_80086A40[(s16) bank].f18 * D_80085458[channel].f14) * D_80085458[channel].f15)) >> 7;
      if (pan >= 0x40)
      {
        right_volume = volume;
        left_volume = ((s32) ((0x40 - (pan & 0x3F)) * (right_volume << 1))) >> 7;
      }
      else
      {
        left_volume = volume;
        right_volume = ((s32) (pan * (left_volume << 1))) >> 7;
      }
      bank_volume = D_80086A40[(s16) bank].f18;
      left_volume = ((s32) (left_volume * bank_volume)) >> 7;
      right_volume = ((s32) (right_volume * bank_volume)) >> 7;
      left_scaled = left_volume * ((s16) left_gain);
      right_scaled = right_volume * ((s16) right_gain);
      D_80085458[channel].f10 = (s16) (left_scaled >> 7);
      D_80085458[channel].f12 = (u16) (right_scaled >> 7);
      req.f08 = (s16) D_80085458[channel].f10;
      req.f0a = D_80085458[channel].f12;
      req.f16 = note_pitch;
      ASM_USE_NV(note_pitch);

      if (tone_data->f05 != 0)
      {
        req.f18 = (((u8 *) tone_data)[-0x1C] << 8) | (0x7F - tone_data->f05);
      }
      else
      {
        req.f18 = tone_data->f05 | (tone_data->f04 << 8);
      }
      func_8005EC0C(&req);
      if (tone_data->f01 & 4)
      {
        func_8005E4A0(1, D_80073740[channel]);
      }
      else
      {
        func_8005E4A0(0, D_80073740[channel]);
      }
    }
    else
    {
      channel = -1;
    }
  }
  D_80085F98[0] = 0;
  return channel;
}
