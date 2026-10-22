/* SPU voice attribute writes, attribute reads and selected voice key-state queries. */
#include "slus/jtbl_8005F134.h"
#include "common.h"
#include "engine/audio/spu.h"



/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */


/* Returns the active/key-on state of the first selected voice, or -1 if none is selected. */
s32 SpuGetKeyStatus(s32 voice_mask)
{
    s32 voice;
    s32 bit_base;
    s32 voice_index;
    s32 result;
    u16 active;

    voice = -1;
    voice_index = 0;
    bit_base = 1;
    for (; voice_index < 24; voice_index++) {
        if ((voice_mask & (bit_base << voice_index)) != 0) {
            voice = voice_index;
            break;
        }
    }

    result = -1;
    if (voice == result) {
        return result;
    }

    voice_mask = voice << 4;
    result = (s32)spu_registers;
    voice_index = spu_active_voice_mask;
    voice_mask = voice_mask + result;
    result = 1;
    result = result << voice;
    voice_index = voice_index & result;
    active = *(u16 *)(voice_mask + 0xC);
    if (voice_index != 0) {
        if (active != 0) {
            return 1;
        }
        return 3;
    }

    return active != 0 ? 2 : 0;
}

/* Applies masked pitch, volume, sample-address and envelope settings to the selected SPU voices. */
void apply_spu_voice_attributes(SpuVoiceAttr_ *attr)
{
    s32 voice;
    u32 mask;
    s32 reg_base;
    s32 set_all;
    s32 left_volume;
    s32 right_volume;
    s32 volume_mode;
    s32 env_mode;
    u16 env_value;
    u16 adsr;
    u16 raw_volume;
    u16 sample_note;
    u16 note;
    s16 mode_offset;
    s32 mode_index;
    volatile s32 delay_step;
    volatile s32 delay_value;

    mask = attr->mask;
    set_all = (mask == 0);
    for (voice = 0; voice < 24; voice++) {
        if (attr->voice & (1 << voice)) {
            reg_base = voice * 8;
            if (set_all || (mask & 0x10)) {
                spu_registers[voice * 8 + 2] = attr->pitch;
            }
            if (set_all || (mask & 0x40)) {
                spu_voice_sample_notes[voice] = attr->sample_note;
            }
            if (set_all || (mask & 0x20)) {
                sample_note = spu_voice_sample_notes[voice];
                note = attr->note;
                spu_registers[reg_base + 2] =
                    _spu_note2pitch(sample_note >> 8, sample_note & 0xFF, note >> 8, note & 0xFF);
            }
            if (set_all || (mask & 0x1)) {
                volume_mode = 0;
                raw_volume = attr->volume.left;
                left_volume = raw_volume & 0x7FFF;
                if (set_all || (mask & 0x4)) {
                    mode_offset = attr->volmode.left - 1;
                    mode_index = mode_offset;
                    switch (mode_index) {
                    case 0:
                        volume_mode = 0x8000;
                        break;
                    case 1:
                        volume_mode = 0x9000;
                        break;
                    case 2:
                        volume_mode = 0xA000;
                        break;
                    case 3:
                        volume_mode = 0xB000;
                        break;
                    case 4:
                        volume_mode = 0xC000;
                        break;
                    case 5:
                        volume_mode = 0xD000;
                        break;
                    case 6:
                        volume_mode = 0xE000;
                        break;
                    default:
                        break;
                    }
                }
                if (volume_mode != 0) {
                    if (attr->volume.left >= 0x80) {
                        left_volume = 0x7F;
                    } else if (attr->volume.left < 0) {
                        left_volume = 0;
                    }
                }
                spu_registers[reg_base + 0] = left_volume | volume_mode;
            }
            if (set_all || (mask & 0x2)) {
                volume_mode = 0;
                raw_volume = attr->volume.right;
                right_volume = raw_volume & 0x7FFF;
                if (set_all || (mask & 0x8)) {
                    mode_offset = attr->volmode.right - 1;
                    mode_index = mode_offset;
                    switch (mode_index) {
                    case 0:
                        volume_mode = 0x8000;
                        break;
                    case 1:
                        volume_mode = 0x9000;
                        break;
                    case 2:
                        volume_mode = 0xA000;
                        break;
                    case 3:
                        volume_mode = 0xB000;
                        break;
                    case 4:
                        volume_mode = 0xC000;
                        break;
                    case 5:
                        volume_mode = 0xD000;
                        break;
                    case 6:
                        volume_mode = 0xE000;
                        break;
                    default:
                        break;
                    }
                }
                if (volume_mode != 0) {
                    if (attr->volume.right >= 0x80) {
                        right_volume = 0x7F;
                    } else if (attr->volume.right < 0) {
                        right_volume = 0;
                    }
                }
                spu_registers[reg_base + 1] = right_volume | volume_mode;
            }
            if (set_all || (mask & 0x80)) {
                _spu_FsetRXXa(reg_base + 3, attr->addr);
            }
            if (set_all || (mask & 0x10000)) {
                _spu_FsetRXXa(reg_base + 7, attr->loop_addr);
            }
            if (set_all || (mask & 0x20000)) {
                spu_registers[reg_base + 4] = attr->adsr1;
            }
            if (set_all || (mask & 0x40000)) {
                spu_registers[reg_base + 5] = attr->adsr2;
            }
            if (set_all || (mask & 0x800)) {
                env_value = attr->ar;
                if (env_value >= 0x80) {
                    env_value = 0x7F;
                }
                env_mode = 0;
                if (set_all || (mask & 0x100)) {
                    if (attr->a_mode == 5) {
                        env_mode = 0x80;
                    }
                }
                adsr = spu_registers[reg_base + 4];
                adsr = (adsr & 0xFF) | ((env_value | env_mode) << 8);
                spu_registers[reg_base + 4] = adsr;
            }
            if (set_all || (mask & 0x1000)) {
                env_value = attr->dr;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = spu_registers[reg_base + 4];
                adsr = (adsr & 0xFF0F) | (env_value << 4);
                spu_registers[reg_base + 4] = adsr;
            }
            if (set_all || (mask & 0x2000)) {
                env_value = attr->sr;
                if (env_value >= 0x80) {
                    env_value = 0x7F;
                }
                env_mode = 0x100;
                if (set_all || (mask & 0x200)) {
                    switch (attr->s_mode) {
                    case 1:
                        env_mode = 0;
                        break;
                    case 5:
                        env_mode = 0x200;
                        break;
                    case 7:
                        env_mode = 0x300;
                        break;
                    }
                }
                adsr = spu_registers[reg_base + 5];
                adsr = (adsr & 0x3F) | ((env_value | env_mode) << 6);
                spu_registers[reg_base + 5] = adsr;
            }
            if (set_all || (mask & 0x4000)) {
                env_value = attr->rr;
                if (env_value >= 0x20) {
                    env_value = 0x1F;
                }
                env_mode = 0;
                if (set_all || (mask & 0x400)) {
                    switch (attr->r_mode) {
                    case 3:
                        env_mode = 0;
                        break;
                    case 7:
                        env_mode = 0x20;
                        break;
                    }
                }
                adsr = spu_registers[reg_base + 5];
                adsr = (adsr & 0xFFC0) | (env_value | env_mode);
                spu_registers[reg_base + 5] = adsr;
            }
            if (set_all || (mask & 0x8000)) {
                env_value = attr->sl;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = spu_registers[reg_base + 4];
                adsr = (adsr & 0xFFF0) | env_value;
                spu_registers[reg_base + 4] = adsr;
            }
        }
    }
    delay_value = 1;
    for (delay_step = 0; delay_step < 2; delay_step++) {
        delay_value = delay_value * 13;
    }
}

/* Read volume, pitch, addresses, and envelope settings for the first selected voice. */
void SpuGetVoiceAttr(SpuVoiceAttr_ *voice_attr)
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
    voice_regs = (S_8005FA34_ent *)spu_registers;
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
    pitch_regs = (u16 *) spu_registers;
    voice_attr->volmode.left = left_mode;
    voice_attr->volumex.left = pitch_regs[volume_word + 0x100];
    voice_attr->volumex.right = pitch_regs[volume_word + 0x101];
    pitch = pitch_regs[voice_word + 2];
    voice_attr->pitch = pitch;
    volume_or_note = spu_voice_sample_notes[voice_index];
    note = _spu_pitch2note(volume_or_note >> 8, volume_or_note & 0xFF, pitch);
    if (note >= 0) {
        voice_attr->note = (u16) note;
    }
    else {
        voice_attr->note = 0;
    }
    voice_attr->sample_note = spu_voice_sample_notes[voice_index];
    envelope_regs = (u16 *) spu_registers;
    address_shift = spu_address_unit_shift;
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
