/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
void func_8004491C(void *, void *); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_800250B4[];
extern u8 D_80028220[];
extern u8 D_80045C34[];

typedef struct S_81959B44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81959B44_0;   /* temp_v0 in func_81959B44 */

typedef struct S_81959B44_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81959B44_1;   /* temp_s2 in func_81959B44 */

typedef struct S_81959B44_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    u16 unk_3C;
} S_81959B44_2;   /* temp_s0 in func_81959B44 */

typedef struct S_81959B44_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0xA];
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
} S_81959B44_3;   /* temp_s2_2 in func_81959B44 */

/* Create sixteen objects in a ring around the given center with a scaled radius. */
void *func_81959B44(s16 center_x, s16 center_y, s16 center_z, s16 radius_scale) {
    s32 call_pad_4;
    s32 call_pad_6;
    s32 call_pad_8;
    s32 div6_magic;
    M2C_UNK object_flags;
    s16 pos_y;
    s16 pos_x;
    s32 ring_index;
    s32 y_scale_product;
    s32 y_component;
    s32 x_component;
    s32 x_offset;
    s32 angle;
    s32 neg_y_fixed;
    s32 x_fixed;
    S_81959B44_2 *state;
    S_81959B44_1 *position;
    S_81959B44_3 *transform;
    void *object;

    ring_index = 0;
    div6_magic = 0x2AAAAAAB;
    do {
        object_flags = 0x12;
        if (radius_scale != 0) {
            object_flags = 0x212;
        }
        object = func_8003FC64(object_flags);
        if (object != NULL) {
            ((S_81959B44_0 *)object)->unk_10 = &D_800250B4;
            func_8004491C(object, &D_80045C34);
            angle = ring_index << 8;
            position = ((S_81959B44_0 *)object)->unk_08;
            x_component = func_80064584(angle) >> 7;
            x_offset = x_component + ((s32) ((s16) x_component * radius_scale) >> 2);
            y_component = func_800644B8(angle) >> 7;
            y_scale_product = (s16) y_component * radius_scale;
            state = object + 0x20;
            pos_x = center_x + x_offset;
            position->unk_02 = pos_x;
            state->unk_1C = pos_x;
            pos_y = center_y + (y_component + (y_scale_product >> 2));
            position->unk_06 = pos_y;
            state->unk_1E = pos_y;
            position->unk_0A = center_z;
            state->unk_20 = center_z;
            transform = ((S_81959B44_0 *)object)->unk_0C;
            transform->unk_08 = &D_80028220;
            transform->unk_1C = 0x1000;
            transform->unk_1A = (u16) (angle + 0x400);
            neg_y_fixed = 0 - (func_800644B8(angle) << 0xC);
            transform->unk_16 = (s16) ((neg_y_fixed / 6) >> 0xC);
            x_fixed = func_80064584(angle) << 0xC;
            transform->unk_18 = (s16) ((x_fixed / 6) >> 0xC);
            state->unk_14 = pos_x;
            state->unk_16 = pos_y;
            state->unk_18 = center_z;
            state->unk_38 = ring_index;
            state->unk_30 = (s16) (radius_scale + 4);
            state->unk_3C = (u16) radius_scale;
        }
        ring_index += 1;
    } while (ring_index < 0x10);
    return object;
}
