#include "shared/object_node.h"
#include "shared/entity.h"
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

void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 rand();
void update_rising_trail_emitter(void *record_data, S_801720D0_0 *state);
extern Rec_D_80174CD8 *ghosh_boss_node;

/* Spawn and initialize an effect at a random offset from the source position. */
void spawn_rising_trail_emitter(void)
{
    SpriteFrameState *sprite_header;
    SpriteFrameState *sprite;
    ObjectPosition *effect_pos;
    ObjectPosition *source_pos;
    ObjectNodeHeader *effect;
    S_80172160_1 *effect_state;
    s32 random_offset;
    s32 coord;

    source_pos = ghosh_boss_node->unk_08;
    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_16 = 0x1E;
        effect_state->unk_18 = 0x1E;
        effect->update_callback = &update_rising_trail_emitter;
        register_node(effect, project_sprite_chain);
        sprite_header = effect->sprite;
        sprite_header->depth_bias = 0;
        effect_pos = effect->position;
        effect_pos->x.v = source_pos->x.v;
        effect_pos->y.v = source_pos->y.v;
        effect_pos->z.v = source_pos->z.v;
        random_offset = rand(sprite_header);
        coord = *(u16 *)&effect_pos->x.w.i;
        random_offset &= 0x3F;
        coord -= 0x20;
        coord += random_offset;
        effect_pos->x.w.i = coord;
        random_offset = rand();
        coord = *(u16 *)&effect_pos->y.w.i;
        random_offset &= 0x3F;
        coord -= 0x20;
        coord += random_offset;
        effect_pos->y.w.i = coord;
        sprite = effect->sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags |= 0x80;
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
    }
}
