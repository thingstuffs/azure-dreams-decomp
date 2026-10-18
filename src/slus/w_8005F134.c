#include "slus/jtbl_8005F134.h"

void func_8005F134(SpuVoiceAttr_ *attr)
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
                D_80079958[voice * 8 + 2] = attr->pitch;
            }
            if (set_all || (mask & 0x40)) {
                D_80079520[voice] = attr->sample_note;
            }
            if (set_all || (mask & 0x20)) {
                sample_note = D_80079520[voice];
                note = attr->note;
                D_80079958[reg_base + 2] =
                    func_8005F7D0(sample_note >> 8, sample_note & 0xFF, note >> 8, note & 0xFF);
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
                D_80079958[reg_base + 0] = left_volume | volume_mode;
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
                D_80079958[reg_base + 1] = right_volume | volume_mode;
            }
            if (set_all || (mask & 0x80)) {
                audio_handle_optionally_aligns_shifts_stores_returns_result(reg_base + 3, attr->addr);
            }
            if (set_all || (mask & 0x10000)) {
                audio_handle_optionally_aligns_shifts_stores_returns_result(reg_base + 7, attr->loop_addr);
            }
            if (set_all || (mask & 0x20000)) {
                D_80079958[reg_base + 4] = attr->adsr1;
            }
            if (set_all || (mask & 0x40000)) {
                D_80079958[reg_base + 5] = attr->adsr2;
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
                adsr = D_80079958[reg_base + 4];
                adsr = (adsr & 0xFF) | ((env_value | env_mode) << 8);
                D_80079958[reg_base + 4] = adsr;
            }
            if (set_all || (mask & 0x1000)) {
                env_value = attr->dr;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = D_80079958[reg_base + 4];
                adsr = (adsr & 0xFF0F) | (env_value << 4);
                D_80079958[reg_base + 4] = adsr;
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
                adsr = D_80079958[reg_base + 5];
                adsr = (adsr & 0x3F) | ((env_value | env_mode) << 6);
                D_80079958[reg_base + 5] = adsr;
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
                adsr = D_80079958[reg_base + 5];
                adsr = (adsr & 0xFFC0) | (env_value | env_mode);
                D_80079958[reg_base + 5] = adsr;
            }
            if (set_all || (mask & 0x8000)) {
                env_value = attr->sl;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = D_80079958[reg_base + 4];
                adsr = (adsr & 0xFFF0) | env_value;
                D_80079958[reg_base + 4] = adsr;
            }
        }
    }
    delay_value = 1;
    for (delay_step = 0; delay_step < 2; delay_step++) {
        delay_value = delay_value * 13;
    }
}
