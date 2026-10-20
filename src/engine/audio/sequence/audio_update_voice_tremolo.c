#include "common.h"


typedef struct S_80084918
{
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
}
S_80084918;
typedef struct S_80055E84
{
    u16 unk0;
    u8 pad2[0xE];
    u16 unk10;
    u16 unk12;
    u8 pad14[0x2D];
    u8 unk41;
    u8 unk42;
    s8 unk43;
    u8 unk44;
    u8 pad45[3];
    s32 unk48;
    s32 unk4C;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 pad53;
    s32 unk54;
    s32 unk58;
    u8 pad5c[0x10];
    s16 unk6C;
}
S_80055E84;
extern S_80084918 audio_voice_request;
extern s16 voice_tremolo_left_volume_alias[8];
extern s32 audio_voice_masks[];
extern s32 func_8005F134(S_80084918 *arg);
/* Advance volume modulation and apply the updated channel volumes. */
void audio_update_voice_tremolo(S_80055E84 *voice)
{
    s32 scaled_offset;
    s8 phase;
    s32 volume;
    if (voice->unk4C != 0) {
        if (voice->unk42 != voice->unk50) {
            voice->unk42 = voice->unk42 + 1;
        }
        else {
            if (voice->unk44 >= voice->unk51) {
                voice->unk48 = voice->unk4C;
            }
            else {
                if (voice->unk44 != 0) {
                    voice->unk48 = voice->unk48 + voice->unk54;
                }
                else {
                    voice->unk48 = voice->unk54;
                }
                voice->unk44 = voice->unk44 + 1;
            }
            voice->unk43 = voice->unk43 + voice->unk52;
            voice->unk41 = 0;
            phase = voice->unk43;
            if (phase < 0) {
                s8 double_phase;
                s8 wave;
                s32 phase_mag = -phase;
                double_phase = phase_mag << 1;
                wave = double_phase;
                if ((phase_mag << 25) < 0) {
                    wave = -double_phase;
                }
                scaled_offset = voice->unk48 * (s8) wave;
                if (scaled_offset > 0) {
                    scaled_offset = -scaled_offset;
                }
            }
            else {
                s8 double_phase;
                s8 wave;
                s32 phase_mag = phase;
                double_phase = phase_mag << 1;
                wave = double_phase;
                if ((phase_mag << 25) < 0) {
                    wave = -double_phase;
                }
                scaled_offset = voice->unk48 * (s8) wave;
                if (scaled_offset < 0) {
                    scaled_offset = -scaled_offset;
                }
            }
            if (scaled_offset != 0) {
                voice->unk58 = (scaled_offset / 256);
            }
            else {
                voice->unk58 = 0;
            }
        }
        if (voice->unk6C != voice->unk58) {
            voice->unk6C = (u16) voice->unk58;
            audio_voice_request.field4 = 0xF;
            audio_voice_request.field0 = audio_voice_masks[voice->unk0];
            volume = voice->unk10 + voice->unk58;
            if (volume < 0) {
                volume = 0;
            }
            else if (volume >= 0x4000) {
                volume = 0x3FFF;
            }
            voice_tremolo_left_volume_alias[0] = volume;
            volume = voice->unk12 + voice->unk58;
            if (volume < 0) {
                volume = 0;
            }
            else if (volume >= 0x4000) {
                volume = 0x3FFF;
            }
            audio_voice_request.fieldA = volume;
            audio_voice_request.fieldC = 0;
            audio_voice_request.fieldE = 0;
            func_8005F134(&audio_voice_request);
        }
    }
}
