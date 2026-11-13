#ifndef TOWN_SCENE_OBJECT_H
#define TOWN_SCENE_OBJECT_H

#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"


/* tick_timed_object_and_mark_complete.c */
void tick_timed_object_and_mark_complete(void *ptr);

void initialize_scene_slot_thirteen(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

void initialize_scene_slot_forty_sprite(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

void initialize_scene_slot_ten(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite);

typedef struct FallingObjectState {
    u8 pad_00[0x4C];
    s8 mode;
    s8 phase;
    u8 pad_4E[2];
    void *callback;
    u8 pad_54[0x18];
    s16 timer;
} FallingObjectState;

typedef union SpriteSixNodeView {
    TownObjectRecord *state;
    ObjectNodeHeader *header;
} SpriteSixNodeView;

typedef union SpriteSixRender {
    SpriteFrameState sprite;
    struct {
        u8 pad_00[8];
        s32 object_id;
    } record;
} SpriteSixRender;

void initialize_sprite_six(TownObjectRecord *state, ObjectPosition *position, SpriteSixRender *render);

/* Callback entry points. */
void update_panel_aggregate_value(void *entry);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void unlink_scene_list_node(TownObjectRecord *node);

void func_8052FE94(s16 object_value);

void build_object_set_and_select_lists(s32 *records, void *ost_w, void *osel_w);
void build_object_set_and_select_lists_rev_b(s32 *entries, s32 ost_w, s32 *osel_w);

void init_runtime_pointers_from_shared_buffer(void);

s32 check_object_callback_returns_two(void);

struct TownSceneListNode;
s32 append_scene_list_node(struct TownSceneListNode *node);

#endif
