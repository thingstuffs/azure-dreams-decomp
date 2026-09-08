#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
void *func_8003FD64();
M2C_UNK func_8004491C();
void func_80047784();
extern M2C_UNK D_80170970;
extern u8 D_80174128[8];

typedef struct S_80975244_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975244_0;   /* temp_v1 in func_80975244 */

typedef struct S_80975244_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80975244_1;   /* temp_v0 in func_80975244 */

typedef struct S_80975244_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x2];
    u16 unk_22;
    u8 pad_24[0x8];
    M2C_UNK * unk_2C;
} S_80975244_2;   /* temp_s0 in func_80975244 */

typedef struct S_80975244_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80975244_3;   /* arg3 in func_80975244 */

typedef struct S_80975244_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975244_4;   /* temp_v1_2 in func_80975244 */

typedef struct S_80975244_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975244_5;   /* arg1 in func_80975244 */

/* Creates an effect from a sprite template and sets its directional frame and position. */
void func_80975244(void *unused, S_80975244_5 *source_pos, void *sprite_template, S_80975244_3 *facing_source) {
    S_80975244_2 *sprite;
    void *effect;
    S_80975244_0 *effect_state;
    S_80975244_4 *effect_pos;
    void *template_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = func_8003FD64(0x112, D_80083498);
    template_data = sprite_template;
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_96 = 7;
        effect_state->unk_AA = 7;
        ((S_80975244_1 *)effect)->unk_10 = &D_80170970;
        effect_state->unk_B0 = source_pos;
        sprite = ((S_80975244_1 *)effect)->unk_0C;
        src = (Block16 *)template_data;
        dst = (Block16 *)sprite;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x50;
        sprite->unk_0D = 0x50;
        sprite->unk_0C = 0x50;
        sprite->unk_10 = 0x20;
        sprite->unk_12 = 0xFF80;
        sprite->unk_22 = 0xFFF1;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        func_8004491C(effect, D_80045340, src, dst);
        sprite->unk_2C = &D_80174128;
        func_80047784(sprite, *((((s32) (*D_80083228 + facing_source->unk_2A + 0x100) >> 9) & 7) + D_80174128), 0);
        effect_pos = ((S_80975244_1 *)effect)->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (u16) source_pos->unk_0A;
    }
}
