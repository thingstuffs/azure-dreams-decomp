#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "engine/graphics.h"

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
    u8 pad00[4];
    s16 field04;
    u16 field06;
} FuncTail;

typedef struct {
    ObjectNodeHeader header;
    FuncTail tail;
} FuncTemp;

extern u32 D_80175480;
struct SpriteFrameState;

/* Creates a directional effect and applies the supplied position offsets. */
s32 create_offset_directional_effect(FuncArg0 *source, FuncArg1 *position, SpriteFrameState *render_context) {
    FuncTemp *effect;
    FuncTail *direction_state;
    SpriteFrameState *sprite;
    ObjectPosition *effect_position;
    s16 angle;
    s32 biased_angle;

    effect = allocate_flagged_object_node(0x312);
    if (effect != NULL) {
        effect->header.update_callback = &D_80175480;
        register_node(&effect->header, project_sprite_chain);
        angle = source->field2A;
        direction_state = &effect->tail;
        biased_angle = angle;
        direction_state->field04 = (s16) (((angle % 4096) << 0x10) >> 0x19);
        direction_state->field06 = source->fieldB0;
        sprite = effect->header.sprite;
        sprite->animation_resource = render_context->animation_resource;
        sprite->flags |= 0x100;
        sprite->clut = direction_state->field06 + ((direction_state->field04 + 6) % 8);
        sprite->color.word = 0x808080;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->depth_bias = 1;
        sprite->flags |= 0xC;
        sprite->tpage_abr |= 0x20;
        select_sprite_entry(sprite, 0x31, 0);
        effect_position = effect->header.position;
        *(FuncArg1 *)effect_position = *position;
        effect_position->x.v += effect_position->velocity_x;
        effect_position->y.v += effect_position->velocity_y;
        return (s32) effect;
    }
    return 0;
}
