#ifndef TOWN_SCENE_OBJECT_H
#define TOWN_SCENE_OBJECT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"


/* tick_timed_object_and_mark_complete.c */
void tick_timed_object_and_mark_complete(void *ptr);

void initialize_scene_slot_thirteen(void *object, void *position, SpriteFrameState *sprite);

void initialize_scene_slot_forty_sprite(void *object, void *position, SpriteFrameState *sprite);

void initialize_scene_slot_ten(void *object, void *position, SpriteFrameState *sprite);

typedef struct FallingObjectState {
    u8 pad_00[0x4C];
    s8 mode;
    s8 phase;
    u8 pad_4E[2];
    void *callback;
    u8 pad_54[0x18];
    s16 timer;
} FallingObjectState;
void initialize_falling_object_sprite(FallingObjectState *object, void *context, void *sprite);

typedef struct SpriteSixState {
    u8 pad_00[0x66];
    s16 angle;
} SpriteSixState;

typedef union SpriteSixNodeView {
    SpriteSixState *state;
    ObjectNodeHeader *header;
} SpriteSixNodeView;

typedef union SpriteSixRender {
    SpriteFrameState sprite;
    struct {
        u8 pad_00[8];
        s32 object_id;
    } record;
} SpriteSixRender;

void initialize_sprite_six(SpriteSixState *state, ObjectPosition *position, SpriteSixRender *render);

/* Callback entry points. */
void update_panel_aggregate_value(void *entry);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_func_80094268_arg0.h"
void unlink_scene_list_node(Rec_func_80094268_arg0 *node);

#endif
