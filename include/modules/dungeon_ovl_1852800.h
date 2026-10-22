#ifndef DUNGEON_OVL_1852800_H
#define DUNGEON_OVL_1852800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
struct S_func_81832800_1;
struct S_func_81832800_4;
struct S_81832FE8_0;
struct StructA0;
struct StructA2;
void decrement_flagged_item_parameters(struct S_func_81832800_1 *, struct S_func_81832800_4 *, void *);
void func_800247E8(struct S_81832FE8_0 *);
void update_shrinking_effect_sprite(struct StructA0 *, void *, SpriteFrameState *);
void func_80024860(struct StructA0 *, void *, SpriteFrameState *);
void update_homing_brightening_effect(void *, void *, SpriteFrameState *);
void func_800248F0(void *, void *, void *);
extern void (*const dungeon_1852800_entry)(struct S_func_81832800_1 *, struct S_func_81832800_4 *, void *);
#endif
