#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

M2C_UNK func_8003DB94();      /* extern */
s32 func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800246AC;
extern u8 D_800E0000[];

typedef struct S_80024790_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_80024790_0;

   /* arg0 in func_80024790 */

typedef struct S_80024790_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
} S_80024790_2;

typedef struct S_80024790_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024790_3;

typedef struct S_80024790_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024790_4;

/* Creates an effect at the origin with index-dependent color, scale, and position. */
s32 func_80024790(MovingPosition *origin, u16 index) {
    u8 color_index;
    s32 frame;
    s16 scale;
    s8 shade;
    S_80024790_3 *sprite;
    S_80024790_4 *position;
    S_80024790_2 *state;
    void *effect;

    color_index = index;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        ((S_80024790_0 *)effect)->unk_10 = &D_800246AC;
        ((S_80024790_0 *)effect)->unk_20 = (u16) origin->unk_02;
        state = effect + 0x20;
        state->unk_02 = (u16) origin->unk_06;
        frame = (s16) index;
        state->unk_04 = (u16) origin->unk_0A;
        state->unk_08 = (s16) ((frame << 8) % 0x1000);
        sprite = ((S_80024790_0 *)effect)->unk_0C;
        color_index <<= 3;
        shade = ~color_index;
        sprite->unk_0E = shade;
        sprite->unk_0D = shade;
        sprite->unk_0C = shade;
        func_8003DB94(sprite, D_800E0000 - 0x14D8, (s16) (7 - frame % 8));
        scale = (frame << 6) + 0x1000;
        sprite->unk_1E = scale;
        sprite->unk_1C = scale;
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        func_8004491C(effect, func_80045340);
        position = ((S_80024790_0 *)effect)->unk_08;
        position->unk_02 = (s16) (((S_80024790_0 *)effect)->unk_20 + ((s32) (func_800644B8(state->unk_08) * 2) >> 8));
        position->unk_06 = (s16) (state->unk_02 + ((s32) (func_80064584(state->unk_08) * 2) >> 8));
        index <<= 3;
        position->unk_0A = state->unk_04 - index;
        return (s32) effect;
    }
    return 0;
}
