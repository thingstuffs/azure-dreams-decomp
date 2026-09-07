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

/* Advances the effect state and initializes up to ten spawned objects. */
void func_80089608(void *effect_state) {
    unsigned char stack_data[104];
    Words4 *initial_table;
    Words4 *spawn_table;
    Words4 *stack_copy;
    s8 *position_table;
    s8 *spawn_template;
    s16 angle;
    s32 state_mode;
    s32 spawn_index;
    s32 phase_value;
    s32 phase_value_adjusted;
    s32 trig_component;
    s32 sine_product;
    s32 cosine_product;
    void *spawned_object;
    void *object_transform;
    void *object_properties;
    void *effect_config;
    void *spawn_callback;

    stack_copy = (Words4 *)&stack_data[0];
    initial_table = (Words4 *)&D_80088790;
    effect_config = ((S_80089608_0 *)effect_state)->unk_00;
    do {
        *stack_copy = *initial_table;
        initial_table++;
        stack_copy++;
    } while (initial_table != ((Words4 *)&D_80088790 + 2));
    *(Words2 *)stack_copy = *(Words2 *)initial_table;
    *(Packed20 *)(stack_data + 40) = *(Packed20 *)&D_800887B8;
    stack_copy = (Words4 *)&stack_data[64];
    spawn_table = &D_800887CC;
    do {
        *stack_copy = *spawn_table;
        spawn_table++;
        stack_copy++;
    } while (spawn_table != ((Words4 *)&D_800887CC + 2));
    *(Words2 *)stack_copy = *(Words2 *)spawn_table;
    if (((S_80089608_1 *)effect_config)->unk_26 & 1) {
        ((S_80089608_0 *)effect_state)->unk_08 = 0xFF;
    }
    if (((S_80089608_1 *)effect_config)->unk_20 >= 2) {
        ((S_80089608_0 *)effect_state)->unk_08 = 0xFF;
        goto epilogue;
    }
    state_mode = ((S_80089608_0 *)effect_state)->unk_08;
    switch (state_mode) {
    case 1:
        goto angle_mode;
    case 0:
        ((S_80089608_0 *)effect_state)->unk_04 = (s32) (((S_80089608_0 *)effect_state)->unk_04 + 0x20202);
        if (((S_80089608_1 *)effect_config)->unk_20 == 1) {
            ((S_80089608_0 *)effect_state)->unk_08++;
            goto set_spawn_count;
        }
        spawn_index = 9;
        goto spawn_setup;
    case 0xFF:
        goto error_mode;
    default:
        spawn_index = 9;
        goto spawn_setup;
    }

angle_mode:
    angle = ((S_80089608_0 *)effect_state)->unk_0A + 1;
    ((S_80089608_0 *)effect_state)->unk_0A = (u16) angle;
    if (angle < 0x80) {
        if (!(angle & 3)) {
            ((S_80089608_0 *)effect_state)->unk_04 += 0x10101;
        }
        goto pre_spawn_angle;
    }
    if (angle < 0x91) {
        phase_value = ((S_80089608_0 *)effect_state)->unk_04;
        spawn_index = ((s32) (~phase_value & 0xFF) >> 1);
        spawn_index = ((spawn_index << 8) + (spawn_index << 16)) + spawn_index;
        ((S_80089608_0 *)effect_state)->unk_04 = phase_value + spawn_index;
        goto pre_spawn_angle;
    }
    if (angle < 0xA0) {
        phase_value_adjusted = ((S_80089608_0 *)effect_state)->unk_04;
        spawn_index = ((s32) (phase_value_adjusted & 0xFF) >> 3);
        spawn_index = ((spawn_index << 8) + (spawn_index << 16)) + spawn_index;
        ((S_80089608_0 *)effect_state)->unk_04 = phase_value_adjusted - spawn_index;
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
    spawn_index = 9;
spawn_setup:
    spawn_callback = &D_80089A14;
    spawn_template = (M2C_UNK *)&stack_data[36];
    position_table = (M2C_UNK *)&stack_data[18];
    do {
        spawned_object = func_8003FC64(0x111);
        if (spawned_object != NULL) {
            object_properties = ((S_80089608_2 *)spawned_object)->unk_0C;
            ((S_80089608_2 *)spawned_object)->unk_10 = spawn_callback;
            func_8004491C(spawned_object, &D_80044BB0);
            sine_product = func_80064584(((S_80089608_0 *)effect_state)->unk_0E.u) * ((S_80089608_3 *)position_table)->unk_28;
            trig_component = sine_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)spawned_object)->unk_08))->unk_02 = (s16) ((trig_component - (sine_product >> 0xD)) + 0xA0);
            object_transform = (void *)((s8 *)spawned_object + 0x20);
            cosine_product = func_800644B8(((S_80089608_0 *)effect_state)->unk_0E.u) * ((S_80089608_3 *)position_table)->unk_28;
            trig_component = cosine_product >> 0xC;
            ((S_80089608_7 *)(((S_80089608_2 *)spawned_object)->unk_08))->unk_06 = (s16) ((trig_component + (cosine_product >> 0xE)) + 0x78);
            ((S_80089608_4 *)object_properties)->unk_1E = 0x1000;
            ((S_80089608_4 *)object_properties)->unk_1C = 0x1000;
            if (spawn_index == 0) {
                ((S_80089608_4 *)object_properties)->unk_1A = ((S_80089608_0 *)effect_state)->unk_0E.u;
                goto configure_spawn;
            }
            if (spawn_index == 1) {
                ((S_80089608_4 *)object_properties)->unk_1A = (s16) (0 - (u16) ((S_80089608_0 *)effect_state)->unk_0E.u);
            }
configure_spawn:
            ((S_80089608_4 *)object_properties)->unk_10 = 0x60;
            ((S_80089608_4 *)object_properties)->unk_14 = (u16) (((S_80089608_4 *)object_properties)->unk_14 | 0xC);
            ((S_80089608_4 *)object_properties)->unk_08 = (s32) ((S_80089608_5 *)spawn_template)->unk_00;
            ((S_80089608_4 *)object_properties)->unk_04 = 0;
            ((S_80089608_4 *)object_properties)->unk_05 = 0;
            ((S_80089608_4 *)object_properties)->unk_0C = (s32) (((S_80089608_0 *)effect_state)->unk_04 & ((S_80089608_5 *)spawn_template)->unk_40);
            ((S_80089608_6 *)object_transform)->unk_0C = spawn_index;
            goto block_43;
        }
block_43:
        spawn_template -= 4;
        spawn_index -= 1;
        position_table -= 2;
    } while (spawn_index >= 0);
    return;
epilogue:
    return;
}
