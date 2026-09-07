#include "common.h"
#include "m2c_compat.h"

typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
s32 func_80167088();                         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80165AB8;
extern M2C_UNK D_80173B34[3];


typedef struct S_80165D0C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165D0C_0;   /* arg0 in func_80165D0C */

typedef struct S_80165D0C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
} S_80165D0C_1;   /* temp_s1 in func_80165D0C */

typedef struct S_80165D0C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80165D0C_2;   /* temp_s0 in func_80165D0C */

typedef struct S_80165D0C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165D0C_3;   /* (*(void **)((u8 *)temp_v0 + 8)) in func_80165D0C */

typedef struct S_80165D0C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80165D0C_4;   /* ((S_80165D0C_0 *)arg0)->unk_08 in func_80165D0C */

/* Spawn an effect relative to the source with randomized motion and sprite size. */
void func_80165D0C(S_80165D0C_0 *source, s16 duration, s32 scale, s32 offset_x, s32 offset_y, s32 offset_z, s32 velocity_z) {
    s32 sprite_scale;
    S_80165D0C_2 *sprite;
    S_80165D0C_1 *effect_state;
    void *effect;
    register s32 held_offset_y ASM_REG("$19") = offset_y;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 held_offset_z ASM_REG("$20") = offset_z;   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    effect = func_8003FC64(0x12);
    if (effect != NULL) {
        (*(M2C_UNK **)((u8 *)effect + 0x10)) = &D_80165AB8;
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_02 = (s16) (((S_80165D0C_4 *)(source->unk_08))->unk_02 + offset_x);
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_06 = (s16) (((S_80165D0C_4 *)(source->unk_08))->unk_06 + held_offset_y);
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_0A = (s16) (((S_80165D0C_4 *)(source->unk_08))->unk_0A + held_offset_z);
        effect_state = effect + 0x20;
        effect_state->unk_42 = (u16) ((S_80165D0C_4 *)(source->unk_08))->unk_02;
        effect_state->unk_44 = (u16) ((S_80165D0C_4 *)(source->unk_08))->unk_06;
        effect_state->unk_46 = (u16) ((S_80165D0C_4 *)(source->unk_08))->unk_0A;
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((*(void **)((u8 *)effect + 8))))->unk_14 = (s32) (velocity_z + 0xFFFC0000);
        effect_state->unk_60 = 0x10000;
        effect_state->unk_14 = duration;
        effect_state->unk_32 = 0;
        effect_state->unk_34 = 0;
        func_8004491C(effect, &D_80045340);
        sprite = (*(void **)((u8 *)effect + 0xC));
        sprite->unk_06 = -4;
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFF3);
        sprite_scale = 0x1000 / (s32) (func_80167088(5) + 8);
        sprite->unk_0C = scale;
        sprite->unk_1E = (s16) sprite_scale;
        sprite->unk_1C = (s16) sprite_scale;
        (*(s32 *)((u8 *)effect + 0x20)) = scale;
        effect_state->unk_04 = scale;
        effect_state->unk_08 = scale;
        (*(Copy12 *)((u8 *)effect + 0x56)) =
            (*(Copy12 *)((u8 *)D_80173B34 + 0));
        sprite->unk_08 = (void *) (effect + 0x56);
    }
}

/* MECHANISM: Pinned stack args offset_y/offset_z create the retail s3/s4 hold set and 0x30 frame;
   end-placed ASM_KEEP guards preserve the exact prologue and call-delay scheduling.
   A packed Copy12 assignment emits the retail lwl/lwr and swl/swr copy sequence. */
