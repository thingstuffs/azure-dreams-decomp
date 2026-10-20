#include "engine/audio/spu/sound_reverb.h"

#include "engine/audio/spu/sound_reverb.h"

/* Copies selected fields to D_80079958, or all 32 fields when the mask is zero. */
void func_8005DF80(SoundReverbParameters *source) {
    s32 field_mask;
    s32 copy_all;

    field_mask = source->mask;
    copy_all = field_mask == 0;
    if ((copy_all != 0) || (field_mask & 1)) {
        D_80079958->reverb[0] = (u16) source->p04;
    }
    if ((copy_all != 0) || (field_mask & 2)) {
        D_80079958->reverb[1] = (u16) source->p06;
    }
    if ((copy_all != 0) || (field_mask & 4)) {
        D_80079958->reverb[2] = (u16) source->p08;
    }
    if ((copy_all != 0) || (field_mask & 8)) {
        D_80079958->reverb[3] = (u16) source->p0A;
    }
    if ((copy_all != 0) || (field_mask & 0x10)) {
        D_80079958->reverb[4] = (u16) source->p0C;
    }
    if ((copy_all != 0) || (field_mask & 0x20)) {
        D_80079958->reverb[5] = (u16) source->p0E;
    }
    if ((copy_all != 0) || (field_mask & 0x40)) {
        D_80079958->reverb[6] = (u16) source->p10;
    }
    if ((copy_all != 0) || (field_mask & 0x80)) {
        D_80079958->reverb[7] = (u16) source->p12;
    }
    if ((copy_all != 0) || (field_mask & 0x100)) {
        D_80079958->reverb[8] = (u16) source->p14;
    }
    if ((copy_all != 0) || (field_mask & 0x200)) {
        D_80079958->reverb[9] = (u16) source->p16;
    }
    if ((copy_all != 0) || (field_mask & 0x400)) {
        D_80079958->reverb[10] = (u16) source->p18;
    }
    if ((copy_all != 0) || (field_mask & 0x800)) {
        D_80079958->reverb[11] = (u16) source->p1A;
    }
    if ((copy_all != 0) || (field_mask & 0x1000)) {
        D_80079958->reverb[12] = (u16) source->p1C;
    }
    if ((copy_all != 0) || (field_mask & 0x2000)) {
        D_80079958->reverb[13] = (u16) source->p1E;
    }
    if ((copy_all != 0) || (field_mask & 0x4000)) {
        D_80079958->reverb[14] = (u16) source->p20;
    }
    if ((copy_all != 0) || (field_mask & 0x8000)) {
        D_80079958->reverb[15] = (u16) source->p22;
    }
    if ((copy_all != 0) || (field_mask & 0x10000)) {
        D_80079958->reverb[16] = (u16) source->p24;
    }
    if ((copy_all != 0) || (field_mask & 0x20000)) {
        D_80079958->reverb[17] = (u16) source->p26;
    }
    if ((copy_all != 0) || (field_mask & 0x40000)) {
        D_80079958->reverb[18] = (u16) source->p28;
    }
    if ((copy_all != 0) || (field_mask & 0x80000)) {
        D_80079958->reverb[19] = (u16) source->p2A;
    }
    if ((copy_all != 0) || (field_mask & 0x100000)) {
        D_80079958->reverb[20] = (u16) source->p2C;
    }
    if ((copy_all != 0) || (field_mask & 0x200000)) {
        D_80079958->reverb[21] = (u16) source->p2E;
    }
    if ((copy_all != 0) || (field_mask & 0x400000)) {
        D_80079958->reverb[22] = (u16) source->p30;
    }
    if ((copy_all != 0) || (field_mask & 0x800000)) {
        D_80079958->reverb[23] = (u16) source->p32;
    }
    if ((copy_all != 0) || (field_mask & 0x01000000)) {
        D_80079958->reverb[24] = (u16) source->p34;
    }
    if ((copy_all != 0) || (field_mask & 0x02000000)) {
        D_80079958->reverb[25] = (u16) source->p36;
    }
    if ((copy_all != 0) || (field_mask & 0x04000000)) {
        D_80079958->reverb[26] = (u16) source->p38;
    }
    if ((copy_all != 0) || (field_mask & 0x08000000)) {
        D_80079958->reverb[27] = (u16) source->p3A;
    }
    if ((copy_all != 0) || (field_mask & 0x10000000)) {
        D_80079958->reverb[28] = (u16) source->p3C;
    }
    if ((copy_all != 0) || (field_mask & 0x20000000)) {
        D_80079958->reverb[29] = (u16) source->p3E;
    }
    if ((copy_all != 0) || (field_mask & 0x40000000)) {
        D_80079958->reverb[30] = (u16) source->p40;
    }
    if ((copy_all != 0) || (field_mask < 0)) {
        D_80079958->reverb[31] = (u16) source->p42;
    }
}
