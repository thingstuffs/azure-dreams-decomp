#include "common.h"

typedef struct SpuVolume_ {
    s16 left;
    s16 right;
} SpuVolume_;

typedef struct SpuVoiceAttr_ {
    u32 voice;          /* 0x00 */
    u32 mask;           /* 0x04 */
    SpuVolume_ volume;  /* 0x08 */
    SpuVolume_ volmode; /* 0x0C */
    SpuVolume_ volumex; /* 0x10 */
    u16 pitch;          /* 0x14 */
    u16 note;           /* 0x16 */
    u16 sample_note;    /* 0x18 */
    s16 envx;           /* 0x1A */
    u32 addr;           /* 0x1C */
    u32 loop_addr;      /* 0x20 */
    s32 a_mode;         /* 0x24 */
    s32 s_mode;         /* 0x28 */
    s32 r_mode;         /* 0x2C */
    u16 ar;             /* 0x30 */
    u16 dr;             /* 0x32 */
    u16 sr;             /* 0x34 */
    u16 rr;             /* 0x36 */
    u16 sl;             /* 0x38 */
    u16 adsr1;          /* 0x3A */
    u16 adsr2;          /* 0x3C */
} SpuVoiceAttr_;

typedef struct { volatile u16 *ptr; u32 pad2[2]; } S_80079958;
extern S_80079958 D_80079958;
extern u16 D_80079520[24];
extern void *jtbl_8003327C[];
extern void *jtbl_8003329C[];

extern s16 func_8005F7D0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8005D598(s32 reg, u32 val);

