#include "modules/dungeon_ovl_193c848.h"

s32 create_scaled_rotating_effect(void *params_input, void *transform_input) {
    Row_8191CBCC_S_8191CBCC_2 *params = params_input;
    void *source_transform = transform_input;
    s16 depth_scale;
    s32 size_fixed;
    s32 variant_random;
    s32 angle_random;
    s32 adjusted_depth;
    s32 angle;
    Row_8191CBCC_S_8191CBCC_3 *render;
    Row_8191CBCC_S_8191CBCC_1 *state;
    void *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        ((Row_8191CBCC_S_8191CBCC_0 *)object)->unk_10 = &D_80024288;
        ((Row_8191CBCC_S_8191CBCC_0 *)object)->unk_20 = params;
        state->unk_0E = 0;
        state->unk_10 = 0;
        variant_random = rand();
        state->unk_12 = (s16)(variant_random % 7);
        state->unk_14.s = (u16) params->unk_12;
        state->unk_16 = (s16) (0x1C - params->unk_10.s);
        render = ((Row_8191CBCC_S_8191CBCC_0 *)object)->unk_0C;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_08 = &D_80024F74;
        render->unk_14 = (u16) (render->unk_14 | 0xC);
        render->unk_10 = (u16) (render->unk_10 | 0x60);
        angle = rand();
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
            Row_8191CBCC_S_8191CBCC_4 *transform;

            transform = ((Row_8191CBCC_S_8191CBCC_0 *)object)->unk_08;
            *(Blk24 *) transform = *(Blk24 *) source_transform;
            depth_scale = state->unk_14.u;
            adjusted_depth = ((transform->unk_14 * depth_scale) -
                              (params->unk_10.u << 0x13)) / depth_scale;
            transform->unk_14 = adjusted_depth;
            return (s32)object;
        }
    }
    return 0;
}
