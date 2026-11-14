#ifndef TOWN_SCENE_ANIMATION_H
#define TOWN_SCENE_ANIMATION_H
struct TownCollectionSequence;

#include "common.h"

struct FallingTimedSceneObject;

struct ObjectPosition;
struct SpriteFrameState;

/* Controller shared by the timed actor creator and its falling objects. */
typedef struct FallingSceneController {
    s16 state;
    s16 timer;
    u16 phase;
    union { s16 s; u16 u; } value;
    union { s16 s; u16 u; } level;
    s16 count;
    u16 flags;
} FallingSceneController;

/* Body of the rising effect object: root link, mode, and per-frame state. */
typedef struct RisingEffectObject {
    /* 0x00 */ void *root;
    /* 0x04 */ s32 field_04;
    /* 0x08 */ s32 field_08;
    /* 0x0C */ union { s16 s; u16 u; } mode;
    /* 0x0E */ s16 field_0E;
    /* 0x10 */ u16 field_10;
} RisingEffectObject;

/* draw_rotating_collection_frame.c */
void draw_rotating_collection_frame(struct TownCollectionSequence *object);

/* Body passed to the collection-center update callback installed by create_collection_center_group. */
typedef struct CollectionCenterControlBody {
    /* 0x00 */ void *work;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 pad_0C[0x4C];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ u8 pad_60[0x2];
    /* 0x62 */ u16 unk_62;
    /* 0x64 */ u8 pad_64[0x8];
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ u16 unk_72;
    /* 0x74 */ u16 unk_74;
} CollectionCenterControlBody;

/* Callback entry points. */
void animate_collection_center_sprite(CollectionCenterControlBody *ctrl, struct ObjectPosition *setup, struct SpriteFrameState *view);
void animate_falling_timed_object(struct FallingTimedSceneObject *obj, struct ObjectPosition *motion, void *incoming_out);
void animate_rising_effect_object(RisingEffectObject *obj, struct ObjectPosition *state_in, void *input);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Actor;
struct State;
void animate_bouncing_score_object(struct State *st, struct ObjectPosition *mot, struct Actor *actor);

#endif
