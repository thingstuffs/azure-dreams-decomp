#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

s32 rand();                                /* extern */
extern M2C_UNK D_800FBE24;

typedef struct S_807AFC9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807AFC9C_0;

typedef struct S_807AFC9C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFC9C_1;

   /* arg1 in func_800F749C */

typedef struct S_807AFC9C_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFC9C_4;   /* arg2 in func_800F749C */

typedef struct S_807AFC9C_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_807AFC9C_5;

/* Spawns an effect near the origin with color channels selected by the source flags. */
void func_800F749C(s32 spawn_arg, MovingPosition *origin, S_807AFC9C_4 *source) {
    SpriteFrameState *sprite;
    S_807AFC9C_1 *position;
    void *effect;
    S_807AFC9C_5 *effect_state;

    effect = allocate_list_node(0x212, spawn_arg);
    if (effect != NULL) {
        ((S_807AFC9C_0 *)effect)->unk_10 = (void *)func_800F7348;
        register_node(effect, project_sprite_chain);
        position = ((S_807AFC9C_0 *)effect)->unk_08;
        position->unk_02 = (s16) ((origin->unk_02 + (rand() & 0x3F)) - 0x20);
        position->unk_06 = (s16) ((origin->unk_06 + (rand() & 0x3F)) - 0x20);
        position->unk_0A = (s16) ((origin->unk_0A + (rand() & 0x3F)) - 0x20);
        sprite = ((S_807AFC9C_0 *)effect)->unk_0C;
        sprite->source = &D_800FBE24;
        if (source->unk_14 & 1) {
            sprite->color.c.r = 0x20;
        }
        if (source->unk_14 & 2) {
            sprite->color.c.b = 0x20;
        }
        if (source->unk_14 & 4) {
            sprite->color.c.g = 0x20;
        }
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->unk_06 = 8;
        effect_state = effect + 0x20;
        sprite->flags = (u16) (sprite->flags | 0xC);
        effect_state->unk_0C = 0x10;
        ((S_807AFC9C_0 *)effect)->unk_20 = source;
        effect_state->unk_04 = origin;
    }
}
