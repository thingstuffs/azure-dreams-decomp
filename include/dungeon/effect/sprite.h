#ifndef DUNGEON_EFFECT_SPRITE_H
#define DUNGEON_EFFECT_SPRITE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_800244BC_2;
s32 ground_items_lack_special_pair(void);
void advance_target_chasing_emitter(void *object, struct S_800244BC_2 *position, s32 context);
void *create_an_copies_three_source_fields_child_runs_n_16_child_setup(s32 value, void *source, s32 unused, s32 context);
void *draw_sprite_effect_quads(u8 *sprite_list, s32 count_hint, s32 render_state_addr, u8 *placement, u8 *packet_buf);
void process_effect_block_entries(void *block);







void advance_damped_animated_sprite(void *entry, ObjectPosition *motion, SpriteFrameState *object);
void update_spiral_effect(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
