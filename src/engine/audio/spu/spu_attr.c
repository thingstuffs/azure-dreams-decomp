/* SPU common volume and input attributes, plus guarded reverb enabling. */
#include "slus/jtbl_8005EDA0.h"
#include "common.h"
#include "engine/audio/spu.h"



/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */


/* Enables/disables SPU reverb and mirrors the active flag in D_800794F8. */
s32 SpuSetReverb(s32 enable)
{
    u16 spu_control;

    switch (enable) {
    case 0:
        spu_control = spu_registers->spucnt;
        spu_reverb_enabled = 0;
        spu_control &= ~0x80;
        spu_registers->spucnt = spu_control;
        break;

    case 1:
        if ((spu_reverb_range_override != enable) && _SpuIsInAllocateArea_(spu_reverb_start_address)) {
            spu_control = spu_registers->spucnt;
            spu_reverb_enabled = 0;
            spu_control &= ~0x80;
            spu_registers->spucnt = spu_control;
        } else {
            spu_control = spu_registers->spucnt;
            spu_reverb_enabled = enable;
            spu_control |= 0x80;
            spu_registers->spucnt = spu_control;
        }
        break;
    }

    return spu_reverb_enabled;
}

/* Applies masked SPU master volumes and CD/external input volume, reverb and mixing settings. */
void SpuSetCommonAttr(SpuCommonAttr *attr)
{
    u32 mask;
    s32 set_all;
    u16 left_volume;
    u16 right_volume;
    u32 mode_bits;
    u16 spu_control;
    s16 left_level;
    s16 right_level;

    left_volume = 0;
    right_volume = 0;
    mask = attr->mask;
    set_all = (mask == 0);

    if (set_all || (mask & 0x1)) {
        if (set_all || (mask & 0x4)) {
            switch (attr->mvolmode.left) {
            case 1:
                mode_bits = 0x8000;
                break;
            case 2:
                mode_bits = 0x9000;
                break;
            case 3:
                mode_bits = 0xA000;
                break;
            case 4:
                mode_bits = 0xB000;
                break;
            case 5:
                mode_bits = 0xC000;
                break;
            case 6:
                mode_bits = 0xD000;
                break;
            case 7:
                mode_bits = 0xE000;
                break;
            case 0:
                left_volume = attr->mvol.left;
                mode_bits = 0;
                break;
            default:
                left_volume = attr->mvol.left;
                mode_bits = 0;
                break;
            }
        } else {
            left_volume = attr->mvol.left;
            mode_bits = 0;
        }
        if (mode_bits != 0) {
            left_level = attr->mvol.left;
            if (left_level > 0x7F) {
                left_volume = 0x7F;
            } else if (left_level < 0) {
                left_volume = 0;
            } else {
                left_volume = left_level;
            }
        }
        spu_registers->mvoll = (left_volume & 0x7FFF) | mode_bits;
    }

    if (set_all || (mask & 0x2)) {
        if (set_all || (mask & 0x8)) {
            switch (attr->mvolmode.right) {
            case 1:
                mode_bits = 0x8000;
                break;
            case 2:
                mode_bits = 0x9000;
                break;
            case 3:
                mode_bits = 0xA000;
                break;
            case 4:
                mode_bits = 0xB000;
                break;
            case 5:
                mode_bits = 0xC000;
                break;
            case 6:
                mode_bits = 0xD000;
                break;
            case 7:
                mode_bits = 0xE000;
                break;
            case 0:
                right_volume = attr->mvol.right;
                mode_bits = 0;
                break;
            default:
                right_volume = attr->mvol.right;
                mode_bits = 0;
                break;
            }
        } else {
            right_volume = attr->mvol.right;
            mode_bits = 0;
        }
        if (mode_bits != 0) {
            right_level = attr->mvol.right;
            if (right_level > 0x7F) {
                right_volume = 0x7F;
            } else if (right_level < 0) {
                right_volume = 0;
            } else {
                right_volume = right_level;
            }
        }
        spu_registers->mvolr = (right_volume & 0x7FFF) | mode_bits;
    }

    if (set_all || (mask & 0x40)) {
        spu_registers->cdvoll = attr->cd.volume.left;
    }
    if (set_all || (mask & 0x80)) {
        spu_registers->cdvolr = attr->cd.volume.right;
    }
    if (set_all || (mask & 0x400)) {
        spu_registers->extvoll = attr->ext.volume.left;
    }
    if (set_all || (mask & 0x800)) {
        spu_registers->extvolr = attr->ext.volume.right;
    }
    if (set_all || (mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            spu_control = spu_registers->spucnt;
            spu_control &= 0xFFFB;
            spu_registers->spucnt = spu_control;
        } else {
            spu_control = spu_registers->spucnt;
            spu_control |= 0x4;
            spu_registers->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x200)) {
        if (attr->cd.mix == 0) {
            spu_control = spu_registers->spucnt;
            spu_control &= 0xFFFE;
            spu_registers->spucnt = spu_control;
        } else {
            spu_control = spu_registers->spucnt;
            spu_control |= 0x1;
            spu_registers->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            spu_control = spu_registers->spucnt;
            spu_control &= 0xFFF7;
            spu_registers->spucnt = spu_control;
        } else {
            spu_control = spu_registers->spucnt;
            spu_control |= 0x8;
            spu_registers->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            spu_control = spu_registers->spucnt;
            spu_control &= 0xFFFD;
            spu_registers->spucnt = spu_control;
        } else {
            spu_control = spu_registers->spucnt;
            spu_control |= 0x2;
            spu_registers->spucnt = spu_control;
        }
    }
}
