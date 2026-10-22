#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"
#include "slus.h"

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
}
S_80086A40;
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
}
S_80085458;
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
}
S_8005BBFC_rec;
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
}
S_8005BBFC_req;
extern s32 audio_voice_count[4];
extern s32 audio_voice_masks[64];
extern S_80085458 audio_voice_records[64];
extern s32 audio_update_guard[4];
extern S_80086A40 audio_bank_slots[16];
/* Starts a channel voice with sample, pitch, envelope, and panned volume settings. */
s32 func_8005BBFC(channel_arg, bank_arg, program_arg, tone_arg, note_arg, fine_note_arg, left_gain_arg, right_gain_arg)
s16 channel_arg;
s16 bank_arg;
s16 program_arg;
s16 tone_arg;
s16 note_arg;
s16 fine_note_arg;
u16 left_gain_arg;
u16 right_gain_arg;
{
    S_8005BBFC_req voice_request;
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
    s16 sample_index;
    s32 sample;
    u16 *sample_sizes;
    s32 pan;
    s32 pan_total;
    s32 volume;
    s32 left_volume;
    s32 right_volume;
    u8 bank_volume;
    s32 left_scaled;
    s32 right_scaled;
    u8 tone_param;
    channel = channel_arg;
    bank = bank_arg;
    program = program_arg;
    left_gain = left_gain_arg;
    tone = tone_arg;
    right_gain = right_gain_arg;
    audio_update_guard[0] = 1;
    if ((audio_voice_count[0] - 1) < channel) {
        channel = -1;
    }
    if (channel != (-1)) {
        bank_data = audio_bank_slots[bank_arg].f04;
        program_offset = ((s32) (program_arg << 0x10)) >> 0xC;
        program_data = bank_data + (program_offset + 0x20);
        note_pitch = (note_arg << 8) + fine_note_arg;
        tone_data = (S_8005BBFC_rec *) (bank_data + (((program_offset + tone_arg) << 5) + 0x820));
        if ((note_arg >= ((s32) tone_data->f06)) && (((s32) tone_data->f07) >= note_arg)) {
            sound_reset_indexed_voice_envelope(channel);
            {
                s32 * voice_ids = audio_voice_masks;
                voice_id = voice_ids + channel;
            }
            do {
                SpuSetKey(0, *voice_id);
                voice_state = SpuGetKeyStatus(*voice_id);
                if (voice_state == 2) {
                    break;
                }
            }
            while (voice_state != 0);
            sample = 0;
            left_volume = sample;
            sample_index = tone_data->f16;
            sample_sizes = (u16 *) ((audio_bank_slots[(s16) bank].f04 + ((*((u16 *) (bank_data + 0x12))) << 9)) + 0x820);
            if (sample_index > 0) {
                do {
                    left_volume += *sample_sizes;
                    sample_sizes += 1;
                    sample += 1;
                }
                while (sample < sample_index);
            }
            voice_request.f04 = 0x701EF;
            voice_request.f0c = 0;
            voice_request.f0e = 0;
            voice_request.f00 = audio_voice_masks[channel];
            left_volume <<= 3;
            voice_request.f1c = audio_bank_slots[(s16) bank].f10 + left_volume;
            adsr1 = tone_data->f10;
            voice_request.f3a = adsr1;
            audio_voice_records[channel].f60 = adsr1;
            adsr2 = tone_data->f12;
            voice_request.f3c = adsr2;
            audio_voice_records[channel].f64 = adsr2;
            if (tone_data->f10 & 0x80) {
                voice_request.f24 = 5;
            }
            else {
                voice_request.f24 = 1;
            }
            voice_request.f20 = voice_request.f1c;
            audio_voice_records[channel].f22 = tone_data->f04;
            audio_voice_records[channel].f23 = tone_data->f05;
            audio_voice_records[channel].f21 = tone_data->f0c;
            tone_param = tone_data->f0d;
            audio_voice_records[channel].f00 = channel;
            audio_voice_records[channel].f04 = program;
            audio_voice_records[channel].f08 = tone;
            audio_voice_records[channel].f0a = (s16) (note_pitch >> 8);
            audio_voice_records[channel].f06 = 0x11;
            audio_voice_records[channel].f1a = 1;
            audio_voice_records[channel].f20 = tone_param;
            audio_voice_records[channel].f14 = program_data[1];
            audio_voice_records[channel].f16 = program_data[4];
            audio_voice_records[channel].f15 = tone_data->f02;
            audio_voice_records[channel].f17 = tone_data->f03;
            audio_voice_records[channel].f5c = bank;
            pan_total = (audio_bank_slots[(s16) bank].f1b + audio_voice_records[channel].f16) + audio_voice_records[channel].f17;
            pan = pan_total - 0x80;
            if (pan < 0) {
                pan = 0;
            }
            if (!(pan < 0x80)) {
                pan = 0x7F;
            }
            audio_voice_records[channel].f18 = pan;
            volume = audio_bank_slots[(s16) bank].f18;
            volume = ((s32) ((volume * audio_voice_records[channel].f14) * audio_voice_records[channel].f15)) >> 7;
            if (pan >= 0x40) {
                right_volume = volume;
                left_volume = ((s32) ((0x40 - (pan & 0x3F)) * (right_volume << 1))) >> 7;
            }
            else {
                left_volume = volume;
                right_volume = ((s32) (pan * (left_volume << 1))) >> 7;
            }
            bank_volume = audio_bank_slots[(s16) bank].f18;
            left_volume = ((s32) (left_volume * bank_volume)) >> 7;
            right_volume = ((s32) (right_volume * bank_volume)) >> 7;
            left_scaled = left_volume * ((s16) left_gain);
            right_scaled = right_volume * ((s16) right_gain);
            audio_voice_records[channel].f10 = (s16) (left_scaled >> 7);
            audio_voice_records[channel].f12 = (u16) (right_scaled >> 7);
            voice_request.f08 = (s16) audio_voice_records[channel].f10;
            voice_request.f0a = audio_voice_records[channel].f12;
            voice_request.f16 = note_pitch;

            if (tone_data->f05 != 0) {
                voice_request.f18 = (((u8 *) tone_data)[-0x1C] << 8) | (0x7F - tone_data->f05);
            }
            else {
                voice_request.f18 = tone_data->f05 | (tone_data->f04 << 8);
            }
            apply_voice_attributes_and_key_on(&voice_request);
            if (tone_data->f01 & 4) {
                update_spu_register_pair_cc_cd(1, audio_voice_masks[channel]);
            }
            else {
                update_spu_register_pair_cc_cd(0, audio_voice_masks[channel]);
            }
        }
        else {
            channel = -1;
        }
    }
    audio_update_guard[0] = 0;
    return channel;
}