/* Apply masked voice attributes to the selected SPU voices. */
void func_8005F134(SpuVoiceAttr_ *attr)
{
    s32 voice;
    u32 mask;
    s32 reg_base;
    s32 set_all;
    register s32 left_volume ASM_REG("$5");
    register s32 right_volume ASM_REG("$5");
    s32 volume_mode;
    s32 env_mode;
    register u16 env_value ASM_REG("$5");
    u16 adsr;
    register u16 raw_volume ASM_REG("$2");
    u16 sample_note;
    u16 note;
    s16 mode_offset;
    s32 mode_index;
    static void *const volume_labels[] = {
        &&L_vl_1, &&L_vl_2, &&L_vl_3, &&L_vl_4, &&L_vl_5, &&L_vl_6, &&L_vl_7,
        &&L_vr_1, &&L_vr_2, &&L_vr_3, &&L_vr_4, &&L_vr_5, &&L_vr_6, &&L_vr_7
    };
    volatile s32 delay_step;
    volatile s32 delay_value;

    (void)volume_labels;

    mask = attr->mask;
    set_all = (mask == 0);
    for (voice = 0; voice < 24; voice++) {
        if (attr->voice & (1 << voice)) {
            reg_base = voice * 8;
            if (set_all || (mask & 0x10)) {
                D_80079958.ptr[voice * 8 + 2] = attr->pitch;
            }
            if (set_all || (mask & 0x40)) {
                D_80079520[voice] = attr->sample_note;
            }
            if (set_all || (mask & 0x20)) {
                sample_note = D_80079520[voice];
                note = attr->note;
                D_80079958.ptr[reg_base + 2] =
                    func_8005F7D0(sample_note >> 8, sample_note & 0xFF, note >> 8, note & 0xFF);
            }
            if (set_all || (mask & 0x1)) {
                volume_mode = 0;
                raw_volume = attr->volume.left;
                left_volume = raw_volume & 0x7FFF;
                if (set_all || (mask & 0x4)) {
                    mode_offset = attr->volmode.left - 1;
                    mode_index = mode_offset;
                    if ((u32)mode_index >= 7) {
                        goto L_vl_end;
                    }
                    goto *jtbl_8003327C[mode_index];
L_vl_1:
                    volume_mode = 0x8000;
                    goto L_vl_end;
L_vl_2:
                    volume_mode = 0x9000;
                    goto L_vl_end;
L_vl_3:
                    volume_mode = 0xA000;
                    goto L_vl_end;
L_vl_4:
                    volume_mode = 0xB000;
                    goto L_vl_end;
L_vl_5:
                    volume_mode = 0xC000;
                    goto L_vl_end;
L_vl_6:
                    volume_mode = 0xD000;
                    goto L_vl_end;
L_vl_7:
                    volume_mode = 0xE000;
L_vl_end:
                    ;
                }
                if (volume_mode != 0) {
                    if (attr->volume.left >= 0x80) {
                        left_volume = 0x7F;
                    } else if (attr->volume.left < 0) {
                        left_volume = 0;
                    }
                }
                D_80079958.ptr[reg_base + 0] = left_volume | volume_mode;
            }
            if (set_all || (mask & 0x2)) {
                volume_mode = 0;
                raw_volume = attr->volume.right;
                right_volume = raw_volume & 0x7FFF;
                if (set_all || (mask & 0x8)) {
                    mode_offset = attr->volmode.right - 1;
                    mode_index = mode_offset;
                    if ((u32)mode_index >= 7) {
                        goto L_vr_end;
                    }
                    goto *jtbl_8003329C[mode_index];
L_vr_1:
                    volume_mode = 0x8000;
                    goto L_vr_end;
L_vr_2:
                    volume_mode = 0x9000;
                    goto L_vr_end;
L_vr_3:
                    volume_mode = 0xA000;
                    goto L_vr_end;
L_vr_4:
                    volume_mode = 0xB000;
                    goto L_vr_end;
L_vr_5:
                    volume_mode = 0xC000;
                    goto L_vr_end;
L_vr_6:
                    volume_mode = 0xD000;
                    goto L_vr_end;
L_vr_7:
                    volume_mode = 0xE000;
L_vr_end:
                    ;
                }
                if (volume_mode != 0) {
                    if (attr->volume.right >= 0x80) {
                        right_volume = 0x7F;
                    } else if (attr->volume.right < 0) {
                        right_volume = 0;
                    }
                }
                D_80079958.ptr[reg_base + 1] = right_volume | volume_mode;
            }
            if (set_all || (mask & 0x80)) {
                func_8005D598(reg_base + 3, attr->addr);
            }
            if (set_all || (mask & 0x10000)) {
                func_8005D598(reg_base + 7, attr->loop_addr);
            }
            if (set_all || (mask & 0x20000)) {
                D_80079958.ptr[reg_base + 4] = attr->adsr1;
            }
            if (set_all || (mask & 0x40000)) {
                D_80079958.ptr[reg_base + 5] = attr->adsr2;
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
                adsr = D_80079958.ptr[reg_base + 4];
                adsr = (adsr & 0xFF) | ((env_value | env_mode) << 8);
                D_80079958.ptr[reg_base + 4] = adsr;
            }
            if (set_all || (mask & 0x1000)) {
                env_value = attr->dr;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = D_80079958.ptr[reg_base + 4];
                adsr = (adsr & 0xFF0F) | (env_value << 4);
                D_80079958.ptr[reg_base + 4] = adsr;
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
                adsr = D_80079958.ptr[reg_base + 5];
                adsr = (adsr & 0x3F) | ((env_value | env_mode) << 6);
                D_80079958.ptr[reg_base + 5] = adsr;
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
                adsr = D_80079958.ptr[reg_base + 5];
                adsr = (adsr & 0xFFC0) | (env_value | env_mode);
                D_80079958.ptr[reg_base + 5] = adsr;
            }
            if (set_all || (mask & 0x8000)) {
                env_value = attr->sl;
                if (env_value >= 0x10) {
                    env_value = 0xF;
                }
                adsr = D_80079958.ptr[reg_base + 4];
                adsr = (adsr & 0xFFF0) | env_value;
                D_80079958.ptr[reg_base + 4] = adsr;
            }
        }
    }
    delay_value = 1;
    for (delay_step = 0; delay_step < 2; delay_step++) {
        delay_value = delay_value * 13;
    }
}
