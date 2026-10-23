#ifndef DUNGEON_OVL_185E800_H
#define DUNGEON_OVL_185E800_H
#include "shared/dungeon_height_query.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_delay_views.h"
#include "shared/slus_callbacks.h"
extern u8 secondary_sprite[];
extern u8 landing_sprite_entries[];
extern u8 fading_sprite_entries[];
void *allocate_list_node(s32, void *);
void *func_8003FD64(s32, void *);
s32 rand(void);
s32 get_definition_entry_byte_13(s16);
void *scan_actor_along_heading(void *, s32, s32, s32, s32);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
void play_sound_if_enabled(s32);
void register_node(void *, void *);
void func_8004491C(void *, void *);
void advance_sprite_animation_and_textures(void *);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);
void func_80024020(u8 *, u8 *);
void advance_delayed_fading_sprite(void *, DelayPosition *, SpriteFrameState *);
void brighten_accelerate_and_fade_effect(void *, DelayMotion *, DelaySpriteColor *);
#endif
