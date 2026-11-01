#ifndef DUNGEON_MONSTER_BELDO_LARGE_H
#define DUNGEON_MONSTER_BELDO_LARGE_H

/* Function contracts owned by src/dungeon/monster/beldo_large/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

/* State shared by encounter overlay construction and its slide callback. */
typedef struct EncounterOverlayBody {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;
    u8 pad_14[0x4];
    u16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
} EncounterOverlayBody;

/* Body fields observed across the single multi-form segment ring generation. */
typedef struct MultiFormSegmentRingBody {
    union { u8 u; s8 s; } unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x0F];
    union { u16 u; s16 s; } unk_12;
    u8 pad_14[0x4];
    union { u16 u; s16 s; } unk_18;
    union { u16 u; s16 s; } unk_1A;
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x54];
    union { s16 s; u16 u; } unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    u16 unk_84;
    s16 unk_86;
    s16 unk_88;
    union { s16 s; u16 u; } unk_8A;
} MultiFormSegmentRingBody;

/* Callback state initialized by create_action_offset_object. */
typedef struct ActionOffsetObjectBody {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;
    u8 pad_14[0x10];
    void *unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} ActionOffsetObjectBody;
extern ObjectNodeHeader *beldo_camera_object;

extern ObjectNodeHeader *D_80175D64;

/* Both the constructor and phase loop visit sixteen node slots. */
extern ObjectNodeHeader *D_80175D78[16];

extern ObjectNodeHeader *encounter_offset_object;

void create_multi_form_segment_ring(EntityRec *origin);
void advance_linked_actor_motion_script(ActorRecord *state_in, ObjectPosition *motion_in, struct SpriteFrameState *sprite_in);




void update_actor_callbacks_and_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);
void update_vertical_motion_and_effect(void *motion, ObjectPosition *position, void *effect);
void *prepare_encounter_resource_descriptor(s32 input_value);
void register_encounter_cd_callbacks(s32 input_value);

/* Callback entry points. */
void advance_timed_blink_effect(void *state_data, void *unused, void *color_data);
void darken_encounter_view_color(u16 *entry);
void update_dungeon_actor_behavior(void *effect);
void create_timed_offset_motion_effect(u8 *unused, s16 duration, s32 offset_x, s32 offset_y, s32 offset_z);
void start_actor_directional_action(Rec_func_800A9E70_arg0 *state, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct BeldoMoveState;
void advance_actor_movement_step(struct BeldoMoveState *movement_in, ObjectPosition *action_ctx, SpriteFrameState *position, ActorRecord *actor);
void emit_multi_form_ring_geometry(MultiFormSegmentRingBody *animation, s32 *origin, void *color);
void initialize_action_offset_and_notify(ActionOffsetObjectBody *action, void *position);
void update_multi_form_actor_control(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void upload_encounter_texture(void);

void complete_actor_facing_action(Rec_func_800A9E70_arg0 *entity, ObjectPosition *unused_1, s32 unused_2, ActorRecord *target);
void create_player_centered_sequence_effect(void);
s32 try_actor_attack(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *target, ActorRecord *actor);

#endif
