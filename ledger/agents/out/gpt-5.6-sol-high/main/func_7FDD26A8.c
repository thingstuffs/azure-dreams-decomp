#include "common.h"
#include "m2c_compat.h"

typedef struct S_80089608_0_pre {
    u16 unk_00;
} S_80089608_0_pre;   /* the 0x2 bytes before arg0 in func_80089608, addressed as arg0[-1] */

typedef struct S_80089608_0 {
    void * unk_00;
    s32 unk_04;
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x2];
    union { u16 s; s16 u; } unk_0E;   /* accessed as both */
} S_80089608_0;   /* arg0 in func_80089608 */

typedef struct S_80089608_1 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x4];
    u16 unk_26;
} S_80089608_1;   /* temp_t1 in func_80089608 */

typedef struct S_80089608_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80089608_2;   /* temp_v0 in func_80089608 */

typedef struct S_80089608_3 {
    u8 pad_00[0x28];
    s16 unk_28;
} S_80089608_3;   /* var_s4 in func_80089608 */

typedef struct S_80089608_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80089608_4;   /* temp_s1 in func_80089608 */

typedef struct S_80089608_5 {
    s32 unk_00;
    u8 pad_04[0x3C];
    s32 unk_40;
} S_80089608_5;   /* var_s5 in func_80089608 */

typedef struct S_80089608_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80089608_6;   /* var_sub in func_80089608 */

typedef struct S_80089608_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80089608_7;   /* ((S_80089608_2 *)temp_v0)->unk_08 in func_80089608 */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_800814A0;
extern M2C_UNK D_80088790;
extern M2C_UNK D_800887B8;
extern M2C_UNK D_800887CC;
extern M2C_UNK D_80089A14;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
} __attribute__((packed)) Packed12;
typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Packed8;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
} __attribute__((packed)) Packed20;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Words4;
typedef struct {
    s32 w0;
    s32 w1;
} Words2;

