#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"


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

typedef struct S_800C52D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800C52D0_1;

   /* arg1 in compute_offset_position */


/* Computes an offset position and subtracts 0x20 from the output state. */
void compute_offset_position(S_800C52D0_0 *object, IntVector3 *out_pos, SpriteFrameState *state) {
    s32 z_product;
    SpriteFrameState *offsets;
    IntVector3 *base_pos;
    S_800C52D0_1 *object_data;

    object_data = object->unk_9C;
    base_pos = object_data->unk_08;
    offsets = object_data->unk_0C;
    out_pos->y = (s32) base_pos->y;
    out_pos->x = (s32) (base_pos->x + (offsets->scale_x * D_800D5138));
    z_product = ((S_800C52D0_7 *)(((ObjectPayloadView *)offsets)->unk_08))->unk_03 * offsets->scale_y;
    out_pos->z = (s32) (base_pos->z + ((z_product / 4096) * D_800D513C));
    state->angle_z = (u16) (state->angle_z - 0x20);
}
