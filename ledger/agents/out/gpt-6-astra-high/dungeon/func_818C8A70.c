#include "common.h"
#include "m2c_compat.h"

typedef struct S_818C8A70_0_pre {
    u16 unk_00;
} S_818C8A70_0_pre;   /* the 0x2 bytes before arg0 in func_818C8A70, addressed as arg0[-1] */

typedef struct S_818C8A70_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0xB];
    u8 unk_15;
    u8 pad_16[0x16];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818C8A70_0;   /* arg0 in func_818C8A70 */

typedef struct S_818C8A70_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x54];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818C8A70_1;   /* temp_s4 in func_818C8A70 */

typedef struct S_818C8A70_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_818C8A70_2;   /* temp_v0 in func_818C8A70 */

typedef struct S_818C8A70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818C8A70_3;   /* temp_s0 in func_818C8A70 */

typedef struct S_818C8A70_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_818C8A70_4;   /* arg1 in func_818C8A70 */

typedef struct S_818C8A70_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818C8A70_5;   /* temp_s2 in func_818C8A70 */

typedef struct S_818C8A70_6 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_818C8A70_6;   /* temp_s7 in func_818C8A70 */

typedef struct S_818C8A70_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818C8A70_7_pre;   /* the 0x18 bytes before ((S_818C8A70_0 *)arg0)->unk_30 in func_818C8A70, addressed as ((S_818C8A70_0 *)arg0)->unk_30[-1] */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80024D04;
extern u8 D_80045340[];
extern u8 D_800DE870[9];
extern s32 D_800814A0[3];
extern u8 D_800DEC00[];
void func_80024414(void) __attribute__((noreturn));                            /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_8009D218();            /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800C8CD8();        /* extern */
extern M2C_UNK D_80024024;
extern M2C_UNK D_80024124;
extern u8 D_800E3D68;

/* Updates a moving effect, spawns particles, and advances its timed phases. */
void func_818C8A70(void *effect, S_818C8A70_4 *position) {
    M2C_UNK effect_mode;
    s16 coord;
    s16 phase;
    s32 effect_value;
    s32 random_value;
    u16 remaining_ticks;
    u16 burst_ticks;
    u16 fade_ticks;
    S_818C8A70_3 *sprite;
    S_818C8A70_5 *particle_pos;
    register S_818C8A70_1 *particle_state ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_818C8A70_6 *source;
    void *particle;

    D_80024D04 = 1;
    source = ((S_818C8A70_0 *)effect)->unk_2C;
    if (((S_818C8A70_0 *)effect)->unk_00 == 0) {
        particle = func_8003FC64(0x212);
        particle_state = particle + 0x20;
        if (particle != NULL) {
            particle_state->unk_02 = 0x1A;
            ((S_818C8A70_2 *)particle)->unk_10 = &D_80024124;
            func_8004491C(particle, D_80045340);
            sprite = ((S_818C8A70_2 *)particle)->unk_0C;
            sprite->unk_10 = 0x60;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
            particle_pos = ((S_818C8A70_2 *)particle)->unk_08;
            random_value = func_80069EF8();
            coord = position->unk_00.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->unk_02 = coord;
            random_value = func_80069EF8();
            coord = position->unk_04.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->unk_06 = coord;
            random_value = func_80069EF8();
            coord = position->unk_08.at02.v;
            coord -= 4;
            coord += random_value & 7;
            particle_pos->unk_0A = coord;
            particle_state->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
            sprite = ((S_818C8A70_2 *)particle)->unk_0C;
            sprite->unk_1C = 0x1000;
            sprite->unk_1E = 0x1000;
            sprite->unk_0E = 0x80;
            sprite->unk_0D = 0x80;
            sprite->unk_0C = 0x80;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
            func_8003DB94(sprite, D_800DE870, 0);
        }
        remaining_ticks = ((S_818C8A70_0 *)effect)->unk_02 - 1;
        ((S_818C8A70_0 *)effect)->unk_02 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            if (((S_818C8A70_0 *)effect)->unk_08 != 0) {
                ((S_818C8A70_0 *)effect)->unk_00 = 1;
                ((S_818C8A70_0 *)effect)->unk_02 = 0U;
                func_800A56E0(0x300);
                func_80024414();
                return;
            }
            ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
            ((S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
        if ((func_800A4778(position->unk_00.at02.v, position->unk_04.at02.v, (s16) position->unk_08.at02.v, ((S_818C8A70_0 *)effect)->unk_30) << 0x10) == 0) {
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((S_818C8A70_0 *)effect)->unk_58);
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((S_818C8A70_0 *)effect)->unk_5C);
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((S_818C8A70_0 *)effect)->unk_60);
            goto update_phase;
        }
        goto remove_effect;
    }
