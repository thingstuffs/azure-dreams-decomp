#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002626C_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002626C_3;   /* temp_v0 in func_8002626C */

typedef struct S_8002626C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002626C_4;   /* ((S_8002626C_3 *)temp_v0)->unk_08 in func_8002626C */




s16 func_8002458C();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8002615C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

typedef struct S_8002626C_0 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    u8 pad_32[0x56];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_8002626C_0;   /* temp_s0 in func_8002626C */

typedef struct S_8002626C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8002626C_1;   /* temp_v0 in func_8002626C */

typedef struct S_8002626C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002626C_2;   /* temp_s1 in func_8002626C */

/* Creates a colored effect at an offset position with velocity toward its base. */
void func_8002626C(
    s32 unused_0, s32 unused_1, s32 unused_2, s32 unused_3,
    s32 offset_x, s32 offset_y, s32 offset_z, s32 base_x, s32 base_y, s32 base_z) {
    s16 color_channel;
    S_8002626C_0 *effect_state;
    S_8002626C_2 *sprite;
    void *effect;
    register s32 held_offset_x ASM_REG("$22") = offset_x;   /* MATCH pin: load-bearing for the whole function shape */
    register s32 held_offset_y ASM_REG("$23") = offset_y;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_28 = 0x14;
        ((S_8002626C_1 *)effect)->unk_10 = &D_8002615C;
        func_8004491C(effect, &D_80045340);
        sprite = ((S_8002626C_1 *)effect)->unk_0C;
        sprite->unk_10 = 0x40;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        ((S_8002626C_4 *)(((S_8002626C_3 *)effect)->unk_08))->unk_02 =
            (s16) (s32) &((s8 *) base_x)[held_offset_x];
        ((S_8002626C_4 *)(((S_8002626C_3 *)effect)->unk_08))->unk_06 =
            (s16) (s32) &((s8 *) base_y)[held_offset_y];
        ((S_8002626C_4 *)(((S_8002626C_3 *)effect)->unk_08))->unk_0A = (s16) (base_z + offset_z);
        effect_state->unk_88 = (s32) (0 - ((s32) (held_offset_x << 0x10) >> 7));
        effect_state->unk_8C = (s32) (0 - ((s32) (held_offset_y << 0x10) >> 7));
        effect_state->unk_2C = (s16) base_x;
        effect_state->unk_2E = (s16) base_y;
        effect_state->unk_30 = (s16) base_z;
        effect_state->unk_90 = (s32) (0 - ((s32) (offset_z << 0x10) >> 7));
        sprite = ((S_8002626C_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x3000;
        sprite->unk_1C = 0x3000;
        color_channel = func_8002458C(3);
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        if (color_channel == 0) {
            sprite->unk_0C = 0x10;
        }
        if (color_channel == 1) {
            sprite->unk_0D = 0x10;
        }
        if (color_channel == 2) {
            sprite->unk_0E = 0x10;
        }
        sprite->unk_12 = 0x7DCF;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
        func_8003DB94(sprite, &D_800DE870, 0);
        ASM_KEEP(held_offset_x);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(held_offset_y);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }
}
/* MECHANISM: The ten-argument ABI and reused pointer local produce the retail
   0x38 frame, full hold set, and reload seam. Tail-kept s6/s7 pins preserve
   scheduling; byte-pointer BASE[index] sums select retail addu operand order. */
