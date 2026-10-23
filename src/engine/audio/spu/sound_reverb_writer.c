#include "engine/audio/spu/sound_reverb.h"

#include "engine/audio/spu/sound_reverb.h"
#include "engine/audio/spu.h"

/*
 * Writes the selected halfword parameters to spu_registers->reverb, or all 32 registers when the
 * mask is zero.
 */
void _spu_setReverbAttr(SoundReverbParameters *source) {
    s32 field_mask;
    s32 copy_all;

    field_mask = source->mask;
    copy_all = field_mask == 0;
    if ((copy_all != 0) || (field_mask & 1)) {
        spu_registers->reverb[0] = (u16) source->p04;
    }
    if ((copy_all != 0) || (field_mask & 2)) {
        spu_registers->reverb[1] = (u16) source->p06;
    }
    if ((copy_all != 0) || (field_mask & 4)) {
        spu_registers->reverb[2] = (u16) source->p08;
    }
    if ((copy_all != 0) || (field_mask & 8)) {
        spu_registers->reverb[3] = (u16) source->p0A;
    }
    if ((copy_all != 0) || (field_mask & 0x10)) {
        spu_registers->reverb[4] = (u16) source->p0C;
    }
    if ((copy_all != 0) || (field_mask & 0x20)) {
        spu_registers->reverb[5] = (u16) source->p0E;
    }
    if ((copy_all != 0) || (field_mask & 0x40)) {
        spu_registers->reverb[6] = (u16) source->p10;
    }
    if ((copy_all != 0) || (field_mask & 0x80)) {
        spu_registers->reverb[7] = (u16) source->p12;
    }
    if ((copy_all != 0) || (field_mask & 0x100)) {
        spu_registers->reverb[8] = (u16) source->p14;
    }
    if ((copy_all != 0) || (field_mask & 0x200)) {
        spu_registers->reverb[9] = (u16) source->p16;
    }
    if ((copy_all != 0) || (field_mask & 0x400)) {
        spu_registers->reverb[10] = (u16) source->p18;
    }
    if ((copy_all != 0) || (field_mask & 0x800)) {
        spu_registers->reverb[11] = (u16) source->p1A;
    }
    if ((copy_all != 0) || (field_mask & 0x1000)) {
        spu_registers->reverb[12] = (u16) source->p1C;
    }
    if ((copy_all != 0) || (field_mask & 0x2000)) {
        spu_registers->reverb[13] = (u16) source->p1E;
    }
    if ((copy_all != 0) || (field_mask & 0x4000)) {
        spu_registers->reverb[14] = (u16) source->p20;
    }
    if ((copy_all != 0) || (field_mask & 0x8000)) {
        spu_registers->reverb[15] = (u16) source->p22;
    }
    if ((copy_all != 0) || (field_mask & 0x10000)) {
        spu_registers->reverb[16] = (u16) source->p24;
    }
    if ((copy_all != 0) || (field_mask & 0x20000)) {
        spu_registers->reverb[17] = (u16) source->p26;
    }
    if ((copy_all != 0) || (field_mask & 0x40000)) {
        spu_registers->reverb[18] = (u16) source->p28;
    }
    if ((copy_all != 0) || (field_mask & 0x80000)) {
        spu_registers->reverb[19] = (u16) source->p2A;
    }
    if ((copy_all != 0) || (field_mask & 0x100000)) {
        spu_registers->reverb[20] = (u16) source->p2C;
    }
    if ((copy_all != 0) || (field_mask & 0x200000)) {
        spu_registers->reverb[21] = (u16) source->p2E;
    }
    if ((copy_all != 0) || (field_mask & 0x400000)) {
        spu_registers->reverb[22] = (u16) source->p30;
    }
    if ((copy_all != 0) || (field_mask & 0x800000)) {
        spu_registers->reverb[23] = (u16) source->p32;
    }
    if ((copy_all != 0) || (field_mask & 0x01000000)) {
        spu_registers->reverb[24] = (u16) source->p34;
    }
    if ((copy_all != 0) || (field_mask & 0x02000000)) {
        spu_registers->reverb[25] = (u16) source->p36;
    }
    if ((copy_all != 0) || (field_mask & 0x04000000)) {
        spu_registers->reverb[26] = (u16) source->p38;
    }
    if ((copy_all != 0) || (field_mask & 0x08000000)) {
        spu_registers->reverb[27] = (u16) source->p3A;
    }
    if ((copy_all != 0) || (field_mask & 0x10000000)) {
        spu_registers->reverb[28] = (u16) source->p3C;
    }
    if ((copy_all != 0) || (field_mask & 0x20000000)) {
        spu_registers->reverb[29] = (u16) source->p3E;
    }
    if ((copy_all != 0) || (field_mask & 0x40000000)) {
        spu_registers->reverb[30] = (u16) source->p40;
    }
    if ((copy_all != 0) || (field_mask < 0)) {
        spu_registers->reverb[31] = (u16) source->p42;
    }
}
