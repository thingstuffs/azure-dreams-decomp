#include "slus/jtbl_8005F134.h"

/* Read volume, pitch, addresses, and envelope settings for the first selected voice. */
void func_8005FA34(SpuVoiceAttr_ *voice_attr)
{
    s32 voice_index;
    s32 voice_bit;
    S_8005FA34_ent *voice_regs;
    S_8005FA34_ent *voice;
    s32 voice_offset;
    u16 *pitch_regs;
    u16 *envelope_regs;
    s32 volume_or_note;
    s32 right_volume;
    s16 left_mode;
    s16 right_mode;
    u16 pitch;
    s32 note;
    s32 address_shift;
    s32 voice_word;
    s32 volume_word;
    voice_index = -1;
    for (voice_bit = 0; voice_bit < 0x18; voice_bit++) {
        if (voice_attr->voice & (1 << voice_bit)) {
            voice_index = voice_bit;
            break;
        }
    }

    if (voice_index == (-1)) {
        return;
    }
    left_mode = 0;
    voice_offset = voice_index * 16;
    voice_regs = (S_8005FA34_ent *)D_80079958;
    volume_word = voice_index * 2;
    voice_word = voice_index * 8;
    voice = (S_8005FA34_ent *)(voice_offset + (u32)voice_regs);
    volume_or_note = voice->unk0;
    do {
        right_volume = voice->unk2;
    } while (0);
    if (volume_or_note & 0x8000) {
        switch (volume_or_note & 0xF000) {
        case 0x8000:
            left_mode = 1;
            break;

        case 0x9000:
            left_mode = 2;
            break;

        case 0xA000:
            left_mode = 3;
            break;

        case 0xB000:
            left_mode = 4;
            break;

        case 0xC000:
            left_mode = 5;
            break;

        case 0xD000:
            left_mode = 6;
            break;

        case 0xE000:
            left_mode = 7;
            break;

        case 0xF000:
            left_mode = 7;
            break;

        }

        volume_or_note &= 0xFFF;
    }
    right_mode = 0;
    if (right_volume & 0x8000) {
        switch (right_volume & 0xF000) {
        case 0x8000:
            right_mode = 1;
            break;

        case 0x9000:
            right_mode = 2;
            break;

        case 0xA000:
            right_mode = 3;
            break;

        case 0xB000:
            right_mode = 4;
            break;

        case 0xC000:
            right_mode = 5;
            break;

        case 0xD000:
            right_mode = 6;
            break;

        case 0xE000:
            right_mode = 7;
            break;

        case 0xF000:
            right_mode = 7;
            break;

        }

        right_volume &= 0xFFF;
    }
    {
        u32 sign_bias = 0x8000;
        u32 volume_bits = (u16) volume_or_note;
        voice_attr->volume.left = (volume_bits < 0x4000U) ? volume_or_note : (volume_bits - sign_bias);
    }
    {
        u32 sign_bias = 0x8000;
        u32 volume_bits = (u16) right_volume;
        voice_attr->volume.right = (volume_bits < 0x4000U) ? right_volume : (volume_bits - sign_bias);
    }
    voice_attr->volmode.right = right_mode;
    pitch_regs = (u16 *) D_80079958;
    voice_attr->volmode.left = left_mode;
    voice_attr->volumex.left = pitch_regs[volume_word + 0x100];
    voice_attr->volumex.right = pitch_regs[volume_word + 0x101];
    pitch = pitch_regs[voice_word + 2];
    voice_attr->pitch = pitch;
    volume_or_note = D_80079520[voice_index];
    note = sound_convert_pitch_to_packed_note(volume_or_note >> 8, volume_or_note & 0xFF, pitch);
    if (note >= 0) {
        voice_attr->note = (u16) note;
    }
    else {
        voice_attr->note = 0;
    }
    voice_attr->sample_note = D_80079520[voice_index];
    envelope_regs = (u16 *) D_80079958;
    address_shift = D_80079980;
    voice_attr->envx = envelope_regs[voice_word + 6];
    voice_attr->addr = ((s32) envelope_regs[voice_word + 3]) << address_shift;
    voice_attr->loop_addr = ((s32) envelope_regs[voice_word + 7]) << address_shift;
    {
        u16 adsr_low;
        u16 adsr_high;

        adsr_low = envelope_regs[voice_word + 4];
        adsr_high = envelope_regs[voice_word + 5];
        if (adsr_low & 0x8000) {
            voice_attr->a_mode = 5;
        }
        else {
            voice_attr->a_mode = 1;
        }
        if ((adsr_high & 0xE000) == 0xC000) {
            voice_attr->s_mode = 7;
        }
        else if ((adsr_high & 0xE000) == 0x8000) {
            voice_attr->s_mode = 5;
        }
        else if ((adsr_high & 0xE000) == 0x4000) {
            voice_attr->s_mode = 3;
        }
        else {
            voice_attr->s_mode = 1;
        }
        if (adsr_high & 0x20) {
            voice_attr->r_mode = 7;
        }
        else {
            voice_attr->r_mode = 3;
        }
        voice_attr->ar = (s16) ((adsr_low >> 8) & 0x3F);
        voice_attr->dr = (s16) ((adsr_low & 0xF0) >> 4);
        voice_attr->sr = (s16) ((adsr_high >> 6) & 0x7F);
        voice_attr->rr = (s16) (adsr_high & 0x1F);
        voice_attr->sl = (s16) (adsr_low & 0xF);
        voice_attr->adsr1 = adsr_low;
        voice_attr->adsr2 = adsr_high;
    }
}
