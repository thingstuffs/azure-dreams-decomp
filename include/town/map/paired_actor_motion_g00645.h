#ifndef TOWN_MAP_PAIRED_ACTOR_MOTION_G00645_H
#define TOWN_MAP_PAIRED_ACTOR_MOTION_G00645_H
#include "town/person/position.h"

struct SpriteFrameState;
/* Paired actor motion (G00645). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D20CC, PD:town/engine:800E9E14, PD:town/engine:800E9E34, PD:town/engine:800E9E7C. */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "shared/object_node.h"
#include "shared/entity.h"


typedef struct Func800BFE50Object {
    u8 pad00[0x48];
    s32 field48;
    u8 pad4C[4];
    s32 field50;
    u8 pad54[0x68 - 0x54];
    s16 field68;
    u8 pad6A[0x95 - 0x6A];
    u8 field95;
    u8 pad96[0xA0 - 0x96];
    s32 fieldA0;
    s32 fieldA4;
} Func800BFE50Object;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    u8 pad0[0x48];
    u16 counter;
} Actor;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;

/* Parent body coordinating the two linked motions in the event_tori_in effect. */
typedef struct EventToriInBody {
    /* 0x00 */ ObjectPosition *child_positions[2];
    /* 0x08 */ Copy16 position;
    /* 0x18 */ Copy8 motion;
    /* 0x20 */ union { s16 s; u16 u; } state;
    /* 0x22 */ u16 ticks;
} EventToriInBody;

typedef struct S_800BD980_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
} S_800BD980_0;

typedef struct LinkedMotionObject {
    u8 pad_00[0x10];
    union {
        void (*parent)(void *);
        void (*child)(void *, void *, s32);
    } update;
    u8 pad_14[0x14];
    Copy16 position;
    Copy8 motion;
} LinkedMotionObject;

typedef struct MotionSource {
    Copy16 position;
    Copy8 motion;
} MotionSource;

/* arg1 in update_randomized_actor_movement */
extern s32 check_transform_identifier_and_hook(s32);
extern s16 SD_Call(s32);
extern void unlink_node_if_registered(void *);
extern s32 D_800E9E34[];
extern s32 D_800E9E54[];
extern u8 paired_actor_sprite_entries[];
extern s32 D_800E9ECC[];
extern void configure_the_set_mode_n_1(void *, void *, void *);
extern u8 D_800BCE78[];
extern u8 town_map_motion_defaults[];
extern s32 D_800D2130;
extern int abs(int);

extern s32 rand(void);
extern void advance_sprite_animation_and_textures(void *);
struct Dst;
struct Elem;
struct ObjectNodeHeader;
extern void select_record_entry_and_value(void *,void *, s16);
extern s32 register_node(struct ObjectNodeHeader *, void *);
extern void *allocate_list_node(s32, void *);
extern s32 D_800E9E14[];
/* Functions defined in this translation unit. */
void update_randomized_actor_movement(void *actor, ObjectPosition *motion,struct SpriteFrameState *sprite, s32 update_mode);
void initialize_object_and_dispatch_by_state(Func800BFE50Object *object, s32 *params, void *dispatch_context);
void randomize_paired_object_motion(void *pair_in);
void advance_motion_and_flag_zero_velocity(Actor *actor, Motion *motion, s32 actor_id);
s32 event_tori_in(void *source);

#endif
