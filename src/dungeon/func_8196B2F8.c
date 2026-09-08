#include "common.h"
#include "m2c_compat.h"

typedef struct S_8196B2F8_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x64];
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B2F8_0;   /* temp_s1 in func_8196B2F8 */

typedef struct S_8196B2F8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8196B2F8_1;   /* temp_v0 in func_8196B2F8 */

typedef struct S_8196B2F8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8196B2F8_2;   /* temp_a0 in func_8196B2F8 */

typedef struct S_8196B2F8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B2F8_3;   /* temp_s0 in func_8196B2F8 */

typedef struct S_8196B2F8_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8196B2F8_4;   /* temp_a0_2 in func_8196B2F8 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                       /* extern */
extern M2C_UNK D_800244E4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800DE870;

/* Creates an effect with randomized position offsets and initializes its rendering state. */
void func_8196B2F8(s32 unused_0, s32 unused_1, s32 unused_2, s32 offset_x, s32 offset_y, s32 offset_z) {
    s32 jitter;
    register s32 world_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 jittered_coord;
    s32 origin_coord;
    s16 random_size;
    u16 render_flags;
    register u16 render_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *render_or_origin;
    S_8196B2F8_4 *render_state;
    S_8196B2F8_3 *position;
    S_8196B2F8_0 *effect_state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        random_size = (rand() & 7) + 0x20;
        effect_state->unk_2C = random_size;
        effect_state->unk_2E = random_size;
        ((S_8196B2F8_1 *)effect)->unk_10 = &D_800244E4;
        func_8004491C(effect, &D_80045340);
        render_or_origin = ((S_8196B2F8_1 *)effect)->unk_0C;
        render_value = ((S_8196B2F8_2 *)render_or_origin)->unk_14;
        ((S_8196B2F8_2 *)render_or_origin)->unk_06.s = 0;
        render_value |= 0xC;
        ((S_8196B2F8_2 *)render_or_origin)->unk_14 = render_value;
        ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render_flags = render_value;
        ASM_KEEP(render_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        render_value = 0x60;
        render_flags |= 2;
        ((S_8196B2F8_2 *)render_or_origin)->unk_10 = render_value;
        ((S_8196B2F8_2 *)render_or_origin)->unk_14 = render_flags;
        render_or_origin = (void *) 0x80080000;
        ASM_KEEP(render_or_origin);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        position = ((S_8196B2F8_1 *)effect)->unk_08;
        render_or_origin = (void *) ((u8 *) render_or_origin + 0x3780);
        position->unk_02 = offset_x;
        position->unk_06 = (u16) offset_y;
        position->unk_0A = (u16) offset_z;
        origin_coord = ((S_8196B2F8_2 *)render_or_origin)->unk_02;
        ASM_KEEP(origin_coord);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        world_coord = offset_x;
        ASM_KEEP(world_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        world_coord += origin_coord;
        position->unk_02 = (u16) world_coord;
        origin_coord = ((S_8196B2F8_2 *)render_or_origin)->unk_06.u;
        ASM_KEEP(origin_coord);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        world_coord = offset_y;
        ASM_KEEP(world_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        world_coord += origin_coord;
        position->unk_06 = (u16) world_coord;
        origin_coord = ((S_8196B2F8_2 *)render_or_origin)->unk_0A;
        ASM_KEEP(origin_coord);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        world_coord = offset_z;
        ASM_KEEP(world_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        world_coord += origin_coord;
        position->unk_0A = (u16) world_coord;
        jitter = rand() & 0x1F;
        jittered_coord = position->unk_02;
        jittered_coord -= 0x10;
        jittered_coord += jitter;
        position->unk_02 = (u16) jittered_coord;
        jitter = rand() & 0x1F;
        jittered_coord = position->unk_06;
        jittered_coord -= 0x10;
        jittered_coord += jitter;
        position->unk_06 = (u16) jittered_coord;
        jitter = rand() & 0x1F;
        jittered_coord = position->unk_0A;
        jittered_coord -= 0x10;
        jittered_coord += jitter;
        position->unk_0A = (u16) jittered_coord;
        effect_state->unk_94 = rand();
        effect_state->unk_A0 = 0x1000;
        render_state = ((S_8196B2F8_1 *)effect)->unk_0C;
        render_state->unk_1C = 0xC00;
        render_state->unk_1E = 0xC00;
        render_state->unk_0E = 0x80;
        render_state->unk_0D = 0x80;
        render_state->unk_0C = 0x80;
        render_state->unk_12 = 0x7DCF;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x100);
        func_8003DB94(render_state, &D_800DE870, 0);
    }
}

/* MECHANISM: The s32 fourth-argument ABI and split RMW live ranges recover the seven-register 0x30 frame.
   Guarded v0/v1 seams preserve the two flag updates and coordinate accumulation order.
   A fenced 0x80080000 page base around the independent s0 load emits retail's lui/lw/addiu sequence. */
