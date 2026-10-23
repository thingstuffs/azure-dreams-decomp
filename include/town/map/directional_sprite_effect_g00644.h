#ifndef TOWN_MAP_DIRECTIONAL_SPRITE_EFFECT_G00644_H
#define TOWN_MAP_DIRECTIONAL_SPRITE_EFFECT_G00644_H

struct SpriteFrameState;
/* Directional sprite effect (G00644). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800F15E4. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
#include "sdk/libgte.h"

typedef struct S_800BC574_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BC574_7;

/* copy_dst in create_directional_sprite_effect */
/* held_arg0 in create_directional_sprite_effect */
typedef struct S_800BC574_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BC574_5;

typedef struct S_800BC6CC_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800BC6CC_0;

struct Dst;

struct Elem;

typedef struct S_800BC764_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
} S_800BC764_0;

typedef struct S_800BC840_0 {
    s32 * unk_00;
    u8 pad_04[0x54];
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
} S_800BC840_0;

/* extern */
struct Rec_func_8008F074_arg0;

void *allocate_list_node();
/* extern */
s32 register_node();
/* extern */
/* extern */
/* extern */
extern void D_800BC6CC();
#include "shared/sprite_source.h"
extern SpriteSourceEntry town_directional_sprite_entries[];
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
void configure_the_set_mode_n_1(struct Rec_func_8008F074_arg0 *, s32, s32);
/* extern */
extern void D_800BC764();
extern M2C_UNK town_map_motion_defaults;
extern s32 D_800D20E4;

extern void advance_sprite_animation_and_textures(void *);
/* Functions defined in this translation unit. */
s32 create_directional_sprite_effect(void *position, s16 angle);
void advance_coordinates_and_propagate_flags(void *object_data, void *motion,struct SpriteFrameState *status);
void wait_then_process_record(S_800BC764_0 *context, void *unused, struct SpriteFrameState *record);
void initialize_record_resources(void *record, s32 init_context, s32 resource_target);

#endif
