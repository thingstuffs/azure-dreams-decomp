#include "shared/object_node.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/node.h"



typedef struct {
    ObjectNodeHeader header;
    u8 pad20[0x28];
    void *field48;
} Obj;

extern void sprite_chain_projector_address(void);

/* Initialize object rendering and copy the three supplied parameter fields. */
void initialize_object_rendering_and_params(Obj *object, void *state_value, ObjectPosition *source_params)
{
    SpriteFrameState *render_state;
    ObjectPosition *dest_params;

    object->field48 = state_value;
    register_node(&object->header, sprite_chain_projector_address);
    render_state = object->header.sprite;
    render_state->tpage_abr = 0x20;
    render_state->flags |= 0xC;
    dest_params = object->header.position;
    dest_params->x.w.i = source_params->x.w.i;
    dest_params->y.w.i = source_params->y.w.i;
    dest_params->z.w.i = source_params->z.w.i;
    render_state = object->header.sprite;
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->color.c.b = 0x80;
    render_state->color.c.g = 0x80;
    render_state->color.c.r = 0x80;
}
