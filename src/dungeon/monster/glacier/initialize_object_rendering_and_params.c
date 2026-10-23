#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} Sub1;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} Sub2;

typedef struct {
    u8 pad0[8];
    Sub2 *sub2;
    Sub1 *sub1;
    u8 pad10[0x38];
    s32 field48;
} Obj;

extern void sprite_chain_projector_address(void);
extern void register_node(void *, void (*)(void));

/* Initialize object rendering and copy the three supplied parameter fields. */
void initialize_object_rendering_and_params(Obj *object, s32 state_value, Sub2 *source_params)
{
    SpriteFrameState *render_state;
    ObjectPosition *dest_params;

    object->field48 = state_value;
    register_node(object, sprite_chain_projector_address);
    render_state = object->sub1;
    render_state->tpage_abr = 0x20;
    render_state->flags |= 0xC;
    dest_params = object->sub2;
    dest_params->x.w.i = source_params->field2;
    dest_params->y.w.i = source_params->field6;
    dest_params->z.w.i = source_params->fieldA;
    render_state = object->sub1;
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->color.c.b = 0x80;
    render_state->color.c.g = 0x80;
    render_state->color.c.r = 0x80;
}
