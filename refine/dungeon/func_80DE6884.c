#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_80DE6884_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80DE6884_0;   /* setup_arg1 in func_80DE6884 */

typedef struct S_80DE6884_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80DE6884_1;   /* temp_v0 in func_80DE6884 */

typedef struct S_80DE6884_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80DE6884_2;   /* temp_s0 in func_80DE6884 */

typedef struct S_80DE6884_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80DE6884_3;   /* held_arg1 in func_80DE6884 */

typedef struct S_80DE6884_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    union { volatile s32 s; s32 u; } unk_14;   /* accessed as both */
} S_80DE6884_4;   /* temp_s0_2 in func_80DE6884 */

typedef struct S_80DE6884_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80DE6884_5;   /* held_arg0 in func_80DE6884 */

typedef struct {
    s32 words[6];
} Copy24;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL 0

M2C_UNK func_8003DB94();
s32 func_8003DE58(s32, void *, s16 *, s32);
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584(s32, s32);
s32 rand();
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DEA68[3];
extern M2C_UNK D_80173F8C[3];

/* Spawns four effects with origin offsets, random rotation, and velocity based on the owner heading. */
void func_80DE6884(void *owner_arg, void *motion_arg, void *origin_arg) {
    u16 offsets[3];
    s32 position_x;
    s32 position_y;
    s32 position_z;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 random_value;
    s32 effect_index;
    s32 biased_random;
    register S_80DE6884_3 *source_motion ASM_REG("$21") = motion_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_80DE6884_5 *owner;
    M2C_UNK *effect_data;
    u32 effect_data_page;
    register S_80DE6884_0 *origin ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 *offset_ptr;
    void *render_config;
    S_80DE6884_2 *render_data;
    S_80DE6884_4 *motion;
    S_80DE6884_1 *effect;

    origin = origin_arg;
    offset_ptr = (s16 *)offsets;
    effect_index = 0;
    offsets[2] = 0;
    offsets[1] = 0;
    offsets[0] = 0;
    owner = owner_arg;
    ASM_KEEP(offset_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_8003DE58(origin->unk_08, origin, offset_ptr, effect_index);
    effect_data_page = 0x80170000;
    ASM_KEEP(effect_data_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    effect_data = (M2C_UNK *)(effect_data_page + 0x3F8C);
    do {
        effect = func_8003FC64(0x212);
        if (effect != NULL) {
            render_config = &D_800DEA68;
            render_data = effect->unk_0C;
            effect->unk_10 = effect_data;
            render_data->unk_0E = 0x60;
            render_data->unk_0D = 0x60;
            render_data->unk_0C = 0x60;
            render_data->unk_14 = (u16)(render_data->unk_14 | 0xC);
            render_data->unk_10 = (u16)(render_data->unk_10 | 0x20);
            func_8003DB94(render_data, render_config, 0);
            func_800478B8(render_data);
            biased_random = rand();
            random_value = biased_random;
            if (random_value < 0) {
                biased_random = random_value + 0xFFF;
            }
            render_data->unk_1A = (s16)(random_value - ((biased_random >> 0xC) << 0xC));
            render_data->unk_1E = 0x1000;
            render_data->unk_1C = 0x1000;
            func_8004491C(effect, &D_80045340);
            motion = effect->unk_08;
            position_x = source_motion->unk_00;
            position_y = source_motion->unk_04;
            position_z = source_motion->unk_08;
            velocity_x = source_motion->unk_0C;
            motion->unk_00.at00.v = position_x;
            motion->unk_04.at00.v = position_y;
            motion->unk_08.at00.v = position_z;
            motion->unk_0C = velocity_x;
            velocity_y = source_motion->unk_10;
            velocity_z = source_motion->unk_14;
            motion->unk_10 = velocity_y;
            motion->unk_14.s = velocity_z;
            motion->unk_00.at02.v = (u16)(motion->unk_00.at02u.v + offsets[0]);
            motion->unk_04.at02.v = (u16)(motion->unk_04.at02.v + offsets[1]);
            motion->unk_08.at02.v = (u16)(motion->unk_08.at02.v + offsets[2]);
            motion->unk_0C = (s32)((func_80064584(
                owner->unk_2A,
                velocity_x) >> 4) << 0xB);
            motion->unk_10 = (s32)((func_800644B8(owner->unk_2A) >> 4) << 0xB);
            motion->unk_14.u = 0x9C40;
        }
        effect_index += 1;
    } while (effect_index < 4);
}

/* MECHANISM: One aliased three-halfword stack object and held s2-s5 roles reproduce the 0x38 frame.
   A grouped 24-byte scalar copy keeps its fourth word live in a1 for the two-argument callee ABI.
   Split v0-to-s4 page formation plus paired volatile store/read ordering closes the final rotations. */
