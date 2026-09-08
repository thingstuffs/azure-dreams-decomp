#include "common.h"
#include "records/Rec_D_80174CD8.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;


typedef struct S_80172160_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_80172160_1;   /* temp_v1 in func_80172160 */

typedef struct S_80172160_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172160_2;   /* temp_v0 in func_80172160 */

typedef struct S_80172160_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80172160_3;   /* temp_a0 in func_80172160 */

typedef struct S_80172160_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80172160_4;   /* temp_s0 in func_80172160 */

typedef struct S_80172160_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172160_5;   /* temp_s2 in func_80172160 */

typedef struct S_80172160_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172160_6;   /* temp_a0_2 in func_80172160 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_801720D0;
extern Rec_D_80174CD8 *D_80174CD8;

/* Spawn and initialize an effect at a random offset from the source position. */
void func_80172160(void)
{
    S_80172160_3 *sprite_header;
    S_80172160_6 *sprite;
    S_80172160_4 *effect_pos;
    S_80172160_5 *source_pos;
    void *effect;
    S_80172160_1 *effect_state;
    s32 random_offset;
    s32 coord;

    source_pos = D_80174CD8->unk_08;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_16 = 0x1E;
        effect_state->unk_18 = 0x1E;
        ((S_80172160_2 *)effect)->unk_10 = &D_801720D0;
        func_8004491C(effect, &D_80045340);
        sprite_header = ((S_80172160_2 *)effect)->unk_0C;
        sprite_header->unk_06 = 0;
        effect_pos = ((S_80172160_2 *)effect)->unk_08;
        effect_pos->unk_00.at00.v = source_pos->unk_00;
        effect_pos->unk_04.at00.v = source_pos->unk_04;
        effect_pos->unk_08 = source_pos->unk_08;
        random_offset = rand(sprite_header);
        coord = effect_pos->unk_00.at02.v;
        random_offset &= 0x3F;
        coord -= 0x20;
        coord += random_offset;
        effect_pos->unk_00.at02.v = coord;
        random_offset = rand();
        coord = effect_pos->unk_04.at02.v;
        random_offset &= 0x3F;
        coord -= 0x20;
        coord += random_offset;
        effect_pos->unk_04.at02.v = coord;
        sprite = ((S_80172160_2 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_14 |= 0x80;
        func_8003DB94(sprite, &D_800DE870, 0);
    }
}
