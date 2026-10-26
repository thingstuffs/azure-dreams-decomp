#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80174CD8.h"
#include "dungeon/system.h"

struct Dst;
struct Elem;

typedef struct S_801722F0_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_801722F0_1;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void update_cascading_trail_emitter(void *record_data);
extern Rec_D_80174CD8 *ghosh_boss_node;

/* Create an effect at the source position and play its sound. */
void spawn_cascading_trail_emitter(void) {
    SpriteFrameState *sprite;
    void *setup_data;
    ObjectPosition *source_pos;
    ObjectNodeHeader *effect;
    S_801722F0_1 *effect_params;
    ObjectPosition *effect_pos;

    source_pos = ghosh_boss_node->unk_08;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        setup_data = project_sprite_chain;
        effect_params = ((void *)effect) + 0x20;
        effect_params->unk_16 = 0x1E;
        effect_params->unk_18 = 0x1E;
        effect->update_callback = &update_cascading_trail_emitter;
        register_node(effect, setup_data);
        sprite = effect->sprite;
        sprite->depth_bias = 0;
        effect_pos = effect->position;
        effect_pos->x.v = (s32) source_pos->x.v;
        effect_pos->y.v = (s32) source_pos->y.v;
        effect_pos->z.v = (s32) source_pos->z.v;
        sprite = effect->sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->flags = (u16) (sprite->flags | 0x80);
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
        play_sound_if_enabled(0x703);
    }
}
