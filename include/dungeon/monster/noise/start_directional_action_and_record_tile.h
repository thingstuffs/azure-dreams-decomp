#ifndef DUNGEON_OVL_7F43F800_P08_H
#define DUNGEON_OVL_7F43F800_P08_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

typedef struct T_801748D0_S_801748D0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} T_801748D0_S_801748D0_0;   /* arg0 in func_801748D0 */


typedef struct T_801748D0_S_801748D0_3 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} T_801748D0_S_801748D0_3;   /* body in func_801748D0 */

typedef struct T_801748D0_S_801748D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
    void * unk_10;
} T_801748D0_S_801748D0_4;   /* obj in func_801748D0 */

typedef struct T_801748D0_S_801748D0_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} T_801748D0_S_801748D0_6_pre;   /* the 0x18 bytes before body_link in func_801748D0, addressed as body_link[-1] */

typedef struct T_801748D0_S_801748D0_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} T_801748D0_S_801748D0_10;   /* scratch in func_801748D0 */

typedef struct T_801748D0_S_801748D0_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} T_801748D0_S_801748D0_11;   /* link in func_801748D0 */

typedef struct {
    s16 delta[3];
    u16 pad06;
    u16 pos[3];
    u16 pad0E;
    s32 out0[2];
    s32 out1;
    s32 out2;
} T_801748D0_LocalFrame;

typedef struct {
    s32 w[12];
} T_801748D0_MeshCopy;

extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void * find_eligible_actor_at_tile_and_height();
extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern s32 resolve_record_orientation_or_fallback(s32, void *, s16 *, s16);
extern s32 RotTransPers(void *, void *, void *, void *);
extern void play_sound_if_enabled(s32);

extern void check_action_six_eligibility(void *, void *);
extern u8 D_80174EC8;
extern s8 view_direction_depth_biases[];
extern u8 noise_direction_frames[];
extern u8 noise_frame_set_2[];
void start_directional_action_and_record_tile(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void advance_timed_actor_visual_effect(ActorRecord *effect_state, ObjectPosition *position, SpriteFrameState *source_mesh, ActorRecord *actor);
void update_actor_behavior_and_direction(ActorRecord *motion, ObjectPosition *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor);
#endif
