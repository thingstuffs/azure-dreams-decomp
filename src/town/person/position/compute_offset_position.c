#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"
#include "shared/object_node.h"
#include "town/person/position.h"
#include "shared/object_node.h"


typedef struct S_800C52D0_7 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800C52D0_7;


extern const s32 D_800D5138;
extern s32 D_800D513C;

typedef struct S_800C52D0_0 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800C52D0_0;   /* arg0 in compute_offset_position */



/* Computes an offset position and subtracts 0x20 from the output state. */
void compute_offset_position(S_800C52D0_0 *object, ObjectPosition *out_pos, SpriteFrameState *state) {
    s32 z_product;
    SpriteFrameState *offsets;
    ObjectPosition *base_pos;
    ObjectNodeHeader *owner;

    owner = object->unk_9C;
    base_pos = owner->position;
    offsets = owner->sprite;
    out_pos->y.v = base_pos->y.v;
    out_pos->x.v = base_pos->x.v + (offsets->scale_x * D_800D5138);
    z_product = ((S_800C52D0_7 *)offsets->source)->unk_03 * offsets->scale_y;
    out_pos->z.v = base_pos->z.v + ((z_product / 4096) * D_800D513C);
    state->angle_z = (u16) (state->angle_z - 0x20);
}
