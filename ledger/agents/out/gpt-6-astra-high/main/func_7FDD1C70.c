/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80088BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    union { s16 s16; void * p32; } unk_20;   /* accessed as both */
    u8 pad_24[0xA];
    s16 unk_2E;
} S_80088BD0_0;   /* temp_v0 in func_80088BD0 */

typedef struct S_80088BD0_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80088BD0_1;   /* var_fp in func_80088BD0 */

typedef struct S_80088BD0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80088BD0_2;   /* var_s5 in func_80088BD0 */

typedef struct S_80088BD0_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80088BD0_3;   /* temp_s1 in func_80088BD0 */

typedef struct S_80088BD0_4 {
    s32 unk_00;
} S_80088BD0_4;   /* (s8 *)stack_desc + (s32)var_s4 in func_80088BD0 */

typedef struct S_80088BD0_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80088BD0_5;   /* (s8 *)temp_s3 - 0x20 in func_80088BD0 */

typedef struct S_80088BD0_6 {
    void * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
} S_80088BD0_6;   /* temp_s3 in func_80088BD0 */

typedef struct S_80088BD0_7 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80088BD0_7;   /* temp_v1 in func_80088BD0 */

typedef struct S_80088BD0_8 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80088BD0_8;   /* (s8 *)var_fp + (var_s2 << 2) in func_80088BD0 */

typedef struct S_80088BD0_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_80088BD0_9;   /* ((S_80088BD0_0 *)temp_v0)->unk_08 in func_80088BD0 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_80053A88;
extern s8 D_80080A84;
extern M2C_UNK D_80088760;
extern M2C_UNK D_8008896C;
void func_80088B48();  /* extern */
void func_80088EDC();  /* extern */
void func_800890EC();  /* extern */
void func_80089608();  /* extern */
void func_80089A38();  /* extern */
extern M2C_UNK D_8008B230;
extern M2C_UNK D_8008B270;

typedef struct { s32 a, b, c; } Desc3;

/* Creates a controller and its linked sprites and effect objects. */
void func_80088BD0(void) {
    s32 sprite_ids[3];
    s32 child_index;
    s32 sprite_y;
    s32 start_delay;
    s32 unit_scale;
    s32 sprite_id;
    void *child_state;
    S_80088BD0_3 *sprite;
    void *object;
    S_80088BD0_7 *effect_state;
    void *parent_state;
    void *id_offset;
    void *child_slot;

    parent_state = NULL;
    *(Desc3 *)sprite_ids = *(Desc3 *)&D_80088760;
    D_80080A84 = 1;
    object = func_8003FC64(0x11);
    if (object != NULL) {
        parent_state = object + 0x20;
        ((S_80088BD0_0 *)object)->unk_10 = (void *)func_800890EC;
        func_8004491C(object, &D_8008896C);
        ((S_80088BD0_1 *)parent_state)->unk_22 = 0x708;
        ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = 0xF0;
        ((S_80088BD0_1 *)parent_state)->unk_1A = 0;
        ((S_80088BD0_1 *)parent_state)->unk_1C = 0x40;
    }
    child_index = 2;
    start_delay = 0x3C;
    sprite_y = 0xC8;
    unit_scale = 0x1000;
    child_slot = parent_state + 8;
    do {
        object = func_8003FC64(0x111);
        ((S_80088BD0_2 *)child_slot)->unk_04 = object;
        id_offset = (void *)(child_index << 2);
        if (object != NULL) {
            child_state = object + 0x20;
            sprite = ((S_80088BD0_0 *)object)->unk_0C;
            ((S_80088BD0_0 *)object)->unk_10 = (void *)func_80088EDC;
            func_8004491C(object, &D_80044BB0);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = -0x40;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = sprite_y;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0x150000;
            sprite->unk_1E = unit_scale;
            sprite->unk_1C = unit_scale;
            sprite_id = ((S_80088BD0_4 *)((s8 *)sprite_ids + (s32)id_offset))->unk_00;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->unk_0C = 0x808080;
            sprite->unk_08 = sprite_id;
            ((S_80088BD0_5 *)((s8 *)child_state - 0x20))->unk_20 = parent_state;
            ((S_80088BD0_6 *)child_state)->unk_0C = child_index;
            ((S_80088BD0_6 *)child_state)->unk_0A = start_delay;
        }
        start_delay -= 0x1E;
        sprite_y -= 0x10;
        child_index -= 1;
        child_slot -= 4;
    } while (child_index >= 0);
    object = func_8003FC64(1);
    if (object != NULL) {
        ((S_80088BD0_0 *)object)->unk_10 = (void *)func_80088B48;
        func_8004491C(object, &D_80053A88);
        effect_state = object + 0x20;
        effect_state->unk_0C = 0x60;
        effect_state->unk_0E = -0x100;
        effect_state->unk_10 = 0x80;
        effect_state->unk_12 = 0x10;
        effect_state->unk_14 = 0;
        effect_state->unk_16 = 3;
        effect_state->unk_08 = 0x606060;
        ((S_80088BD0_0 *)object)->unk_20.s16 = 0;
        effect_state->unk_04 = parent_state;
    }
    child_index = 1;
    do {
        object = func_8003FC64(0x111);
        ((S_80088BD0_8 *)((s8 *)parent_state + (child_index << 2)))->unk_10 = object;
        if (object != NULL) {
            child_state = object + 0x20;
            sprite = ((S_80088BD0_0 *)object)->unk_0C;
            ((S_80088BD0_0 *)object)->unk_10 = (void *)func_80089A38;
            func_8004491C(object, &D_80044BB0);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = 0xE9;
            if (child_index != 0) {
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = -0x15;
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0x160000;
                func_8003DB94(sprite, &D_8008B270, 0);
                goto common_tail;
            }
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = 0x155;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0xFFEA0000;
            func_8003DB94(sprite, &D_8008B230, 0);
common_tail:
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_10 = 0xFFF80000;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_0C = 0x808080;
            ((S_80088BD0_6 *)child_state)->unk_00 = parent_state;
            ((S_80088BD0_6 *)child_state)->unk_0C = child_index;
        }
        child_index -= 1;
    } while (child_index >= 0);
    object = func_8003FC64(1);
    if (object != NULL) {
        ((S_80088BD0_0 *)object)->unk_10 = (void *)func_80089608;
        ((S_80088BD0_0 *)object)->unk_20.p32 = parent_state;
        ((S_80088BD0_0 *)object)->unk_2E = 0xE00;
    }
}
