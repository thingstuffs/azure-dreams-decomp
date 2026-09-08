#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B7D74_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800B7D74_0;   /* temp_v0 in func_800B7D74 */

typedef struct S_800B7D74_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    u8 pad_14[0x2];
    s16 unk_16;
} S_800B7D74_1;   /* temp_s1 in func_800B7D74 */

typedef struct S_800B7D74_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_800B7D74_2;   /* temp_s2 in func_800B7D74 */

typedef struct S_800B7D74_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800B7D74_3;   /* temp_s0 in func_800B7D74 */

typedef struct S_800B7D74_4 {
    u8 pad_00[0xB0];
    s16 unk_B0;
} S_800B7D74_4;   /* global in func_800B7D74 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089340[];
struct S_80083178__jr {
    /* 0x00 */ char pad0[0xB0];
    /* 0xB0 */ s16 unkB0;                           /* inferred */
    /* 0xB2 */ char padB2[2];
    /* 0xB4 */ void (*callback)();
    /* 0xB8 */ void *field_B8;
    /* 0xBC */ char padBC[0x1C];                    /* maybe part of field_B8[8]? */
    /* 0xD8 */ void *ptr;
};                                                  /* size = 0xDC */

void func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E24C;
extern M2C_UNK D_8006E258;
extern M2C_UNK D_8006E51C;
extern M2C_UNK D_8006E57C;
extern M2C_UNK D_8006E5D4;
extern M2C_UNK D_800B7C14;

/* Spawns an effect at the given position with variant-specific graphics and randomized motion. */
void func_800B7D74(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    struct S_80083178 *game_state = &D_80083178;
    s32 velocity_y;
    S_800B7D74_3 *sprite;
    S_800B7D74_1 *motion;
    S_800B7D74_2 *effect_data;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect == NULL) {
        goto block_12;
    }
    ((S_800B7D74_0 *)effect)->unk_10 = &D_800B7C14;
    func_8004491C(effect, &D_80045340);
    motion = ((S_800B7D74_0 *)effect)->unk_08;
    motion->unk_02 = pos_x;
    effect_data = effect + 0x20;
    motion->unk_06 = pos_y;
    motion->unk_0A = pos_z;
    sprite = ((S_800B7D74_0 *)effect)->unk_0C;
    if (variant >= 5U) {
        goto block_10;
    }
    (void)jt_keep; goto *D_80089340[(u32)(variant)];
jt_c0:
    motion->unk_0C.at02.v = (s16) ((rand() & 0x1F) - 0x10);
    motion->unk_10.at02.v = (s16) ((rand() & 0x1F) - 0x10);
    motion->unk_16 = (s16) (-8 - (rand() & 0x1F));
    effect_data->unk_08 = &D_8006E5D4;
    func_8003DB94(sprite, &D_8006E5D4, 0);
    goto block_11;
jt_c1:
    sprite->unk_08 = &D_8006E24C;
    motion->unk_16 = (s16) (-0x10 - (rand() & 0xF));
    motion->unk_0C.at00.v = (s32) (func_80064584(((S_800B7D74_4 *)game_state)->unk_B0 - 0x300) << 7);
    motion->unk_10.at00.v = (s32) (func_800644B8(((S_800B7D74_4 *)game_state)->unk_B0 - 0x300) << 7);
    goto block_6;
    goto block_6;
jt_c2:
    sprite->unk_08 = &D_8006E258;
    motion->unk_16 = (s16) (-8 - (rand() & 0xF));
    motion->unk_0C.at00.v = (s32) (func_80064584(((S_800B7D74_4 *)game_state)->unk_B0 + 0x500) << 7);
    motion->unk_10.at00.v = (s32) (func_800644B8(((S_800B7D74_4 *)game_state)->unk_B0 + 0x500) << 7);
block_6:
    effect_data->unk_12 = 1;
    goto block_10;
jt_c3:
    effect_data->unk_08 = &D_8006E51C;
    func_8003DB94(sprite, &D_8006E51C, 0);
    motion->unk_0C.at00.v = (s32) (func_80064584(((S_800B7D74_4 *)game_state)->unk_B0) << 7);
    velocity_y = func_800644B8(((S_800B7D74_4 *)game_state)->unk_B0) << 7;
    goto block_9;
jt_c4:
    effect_data->unk_08 = &D_8006E57C;
    func_8003DB94(sprite, &D_8006E57C, 0);
    motion->unk_0C.at00.v = (s32) ((0 - func_80064584(((S_800B7D74_4 *)game_state)->unk_B0)) << 7);
    velocity_y = (0 - func_800644B8(((S_800B7D74_4 *)game_state)->unk_B0)) << 7;
block_9:
    motion->unk_10.at00.v = velocity_y;
    motion->unk_16 = (s16) (-0xC - (rand() & 0xF));
block_10:
block_11:
    sprite->unk_0E = 0x80;
    sprite->unk_0D = 0x80;
    sprite->unk_0C = 0x80;
    sprite->unk_1E = 0x1000;
    sprite->unk_1C = 0x1000;
    effect_data->unk_14 = (s16) ((rand() & 0x1FF) - 0x100);
    effect_data->unk_16 = (s16) ((rand() & 0x1FF) - 0x100);
    effect_data->unk_10 = (s16) ((rand() & 0x1F) + 0x20);
block_12:
    return;
}
