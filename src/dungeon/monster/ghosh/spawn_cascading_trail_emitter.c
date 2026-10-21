#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80174CD8.h"

struct Dst;
struct Elem;

typedef struct S_801722F0_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_801722F0_1;

typedef struct S_801722F0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_801722F0_2;

typedef struct S_801722F0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801722F0_4;

typedef struct S_801722F0_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801722F0_5;

s32 register_node();
extern void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
s32 play_sound_if_enabled();
extern void update_cascading_trail_emitter(void *record_data);
extern Rec_D_80174CD8 *ghosh_boss_node;

/* Create an effect at the source position and play its sound. */
void spawn_cascading_trail_emitter(void) {
    SpriteFrameState *sprite;
    void *setup_data;
    S_801722F0_5 *source_pos;
    void *effect;
    S_801722F0_1 *effect_params;
    S_801722F0_4 *effect_pos;

    source_pos = ghosh_boss_node->unk_08;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        setup_data = project_sprite_chain;
        effect_params = effect + 0x20;
        effect_params->unk_16 = 0x1E;
        effect_params->unk_18 = 0x1E;
        ((S_801722F0_2 *)effect)->unk_10 = &update_cascading_trail_emitter;
        register_node(effect, setup_data);
        sprite = ((S_801722F0_2 *)effect)->unk_0C;
        sprite->unk_06 = 0;
        effect_pos = ((S_801722F0_2 *)effect)->unk_08;
        effect_pos->unk_00 = (s32) source_pos->unk_00;
        effect_pos->unk_04 = (s32) source_pos->unk_04;
        effect_pos->unk_08 = (s32) source_pos->unk_08;
        sprite = ((S_801722F0_2 *)effect)->unk_0C;
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
