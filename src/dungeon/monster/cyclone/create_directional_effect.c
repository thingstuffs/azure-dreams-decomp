#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad00[0x2A];
    s16 field2A;
    u8 pad2C[0x84];
    u16 fieldB0;
} FuncArg0;

typedef struct {
    s32 field00;
    s32 field04;
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
} FuncArg1;


typedef struct {
    u8 pad00[6];
    s16 field06;
    u8 pad08[4];
    s32 field0C;
    u16 field10;
    s16 field12;
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
    u8 pad20[8];
    s32 field28;
} FuncInner;

typedef struct {
    u8 pad00[4];
    s16 field04;
    u16 field06;
} FuncTail;

typedef struct {
    u8 pad00[8];
    FuncArg1 *buffer;
    FuncInner *inner;
    void *field10;
    u8 pad14[0xC];
    FuncTail tail;
} FuncTemp;

extern u32 D_801751C4;
extern void register_node(FuncTemp *, u8 *);
extern void select_sprite_entry(FuncInner *, s16, s16);

/* Creates a directional effect and initializes its sprite and offset position. */
s32 create_directional_effect(FuncArg0 *source, FuncArg1 *initial_motion, SpriteFrameState *render_source) {
    FuncTemp *effect;
    FuncTail *direction_state;
    SpriteFrameState *sprite;
    ObjectPosition *motion;
    s16 angle;
    s32 biased_angle;

    effect = (FuncTemp *)allocate_flagged_object_node(0x312);
    if (effect != NULL) {
        effect->field10 = &D_801751C4;
        register_node(effect, project_sprite_chain);
        angle = source->field2A;
        direction_state = &effect->tail;
        biased_angle = angle;
        direction_state->field04 = (s16) (((angle % 4096) << 0x10) >> 0x19);
        direction_state->field06 = source->fieldB0;
        sprite = effect->inner;
        sprite->animation_resource = render_source->animation_resource;
        sprite->flags |= 0x100;
        sprite->clut = direction_state->field06 + ((direction_state->field04 + 6) % 8);
        sprite->color.word = 0x808080;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->depth_bias = -1;
        sprite->flags |= 0xC;
        sprite->tpage_abr |= 0x20;
        select_sprite_entry(sprite, 0x30, 0);
        motion = effect->buffer;
        *(FuncArg1 *)motion = *initial_motion;
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        return (s32) effect;
    }
    return 0;
}