// Updates a radial particle effect and spawns and configures its next batch of particles.
void func_80089608(void *effect_state) {
    unsigned char particle_data[104];
    Words4 *template_src;
    Words4 *second_template_src;
    Words4 *template_dst;
    s8 *angle_scale_cursor;
    s8 *particle_data_cursor;
    s16 phase;
    s32 mode;
    s32 particle_index;
    s32 color;
    s32 fading_color;
    s32 scaled_trig_value;
    s32 sine_product;
    s32 cosine_product;
    void *particle;
    void *particle_tail;
    void *particle_config;
    void *effect_owner;
    void *callback;

    template_dst = (Words4 *)&particle_data[0];
    template_src = (Words4 *)&D_80088790;
    effect_owner = ((S_80089608_0 *)effect_state)->unk_00;
    do {
        *template_dst = *template_src;
        template_src++;
        template_dst++;
    } while (template_src != ((Words4 *)&D_80088790 + 2));
    *(Words2 *)template_dst = *(Words2 *)template_src;
    *(Packed20 *)(particle_data + 40) = *(Packed20 *)&D_800887B8;
    template_dst = (Words4 *)&particle_data[64];
    second_template_src = &D_800887CC;
    do {
        *template_dst = *second_template_src;
        second_template_src++;
        template_dst++;
    } while (second_template_src != ((Words4 *)&D_800887CC + 2));
    *(Words2 *)template_dst = *(Words2 *)second_template_src;
    if (((S_80089608_1 *)effect_owner)->unk_26 & 1) {
        ((S_80089608_0 *)effect_state)->unk_08 = 0xFF;
    }
    if (((S_80089608_1 *)effect_owner)->unk_20 >= 2) {
        ((S_80089608_0 *)effect_state)->unk_08 = 0xFF;
        goto epilogue;
    }
    mode = ((S_80089608_0 *)effect_state)->unk_08;
    switch (mode) {
    case 1:
        goto angle_mode;
    case 0:
        ((S_80089608_0 *)effect_state)->unk_04 = (s32) (((S_80089608_0 *)effect_state)->unk_04 + 0x20202);
        if (((S_80089608_1 *)effect_owner)->unk_20 == 1) {
            ((S_80089608_0 *)effect_state)->unk_08++;
            goto set_spawn_count;
        }
        particle_index = 9;
        goto spawn_setup;
    case 0xFF:
        goto error_mode;
    default:
        particle_index = 9;
        goto spawn_setup;
    }

angle_mode:
    phase = ((S_80089608_0 *)effect_state)->unk_0A + 1;
    ((S_80089608_0 *)effect_state)->unk_0A = (u16) phase;
    if (phase < 0x80) {
        if (!(phase & 3)) {
            ((S_80089608_0 *)effect_state)->unk_04 += 0x10101;
        }
        goto pre_spawn_angle;
    }
    if (phase < 0x91) {
        color = ((S_80089608_0 *)effect_state)->unk_04;
        particle_index = ((s32) (~color & 0xFF) >> 1);
        particle_index = ((particle_index << 8) + (particle_index << 16)) + particle_index;
        ((S_80089608_0 *)effect_state)->unk_04 = color + particle_index;
        goto pre_spawn_angle;
    }
    if (phase < 0xA0) {
        fading_color = ((S_80089608_0 *)effect_state)->unk_04;
        particle_index = ((s32) (fading_color & 0xFF) >> 3);
        particle_index = ((particle_index << 8) + (particle_index << 16)) + particle_index;
        ((S_80089608_0 *)effect_state)->unk_04 = fading_color - particle_index;
        goto pre_spawn_angle;
    }
    ((S_80089608_0 *)effect_state)->unk_08 = 0xFF;
    ((S_80089608_0 *)effect_state)->unk_04 = 0;
pre_spawn_angle:
    ((S_80089608_0 *)effect_state)->unk_0E.s -= 12;
    goto set_spawn_count;

error_mode:
    (*(u16 *)((u8 *)effect_state + -2)) = (u16) (((S_80089608_0_pre *)effect_state)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    goto epilogue;
set_spawn_count:
    particle_index = 9;
spawn_setup:
    callback = &D_80089A14;
    particle_data_cursor = (M2C_UNK *)&particle_data[36];
    angle_scale_cursor = (M2C_UNK *)&particle_data[18];
    do {
        particle = func_8003FC64(0x111);
        if (particle != NULL) {
            particle_config = ((S_80089608_2 *)particle)->unk_0C;
            ((S_80089608_2 *)particle)->unk_10 = callback;
            func_8004491C(particle, &D_80044BB0);
            sine_product = func_80064584(((S_80089608_0 *)effect_state)->unk_0E.u) * ((S_80089608_3 *)angle_scale_cursor)->unk_28;
            scaled_trig_value = sine_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)particle)->unk_08))->unk_02 = (s16) ((scaled_trig_value - (sine_product >> 0xD)) + 0xA0);
            particle_tail = (void *)((s8 *)particle + 0x20);
            cosine_product = func_800644B8(((S_80089608_0 *)effect_state)->unk_0E.u) * ((S_80089608_3 *)angle_scale_cursor)->unk_28;
            scaled_trig_value = cosine_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)particle)->unk_08))->unk_06 = (s16) ((scaled_trig_value + (cosine_product >> 0xE)) + 0x78);
            ((S_80089608_4 *)particle_config)->unk_1E = 0x1000;
            ((S_80089608_4 *)particle_config)->unk_1C = 0x1000;
            if (particle_index == 0) {
                ((S_80089608_4 *)particle_config)->unk_1A = ((S_80089608_0 *)effect_state)->unk_0E.u;
                goto configure_spawn;
            }
            if (particle_index == 1) {
                ((S_80089608_4 *)particle_config)->unk_1A = (s16) (0 - (u16) ((S_80089608_0 *)effect_state)->unk_0E.u);
            }
configure_spawn:
            ((S_80089608_4 *)particle_config)->unk_10 = 0x60;
            ((S_80089608_4 *)particle_config)->unk_14 = (u16) (((S_80089608_4 *)particle_config)->unk_14 | 0xC);
            ((S_80089608_4 *)particle_config)->unk_08 = (s32) ((S_80089608_5 *)particle_data_cursor)->unk_00;
            ((S_80089608_4 *)particle_config)->unk_04 = 0;
            ((S_80089608_4 *)particle_config)->unk_05 = 0;
            ((S_80089608_4 *)particle_config)->unk_0C = (s32) (((S_80089608_0 *)effect_state)->unk_04 & ((S_80089608_5 *)particle_data_cursor)->unk_40);
            ((S_80089608_6 *)particle_tail)->unk_0C = particle_index;
            goto advance_particle;
        }
advance_particle:
        particle_data_cursor -= 4;
        particle_index -= 1;
        angle_scale_cursor -= 2;
    } while (particle_index >= 0);
    return;
epilogue:
    return;
}
