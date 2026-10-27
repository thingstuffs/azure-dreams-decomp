#ifndef DUNGEON_ACTOR_SPELL_RESOURCE_IDS_G01008_H
#define DUNGEON_ACTOR_SPELL_RESOURCE_IDS_G01008_H
#include "engine/node/allocation.h"

struct ObjectPosition;
/* spell resource ids g01008. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01008 - CL:dungeon/func_800A3C30, CL:dungeon/func_800A40CC, PD:dungeon/engine:800DD8E7. */

/* Spell resource ids (G00331). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A3C30, PD:dungeon/engine:800DD8E7. */
/* Spell resource ids shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A3C30, PD:dungeon/engine:800DD8E7. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/def_table.h"
#include "shared/sys_flags.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
struct S_800AD594_0;

typedef struct Inner {
    u8 pad[1];
    u8 flag;
} Inner;

typedef struct S_800A94A0_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x23];
    u8 unk_2B;
    u8 pad_2C[0x4C];
    void * unk_78;
    u8 pad_7C[0x24];
    s16 unk_A0;
} S_800A94A0_0;

/* arg0 in create_actor_spell_effect; pointer addresses record offset 0x18 */
typedef struct S_800A94A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_800A94A0_2;

typedef struct S_800A94A0_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
} S_800A94A0_3;

typedef struct S_800A94A0_6 {
    s32 unk_00;
} S_800A94A0_6;

/* Pointer addresses record offset 0x14. */
typedef struct S_800A94A0_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A94A0_7;


typedef struct S_800A94A0_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A94A0_9;

/* 49 resource slots occupy the byte span before the next spell table. */
extern u8 spell_resource_ids[49];
/* *D_800E3D7C in create_actor_spell_effect */
extern u8 active_spell_parameters[];
extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];
s32 rand(void);
void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
u8 * expand_text_control_codes();
u8 * clear_byte_and_advance(u8 *byte_ptr);
u8 *append_entity_display_text(void *record, u8 *out);
s16 get_tile_chebyshev_distance();
s32 display_text_with_fullwidth_adjustment(s8 *text);
s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
void setup_object_within_planar_range(void *object, s32 x, s32 y, s32 height, s32 mode, s32 settings);
void spend_actor_mp(struct S_800AD594_0 *entity, s32 base_reduction);
extern u8 D_80089080[];
extern u8 spell_mp_costs[];
extern u8 alternate_spell_mp_costs[];
extern u8 D_800E1C58[12];
extern u8 current_spell_effect_variant;
extern void Control_CD(s32, void *, void *);
extern void sound_set_cd_cue_parameters(s32, s32, s32, s32);
extern void pack_tagged_resource_descriptor(s32, void *, void *, s32);
extern s32 read_stream_cue_start_offset(void);
extern s32 cd_cue_base[];
extern s8 spell_effect_selector_cache;
extern u8 spell_resource_load_state;
extern s32 spell_audio_cues[];
extern s32 D_800DDAB8[];
extern s32 D_800E58B0[];

/* Functions defined in this translation unit. */
s32 resolve_spell_effect_resource_id(s16 index);
s16 resolve_alternate_spell_id(s32 tile_index);
void *create_actor_spell_effect(void *actor, void *effect_record, s16 mode, void *context);
s32 load_spell_effect_code(s32 selection_id, s32 alternate_table, s32 unused);

#endif
