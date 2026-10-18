#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */

s32 rand();                                /* extern */
extern M2C_UNK D_800263F8;



typedef struct S_8002596C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8002596C_1;

typedef struct S_8002596C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002596C_2;

/* Create a sprite effect at the given position with a randomized rotation. */
void create_a_sprite_effect_position_randomized_rotation(s16 x, s16 y, s16 z) {
    S_8002596C_1 *transform;
    S_8002596C_2 *sprite;
    ObjectNodeHeader *effect;

    effect = func_8003FC64(0x202);
    if (effect != NULL) {
        effect->unk_10 = (s32 *)advance_and_fade_effect_flagging_expiration_timer_runs_out;
        func_8004491C(effect, func_80045340);
        transform = effect->unk_08;
        transform->unk_02 = x;
        transform->unk_06 = y;
        transform->unk_0A = z;
        transform->unk_0E = 0;
        transform->unk_12 = 0;
        transform->unk_16 = (s16) (rand() & 7);
        sprite = effect->unk_0C;
        sprite->unk_0C = 0x808080;
        func_8003DB94(sprite, &D_800263F8, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x20;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        ((s16 *)(effect + 1))[0x1A / 2] = 0x10;
    }
}
