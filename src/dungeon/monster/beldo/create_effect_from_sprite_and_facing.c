#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

void *allocate_list_node();
s32 register_node();
void select_sprite_entry();
extern M2C_UNK D_80170D44;
extern u8 D_80173EB4[8];

typedef struct S_80170E18_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
} S_80170E18_0;

typedef struct S_80170E18_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80170E18_1;

typedef struct S_80170E18_2 {
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
} S_80170E18_2;

typedef struct S_80170E18_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170E18_3;   /* arg3 in create_effect_from_sprite_and_facing */



   /* arg1 in create_effect_from_sprite_and_facing */

/* Creates an effect using the supplied sprite data, transform, and facing. */
void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, S_80170E18_3 *facing_source) {
    S_80170E18_2 *sprite;
    void *effect;
    S_80170E18_0 *effect_state;
    MovingPosition *transform;
    void *sprite_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    sprite_data = sprite_template;
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_96 = 7;
        effect_state->unk_A8 = 7;
        ((S_80170E18_1 *)effect)->unk_10 = &D_80170D44;
        effect_state->unk_AC = source_transform;
        sprite = ((S_80170E18_1 *)effect)->unk_0C;
        src = (Block16 *)sprite_data;
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
        register_node(effect, project_sprite_chain);
        sprite->unk_2C = &D_80173EB4;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7)
            + D_80173EB4), 0);
        transform = ((S_80170E18_1 *)effect)->unk_08;
        transform->unk_02 = (u16) source_transform->unk_02;
        transform->unk_06 = (u16) source_transform->unk_06;
        transform->unk_0A = (u16) source_transform->unk_0A;
    }
}
