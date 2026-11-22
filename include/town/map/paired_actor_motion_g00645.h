#ifndef TOWN_MAP_PAIRED_ACTOR_MOTION_G00645_H
#define TOWN_MAP_PAIRED_ACTOR_MOTION_G00645_H
#include "engine/node/registration.h"
#include "engine/node/allocation.h"
#include "town/map/motion_defaults_data.h"
struct SpriteFrameState;
#include "town/person/position.h"

struct SpriteFrameState;
/* Paired actor motion. */
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
#include "shared/town_object.h"
#include "sdk/abs.h"
#include "sdk/rand.h"


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

/* Each of the two child nodes stores the origin's integer coordinates and
 * advances its animation on the eighth tick. */
typedef struct EventToriChildBody {
    u8 pad_00[0x0C];
    u16 origin_x, origin_y, origin_z;
    u8 pad_12[0x36];
    u16 counter;
} EventToriChildBody;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;

/* The event copies these four words together. Its child setup also reads
 * the integer halves and complete words of the first three coordinates. */
typedef struct EventToriOriginCopy {
    Fixed1616 x, y, z;
    s32 fourth_word;
} EventToriOriginCopy;

/* Parent body coordinating the two linked motions in the event_tori_in effect. */
typedef struct EventToriInBody {
    /* 0x00 */ ObjectPosition *child_positions[2];
    /* 0x08 */ EventToriOriginCopy position;
    /* 0x18 */ Copy8 motion;
    /* 0x20 */ union { s16 s; u16 u; } state;
    /* 0x22 */ u16 ticks;
} EventToriInBody;

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
    EventToriOriginCopy position;
    Copy8 motion;
} MotionSource;

/* arg1 in update_randomized_actor_movement */
extern s32 check_town_target_and_callback(const void *object);
extern s16 SD_Call(s32);
extern void unlink_node_if_registered(void *);
extern s32 D_800E9E34[];
extern s32 D_800E9E54[];
extern u8 paired_actor_sprite_entries[];
extern s32 D_800E9ECC[];
struct ObjectPosition;
extern void init_scene_node_mode_1(void *, struct ObjectPosition *, void *);
extern u8 D_800BCE78[];
extern s32 D_800D2130;

extern void advance_sprite_animation_and_textures(void *);
struct Dst;
struct Elem;
struct ObjectNodeHeader;
extern void select_record_entry_and_value(void *,void *, s16);
extern s32 D_800E9E14[];
/* Functions defined in this translation unit. */
void update_randomized_actor_movement(TownObjectRecord *actor, ObjectPosition *motion,struct SpriteFrameState *sprite, s32 update_mode);
void init_paired_actor_motion(TownObjectRecord *object, ObjectPosition *params, SpriteFrameState *dispatch_context);
void update_tori_pair_motion(EventToriInBody *pair);
void update_tori_child_sprite(EventToriChildBody *actor, ObjectPosition *motion, struct SpriteFrameState *actor_id);
s32 event_tori_in(void *source);

#endif
