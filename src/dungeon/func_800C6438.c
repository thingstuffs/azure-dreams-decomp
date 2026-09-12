#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800A56E0();
extern M2C_UNK D_80045340;
extern u8 D_80083460[0xC];
extern M2C_UNK D_800CB9DC;
extern u8 D_800DF650[];

typedef struct S_800CBB98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800CBB98_0;   /* temp_v0 in func_800CBB98 */

typedef struct S_800CBB98_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CBB98_1;   /* temp_v1 in func_800CBB98 */

typedef struct S_800CBB98_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CBB98_2;   /* temp_a0 in func_800CBB98 */

typedef struct S_800CBB98_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CBB98_3;   /* held_arg3 in func_800CBB98 */

typedef struct S_800CBB98_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CBB98_4;   /* global_base in func_800CBB98 */

/* Creates an effect at the tile center, links it to its owner, and increments the effect count. */
void *func_800CBB98(s32 tile_x, s32 tile_y, s16 height, void *owner) {
    s16 saved_height = height;
    S_800CBB98_3 *saved_owner = owner;
    register s32 saved_tile_x ASM_REG("$17") = tile_x;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 saved_tile_y ASM_REG("$18") = tile_y;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_800CBB98_2 *sprite;
    S_800CBB98_0 *effect;
    S_800CBB98_1 *position;
    u8 *effect_state;
    u32 tile_x_low;
    u32 tile_y_low;

    effect = func_8003FC64(2);
    if (effect != NULL) {
        effect->unk_10 = &D_800CB9DC;
        func_8004491C(effect, &D_80045340);
        position = effect->unk_08;
        tile_x_low = (u32)saved_tile_x & 0xFFFFU;
        position->unk_02 = (s16) (tile_x_low * 64 + 0x20);
        tile_y_low = (u32)saved_tile_y & 0xFFFFU;
        position->unk_06 = (s16) (tile_y_low * 64 + 0x20);
        position->unk_0A = saved_height;
        sprite = effect->unk_0C;
        sprite->unk_0C = 0x808080;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8003DB94(sprite, D_800DF650, 0);
        effect->unk_20 = saved_owner;
        saved_owner->unk_14 = (s32) (saved_owner->unk_14 | 0x100000);
        func_800A56E0(0x614);
        ASM_KEEP(saved_tile_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_tile_y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        effect_state = D_80083460;
        ((S_800CBB98_4 *)effect_state)->unk_0A = (u16) (((S_800CBB98_4 *)effect_state)->unk_0A + 1);
    }
    return effect;
}
