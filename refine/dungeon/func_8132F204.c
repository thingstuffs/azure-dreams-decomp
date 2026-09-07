#include "common.h"
#include "m2c_compat.h"

typedef struct S_80166204_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80166204_3;   /* temp_v0 in func_80166204 */

typedef struct S_80166204_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80166204_4;   /* arg0 in func_80166204 */

typedef struct S_80166204_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80166204_5;   /* ((S_80166204_3 *)temp_v0)->unk_08 in func_80166204 */

typedef struct S_80166204_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80166204_6;   /* ((S_80166204_4 *)arg0)->unk_08 in func_80166204 */


typedef struct S_80166204_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80166204_0;   /* temp_v0 in func_80166204 */

typedef struct S_80166204_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
} S_80166204_1;   /* temp_s0 in func_80166204 */

typedef struct S_80166204_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    union { u16 s; volatile u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80166204_2;   /* temp_a0 in func_80166204 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80165A0C;

/* Creates an offset effect with randomized motion and initializes its display properties. */
void func_80166204(S_80166204_4 *source, s16 effect_value, s32 unused, s32 offset_x, s32 offset_y, s32 offset_z, s32 velocity_z) {
    register s32 saved_offset_y ASM_REG("$19") = offset_y;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 saved_offset_z = offset_z;
    register s32 color_component ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 sprite_flags;
    S_80166204_2 *sprite;
    S_80166204_1 *effect_state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        ((S_80166204_0 *)effect)->unk_10 = &D_80165A0C;
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_02 = (s16) (((S_80166204_6 *)(source->unk_08))->unk_02 + offset_x);
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_06 = (s16) (((S_80166204_6 *)(source->unk_08))->unk_06 + saved_offset_y);
        ASM_KEEP(saved_offset_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_0A = (s16) (((S_80166204_6 *)(source->unk_08))->unk_0A + saved_offset_z);
        ASM_KEEP(saved_offset_z);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        effect_state = effect + 0x20;
        effect_state->unk_42 = (u16) ((S_80166204_6 *)(source->unk_08))->unk_02;
        effect_state->unk_44 = (u16) ((S_80166204_6 *)(source->unk_08))->unk_06;
        effect_state->unk_46 = (u16) ((S_80166204_6 *)(source->unk_08))->unk_0A;
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80166204_5 *)(((S_80166204_3 *)effect)->unk_08))->unk_14 = velocity_z;
        effect_state->unk_14 = effect_value;
        effect_state->unk_32 = 8;
        effect_state->unk_34 = 8;
        func_8004491C(effect, &D_80045340);
        sprite = ((S_80166204_0 *)effect)->unk_0C;
        sprite->unk_1E = 0x2AA;
        sprite->unk_1C = 0x2AA;
        sprite->unk_0C = 0xFF;
        color_component = 0x20;
        sprite->unk_0E = color_component;
        sprite->unk_0D = color_component;
        sprite->unk_12 = 0x7DCF;
        sprite_flags = sprite->unk_14.s & 0xFFF3;
        sprite_flags |= 2;
        ASM_KEEP_NV(sprite_flags);   /* MATCH pin: load-bearing for the whole function shape */
        sprite->unk_14.u = sprite_flags;
        sprite_flags |= 0x100;
        sprite->unk_14.s = sprite_flags;
        func_8003DB94(sprite, &D_800DE870, 0);
    }
}

/* MECHANISM: Seven ABI arguments preserve the unused a2 slot; guarded s3/s4
   locals hold stack inputs offset_y/offset_z across the allocator-crossing first call.
   A v1 byte-value pin plus volatile midpoint and tied keep preserve the v0 RMW chain. */
