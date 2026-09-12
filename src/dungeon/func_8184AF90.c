#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();      /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800246AC;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEB28;
extern u8 D_800E0000[];

typedef struct S_80024790_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_80024790_0;   /* temp_v0 in func_80024790 */

typedef struct S_80024790_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024790_1;   /* arg0 in func_80024790 */

typedef struct S_80024790_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
} S_80024790_2;   /* temp_s3 in func_80024790 */

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
} S_80024790_3;   /* temp_s0 in func_80024790 */

typedef struct S_80024790_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024790_4;   /* temp_s0_2 in func_80024790 */

/* Creates an effect at the origin with index-dependent color, scale, and position. */
s32 func_80024790(S_80024790_1 *origin, s32 index) {
    s32 signed_index;
    s32 index_high;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s16 scale;
    s32 frame_dividend;
    register s32 color_index ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 angle;
    s32 angle_dividend;
    s32 height;
    s8 shade;
    u8 *sprite_data;
    S_80024790_3 *sprite;
    S_80024790_4 *position;
    S_80024790_2 *state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        color_index = index;
        ASM_KEEP(color_index);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ((S_80024790_0 *)effect)->unk_10 = &D_800246AC;
        ((S_80024790_0 *)effect)->unk_20 = (u16) origin->unk_02;
        state = effect + 0x20;
        state->unk_02 = (u16) origin->unk_06;
           /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        index_high = index << 16;
        signed_index = index_high >> 16;
        angle = signed_index << 8;
        angle_dividend = angle;
        state->unk_04 = (u16) origin->unk_0A;
        if (angle < 0) {
            angle_dividend = angle + 0xFFF;
        }
        frame_dividend = signed_index;
        state->unk_08 = (s16) (angle - ((angle_dividend >> 0xC) << 0xC));
        sprite = ((S_80024790_0 *)effect)->unk_0C;
        shade = ~(color_index * 8);
        sprite->unk_0E = shade;
        sprite->unk_0D = shade;
        sprite->unk_0C = shade;
        ASM_KEEP(color_index);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        sprite_data = D_800E0000 - 0x14D8;
        if (signed_index < 0) {
            frame_dividend = signed_index + 7;
        }
        func_8003DB94(sprite, sprite_data, (s16) (7 - (signed_index - ((frame_dividend >> 3) * 8))));
        scale = (signed_index << 6) + 0x1000;
        sprite->unk_1E = scale;
        sprite->unk_1C = scale;
        sprite->unk_10 = (u16) (sprite->unk_10 | 0x20);
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        func_8004491C(effect, &D_80045340);
        position = ((S_80024790_0 *)effect)->unk_08;
        position->unk_02 = (s16) (((S_80024790_0 *)effect)->unk_20 + ((s32) (func_800644B8(state->unk_08) * 2) >> 8));
        position->unk_06 = (s16) (state->unk_02 + ((s32) (func_80064584(state->unk_08) * 2) >> 8));
        result = (s32) effect;
        height = state->unk_04 - (index * 8);
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        position->unk_0A = (u16) height;
        return;
    }
    return 0;
}
