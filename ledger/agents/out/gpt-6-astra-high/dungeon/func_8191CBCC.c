#include "common.h"
#include "m2c_compat.h"

typedef struct S_8191CBCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8191CBCC_0;   /* temp_v0 in func_8191CBCC */

typedef struct S_8191CBCC_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    union { u16 s; s16 u; } unk_14;   /* accessed as both */
    s16 unk_16;
} S_8191CBCC_1;   /* temp_s2 in func_8191CBCC */

typedef struct S_8191CBCC_2 {
    u8 pad_00[0x10];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u16 unk_12;
} S_8191CBCC_2;   /* held_arg0 in func_8191CBCC */

typedef struct S_8191CBCC_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_8191CBCC_3;   /* temp_s0 in func_8191CBCC */

typedef struct S_8191CBCC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8191CBCC_4;   /* copy_dst in func_8191CBCC */


void func_80024554(void) __attribute__((noreturn));                /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                             /* extern */
typedef struct { s32 w0, w1, w2, w3, w4, w5; } Blk24;
extern M2C_UNK D_80024288;
extern M2C_UNK D_80024F74;
extern M2C_UNK D_80045C34;

/* Creates an effect with randomized appearance and a depth-adjusted copy of the source transform. */
s32 func_8191CBCC(void *params_input, void *transform_input) {
    register S_8191CBCC_2 *params ASM_REG("$19") = params_input;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *source_transform = transform_input;
    register void *result_obj ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 depth_scale;
    s32 size_fixed;
    s32 variant_random;
    s32 angle_random;
    s32 adjusted_depth;
    s32 angle;
    S_8191CBCC_3 *render;
    S_8191CBCC_1 *state;
    void *object;

    object = func_8003FC64(0x212);
    ASM_KEEP(params);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(source_transform);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (object != NULL) {
        state = object + 0x20;
        ((S_8191CBCC_0 *)object)->unk_10 = &D_80024288;
        ((S_8191CBCC_0 *)object)->unk_20 = params;
        state->unk_0E = 0;
        state->unk_10 = 0;
        variant_random = rand();
        state->unk_12 = (s16)(variant_random % 7);
        state->unk_14.s = (u16) params->unk_12;
        state->unk_16 = (s16) (0x1C - params->unk_10.s);
        render = ((S_8191CBCC_0 *)object)->unk_0C;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_08 = &D_80024F74;
        render->unk_14 = (u16) (render->unk_14 | 0xC);
        render->unk_10 = (u16) (render->unk_10 | 0x60);
        angle = rand(variant_random / 7);
        angle_random = angle;
        angle >>= 0xC;
        if (angle_random < 0) {
            angle = (s32) (angle_random + 0xFFF) >> 0xC;
        }
        angle = angle_random - (angle << 0xC);
        render->unk_1A = (s16)angle;
        size_fixed = params->unk_10.u << 8;
        render->unk_1E = size_fixed;
        render->unk_1C = size_fixed;
        func_8004491C(object, &D_80045C34);
        {
            S_8191CBCC_4 *transform;

            transform = ((S_8191CBCC_0 *)object)->unk_08;
            *(Blk24 *) transform = *(Blk24 *) source_transform;
            depth_scale = state->unk_14.u;
            adjusted_depth = ((transform->unk_14 * depth_scale) -
                          (params->unk_10.u << 0x13)) / depth_scale;
            result_obj = object;
            ASM_KEEP(result_obj);   /* MATCH pin: retail keeps a computation the compiler would drop */
            transform->unk_14 = adjusted_depth;
            func_80024554();
        }
    }
    result_obj = NULL;
    return (s32)result_obj;
}
