#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80174CD8.h"

typedef struct S_801720D0_0 S_801720D0_0;

struct Dst;
struct Elem;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172160_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_80172160_1;

typedef struct S_80172160_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80172160_2;

typedef struct S_80172160_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80172160_4;

typedef struct S_80172160_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172160_5;

void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
extern s32 rand();
void update_rising_trail_emitter(void *record_data, S_801720D0_0 *state);
extern Rec_D_80174CD8 *D_80174CD8;

/* Spawn and initialize an effect at a random offset from the source position. */
void spawn_rising_trail_emitter(void)
{
    SpriteFrameState *sprite_header;
    SpriteFrameState *sprite;
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
        ((S_80172160_2 *)effect)->unk_10 = &update_rising_trail_emitter;
        register_node(effect, project_sprite_chain);
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
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags |= 0x80;
        func_8003DB94(sprite, D_800DE870, 0);
    }
}