update_phase:
    phase = ((S_818C8A70_0 *)effect)->unk_00;
    if (phase == 1) {
        burst_ticks = ((S_818C8A70_0 *)effect)->unk_02 + 1;
        ((S_818C8A70_0 *)effect)->unk_02 = burst_ticks;
        if ((burst_ticks & 3) == phase) {
            particle = func_8003FC64(0x212);
            particle_state = particle + 0x20;
            if (particle != NULL) {
                register s16 particle_z ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                particle_state->unk_02 = 0x1A;
                ((S_818C8A70_2 *)particle)->unk_10 = &D_80024124;
                func_8004491C(particle, D_80045340);
                sprite = ((S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_10 = 0x60;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = ((S_818C8A70_2 *)particle)->unk_08;
                sprite = ((S_818C8A70_7_pre *)(((S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = func_80069EF8();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_02 = coord;
                random_value = func_80069EF8();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_06 = coord;
                random_value = func_80069EF8();
                random_value &= 0x1F;
                coord = sprite->unk_0A;
                random_value += 0x10;
                particle_z = coord - random_value;
                particle_pos->unk_0A = particle_z;
                particle_state->unk_58 = (s32) (func_80069EF8() - 0x8000);
                particle_state->unk_5C = (s32) (func_80069EF8() - 0x8000);
                particle_state->unk_60 = (s32) ((func_80069EF8() + 0xFFFC0000) * 2);
                sprite = ((S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_1C = 0x1000;
                sprite->unk_1E = 0x1000;
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DCF;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                func_8003DB94(sprite, D_800DE870, 0);
            }
        }
        if ((((S_818C8A70_0 *)effect)->unk_02 & 3) == 2) {
            particle = func_8003FC64(0x212);
            particle_state = particle + 0x20;
            if (particle != NULL) {
                register s16 particle_z ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                particle_state->unk_02 = 0x14;
                ((S_818C8A70_2 *)particle)->unk_10 = &D_80024024;
                func_8004491C(particle, D_80045340);
                sprite = ((S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_10 = 0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = ((S_818C8A70_2 *)particle)->unk_08;
                sprite = ((S_818C8A70_7_pre *)(((S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = func_80069EF8();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_02 = coord;
                random_value = func_80069EF8();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->unk_06 = coord;
                random_value = func_80069EF8();
                random_value &= 0x3F;
                coord = sprite->unk_0A;
                random_value += 0x20;
                particle_z = coord - random_value;
                particle_pos->unk_0A = particle_z;
                sprite = ((S_818C8A70_2 *)particle)->unk_0C;
                sprite->unk_1C = 0x800;
                sprite->unk_1E = 0x800;
                particle_state->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DC0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                func_8003DB94(sprite, D_800DEC00, 0);
            }
        }
        if ((s16) ((S_818C8A70_0 *)effect)->unk_02 >= 0x29) {
            ((S_818C8A70_0 *)effect)->unk_00 = 2;
            ((S_818C8A70_0 *)effect)->unk_02 = 0U;
            if (func_8009D218(source->unk_60, 1, source) == 0) {
                s32 random_bonus;
                u32 effect_scale;
                random_bonus = func_800A6D30();
                random_bonus &= 3;
                effect_scale = ((S_818C8A70_0 *)effect)->unk_15;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                random_bonus += 2;
                effect_scale >>= 2;
                effect_value = effect_scale + random_bonus;
                effect_mode = 0x10;
                if (D_800E3D68 == 0xFF) {
                    effect_mode = 0xFF;
                }
                func_800C8CD8(((S_818C8A70_0 *)effect)->unk_30, effect_mode, effect_value);
            }
        }
    }
    if (((S_818C8A70_0 *)effect)->unk_00 == 2) {
        fade_ticks = ((S_818C8A70_0 *)effect)->unk_02 + 1;
        ((S_818C8A70_0 *)effect)->unk_02 = fade_ticks;
        if ((s16) fade_ticks >= 0x15) {
remove_effect:
            ((S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
